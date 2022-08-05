#include "stdafx.h"

#include "RowColumnInfo.h"

#include "SLSAutoPtr.h"

#include "SLSException.h"

/** The size of the bind buffer.*/
static const size_t SIZEOFBUFFER = 1024;

struct BindObject
{
public:
    BindObject() throw()
    : m_status(0)
    {
        memset(m_value, 0, sizeof(m_value)/sizeof(m_value[0]));
    }

    ~BindObject() throw() {}

public:
    wchar_t  m_value[SIZEOFBUFFER];
    DWORD    m_status;
};

/** Error info class.*/
struct RCErrorInfo
{
public:
    RCErrorInfo() throw()
    : m_source(0)
    , m_description(0)
    , m_helpContext(0)
    , m_guid(GUID_NULL)
    , m_helpFile(0)
    {
    }

    /** Standard destructor.*/
    virtual ~RCErrorInfo() throw()
    {
        try {
            if (m_source)       SysFreeString(m_source);
            if (m_description)  SysFreeString(m_description);
            if (m_helpFile)     SysFreeString(m_helpFile);
        }
        catch (...) { }
    }

    BSTR    m_source;
    BSTR    m_description;
    DWORD   m_helpContext;
    GUID    m_guid;
    BSTR    m_helpFile;
};

bool RowColumnInfo::Export(ISTableSink& sink)
{    
    bool brc (false);
    if (m_data.GetCount() > 0) {
        unsigned long cols = getNumColumns(),
                      rows = getNumRows();
        CAtlArray<CAtlString> arrayValues;

        DBCOLUMNINFO *colinfo = m_dbcolinfo[0];
        for (unsigned i = 0; i < cols; ++i) {
            arrayValues.Add(colinfo->pwszName);
            ++colinfo;
        }

        sink.Begin();
        sink.SetColumns(arrayValues);

        for (unsigned i = 0; i < rows; ++i) {
            CAtlList<RowData *> *rd = getRowData(i);
            if (rd) {
                arrayValues.RemoveAll();
                for (POSITION pos = rd->GetHeadPosition(); 0 != pos;) {
                    RowData *data = rd->GetNext(pos);
                    arrayValues.Add(data->getData());
                }
                sink.AddRowSet(arrayValues);
            }
        }

        sink.End();
        brc = true;
    }
    return brc;
}

HRESULT RowColumnInfo::Execute(const CSession & session, const wchar_t * sql, COutputWatcher * pWatcher)
{
    HRESULT hr = E_FAIL;

    try
	{
        CDBPropSet propset(DBPROPSET_ROWSET);
        CCommand<CManualAccessor, CRowset, CMultipleResults> rs;

        // Open without binding with row count.
        //TraceInfo(L"Open:%s", (const wchar_t *) sql);
        hr = rs.Open(session, sql, &propset, 0, DBGUID_SQL, FALSE);
        if (pWatcher) pWatcher->m_hr = hr;

        // No matter what the results are we  will get the message.
        getErrorInfoMessages(rs.m_spCommand, pWatcher);
        if (FAILED(hr))
		{
			SLSException ex("cannot open record set", SLSException::DOInitError, __FILE__, __LINE__);
            //TraceThrow(SLSException, ex);
        }

        // Clear the old instance 
        clear();

        while (S_OK == hr)
		{
            // if there is no result set simply exit with success
            if (rs.m_spRowset != 0)
			{    // exception to coding conv rule due to COM
                // Get the column information
                DBORDINAL  cols = 0;
                DBCOLUMNINFO * colInfo = 0;
                LPOLESTR strings = 0;

                hr = rs.GetColumnInfo(&cols, &colInfo, &strings);
                if (pWatcher) pWatcher->m_hr = hr;
                if (!SUCCEEDED(hr))
				{
                    getErrorInfoMessages(rs.m_spCommand, pWatcher);
					SLSException ex("GetColumnInfo failed", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }

                m_dbcolinfo.SetAtGrow( m_resultSets, colInfo );
                m_strings.SetAtGrow( m_resultSets, strings );

                CAutoPtr<BindObject> bind(new BindObject[cols + 1]);

                if (0 == bind.m_p)
				{
					SLSException ex("bind = 0", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }

                BindObject *bobj = dynamic_cast<BindObject *> (bind.m_p + 0);
                if (0 == bobj)
				{
					SLSException ex("bobj = 0", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }

                hr = rs.CreateAccessor((int)cols, bobj, ((DBLENGTH)sizeof(BindObject)) * (DBLENGTH)cols);
                if (pWatcher) pWatcher->m_hr = hr;
                if (!SUCCEEDED(hr))
				{
                    getErrorInfoMessages(rs.m_spCommand,  pWatcher);
					SLSException ex("CreateAccessor failed", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }
                
                for (unsigned long cnt = 0; cnt < cols; cnt++)
				{
                    BindObject *bobj = dynamic_cast<BindObject *>(bind.m_p + cnt);
                    if (0 == bobj)
					{
						SLSException ex("BindObject cast failed", SLSException::DOInitError, __FILE__, __LINE__);
                        //TraceThrow(SLSException, ex);
                    }
                    rs.AddBindEntry(cnt + 1, DBTYPE_WSTR, sizeof(bobj->m_value)/ sizeof(bobj->m_value[0]), 
                                    &bobj->m_value, NULL, &bobj->m_status);
                }

                hr = rs.Bind();
                if (pWatcher) pWatcher->m_hr = hr;
                if (!SUCCEEDED(hr))
				{
                    getErrorInfoMessages(rs.m_spCommand, pWatcher);
					SLSException ex("bind failed", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }
                
                ULONG fields = (ULONG)cols;

                CAtlArray< CAtlList< RowData *> * > * resultSet = new CAtlArray< CAtlList< RowData *> *>;
                if (0 == resultSet)
				{
					SLSException ex("resultSet = 0", SLSException::DOInitError, __FILE__, __LINE__);
                    //TraceThrow(SLSException, ex);
                }

                m_data.SetAtGrow( m_resultSets, resultSet );

                int itemcnt = 0;
                RowData *rowdata = 0;

                HRESULT parse = rs.MoveFirst();

                while (S_OK == parse)
				{
                    CAtlList< RowData * > * rowList = new CAtlList<RowData *>;
                    if (0 == rowList)
					{
						SLSException ex("rowList = 0", SLSException::DOInitError, __FILE__, __LINE__);
                        //TraceThrow(SLSException, ex);
                    }

                    for (ULONG field = 0; field < fields; field++)
					{
                        BindObject *bobj = dynamic_cast<BindObject *>(bind.m_p + field);
                        if (0 == bobj)
						{
							SLSException ex("bobj = 0", SLSException::DOInitError, __FILE__, __LINE__);
                            //TraceThrow(SLSException, ex);
                        }

                        rowdata = (DBSTATUS_S_ISNULL == bobj->m_status) ? new RowData(L"", DBSTATUS_S_ISNULL) : new RowData(bobj->m_value);
                        
                        if (0 == rowdata)
						{
							SLSException ex("rowdata == 0", SLSException::DOInitError, __FILE__, __LINE__);
                            //TraceThrow(SLSException, ex);
                        }
                        rowList->AddTail(rowdata);
                    }// end for(..;field < fields;..)

                    resultSet->SetAtGrow( itemcnt, rowList );
                    ++itemcnt;
                    parse = rs.MoveNext();

					Sleep(10);

                }// end while(S_OK == parse)

                ++m_resultSets;
            } //end if (rs.m_spRowset != 0)

            DBROWCOUNT rowsAff = 0;
            hr = rs.GetNextResult(&rowsAff, false);
            if (pWatcher) pWatcher->m_hr = hr;

            getErrorInfoMessages(rs.m_spCommand, pWatcher);

			Sleep(10);

        } // end while(S_OK == hr)

        rs.Close();

    }
    catch (SLSException & /*excp*/)
	{
       // TraceCatch(SLSException, excp);
        //TraceError(_T("SLSException: %S"), excp.what());
        hr = E_FAIL;
    }
    catch (runtime_error & /*re*/)
	{
        //TraceCatch(runtime_error, re);
       // TraceError(L"runtime_error: %S\n", re.what());
        hr = E_FAIL;
    }
    catch (...)
	{
        //TraceCatchAll();
        hr = E_FAIL;
    }

    return(hr);
}

void RowColumnInfo::clear()
{
    //TraceVoidCallQuietly(LSMAIN, RowColumnInfo::clear);
    try {
        for (unsigned long set = 0; set < m_resultSets; set++) {
            CAtlArray < CAtlList < RowData * > * > * resultSet = m_data[ set ];
            unsigned long rowcount = (unsigned long) resultSet->GetCount();
            //TraceInfo(L"ResultSet %d (%d rows) cleared", set, rowcount);
            for (DBCOUNTITEM cnt = 0; cnt < rowcount; cnt++) {
                CAtlList < RowData * > * rowList = resultSet->GetAt( cnt );
                for (POSITION pos = rowList->GetHeadPosition(); 0 != pos;) {
                    delete rowList->GetNext(pos);
                }

                rowList->RemoveAll();
                delete rowList;
            }

            resultSet->RemoveAll();
            delete resultSet;
        }

        m_data.RemoveAll();

        for (unsigned long set = 0; set < m_resultSets; set++) {
            CoTaskMemFree(m_dbcolinfo[set]);
            CoTaskMemFree(m_strings[set]);
        }

        m_dbcolinfo.RemoveAll();
        m_strings.RemoveAll();

        m_resultSets = 0;
    }
    catch (...) {
        //TraceCatchAll();
    }
}

bool RowColumnInfo::getErrorInfoMessages(IUnknown *unknown, COutputWatcher* pWatcher) 
{
    //TraceCallQuietly(LSMAIN, RowColumnInfo::getErrorInfoMessages, bool);
    bool ret = false;

    try {
        // Parse through the error record set.
        CDBErrorInfo errInfo;
        ULONG records = 0;
        HRESULT hr = errInfo.GetErrorRecords(unknown, IID_ICommandPrepare, &records);
        if (SUCCEEDED(hr) && records) {
            //TraceInfo(L"RecordCount:%d", records);

            LCID lcid = GetUserDefaultLCID();

            for (ULONG count =0; count <records; count++) {
                CAutoPtr<RCErrorInfo> info(new RCErrorInfo());
                RCErrorInfo* inf = info.m_p;

                //
                // Get the error information from the source
                //
                hr = errInfo.GetAllErrorInfo(count, lcid, &inf->m_description,
                                             &inf->m_source, &inf->m_guid, &inf->m_helpContext,
                                             &inf->m_helpFile);

                if (SUCCEEDED(hr)) {
                    CAtlString sMsg(inf->m_description);
                    //TraceInfo(_T("Status/Info/Error Msg='%s'"), (LPCTSTR) sMsg);
                    if (pWatcher) pWatcher->ProcessMessage(sMsg);
                }
                else {
                    //TraceInfo(L"Error in GetAllErrorInfo at count : %lu, err : %ld\n", count, hr);
                }
            }

            ret = true;
        }
    }
    catch (...) {
        //TraceCatchAll();
    }

    return ret;
}

void COutputWatcher::ProcessMessage(CAtlString & sMsg)
{
    if (!sMsg.IsEmpty()) {
        m_sMsg += sMsg;
        m_sMsg += _T("\n");
    }
}
