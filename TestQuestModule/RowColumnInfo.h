#pragma once

#include "STable.h"

class COutputWatcher
{
	friend class RowColumnInfo;

public:
	COutputWatcher() : m_hr(0) {}
	~COutputWatcher() {}
	virtual void ProcessMessage(CAtlString & sMsg);
	void GetMessages(CAtlString& sMsg) { sMsg = m_sMsg; }
	HRESULT GetResult()                { return m_hr;   }
	void Clear() { m_sMsg.Empty(); }

private:
	CAtlString m_sMsg;
	HRESULT    m_hr;
};

class RowData
{
public:
    /** Standard constructor.*/
    RowData(const wchar_t *data, const DWORD status = 0) throw() :m_data(data), m_status(status) {}
    virtual ~RowData() throw() {}

public:
    const CAtlStringW & getData()   const throw() { return m_data;   }
    DWORD               getStatus() const throw() { return m_status; }

private:
    CAtlStringW m_data;
    DWORD       m_status;
};

class RowColumnInfo : public ISTableSource
{
public:
    RowColumnInfo() throw() : m_rowcount(0), m_resultSets(0) {}
    virtual ~RowColumnInfo() throw()
    {
        clear();
    }

    HRESULT Execute(const CSession& session, const wchar_t *sql, COutputWatcher* pWatcher) throw();
    bool Export(ISTableSink& sink);

    // Get the number of columns (0-based).
    inline const unsigned long getNumColumns(unsigned long set = 0) const throw()
    {
        unsigned long cols = 0;

        if (set < m_resultSets)
		{
            if (0 < m_data.GetCount())
			{
                CAtlArray< CAtlList<RowData *> * > * tmpArr = m_data[set];

                if (tmpArr && (0 < tmpArr->GetCount()))
				{
                    CAtlList<RowData *> * tmpList = tmpArr->GetAt( 0 );
                    if (tmpList)
					{
                        cols = (unsigned long) tmpList->GetCount();
                    }
                }
            }
        }

        return cols;
    }

    /**
    * Get the column information.
    * @param colnum [in] column number (0-based).
    * @return the column info, 0 on error.
    * @exception none.
    */
    inline const DBCOLUMNINFO *getColumnInfo( unsigned long colnum,
                                              unsigned long set = 0
                                            ) throw()
    {
        DBCOLUMNINFO *colinfo = 0;
        if ( set < m_resultSets ) {
            unsigned long cols = getNumColumns( set );

            if ( colnum < cols ) {
                colinfo = m_dbcolinfo[set];
                colinfo = colinfo + colnum;
            }
        }

        return colinfo;
    }

    // Get the number of rows.
    inline const unsigned long getNumRows( unsigned long set = 0
                                         ) const throw()
    {
        unsigned long rowCount = 0;

        if ( set < m_resultSets) {
            if ( 0 < m_data.GetCount() ) {
                CAtlArray< CAtlList<RowData *> * > * tmpArr = m_data[set];

                if ( tmpArr ) {
                    rowCount = (unsigned long) tmpArr->GetCount();
                }
            }
        }

        return rowCount;
    }

    /**
    * Get the error message.
    * @param none.
    * @return the message buffer.
    * @exception none.
    */
    inline unsigned long getNumResultSets() const throw()
    {
        return m_resultSets;
    }

    /**
    * Get the row list.
    * @param rownum    [in]    0-based row number.
    * @return the list.
    * @exception none.
    */
    inline CAtlList<RowData *> *getRowData( unsigned long rownum,
                                            unsigned long set = 0
                                          ) throw()
    {
        CAtlList<RowData *> *ret = 0;

        if ( set < m_resultSets ) {
            unsigned long rowCount = getNumRows( set );
            if ( rownum < rowCount ) {
                ret = m_data[set]->GetAt( rownum );
            }
        }

        return ret;
    }

    /**
    * Get the column string.
    * @param row    [in]    the row (0-based).
    * @param col    [in]    the column (0-based).
    * @return the buffer.
    * @exception none.
    */
    inline const CAtlStringW getColumnString( unsigned long row, 
                                              unsigned long col,
                                              unsigned long set = 0
                                             ) throw()
    {
        //TraceCallQuietly(LSSQL, RowColumnInfo::getColumnString, CAtlStringW);
        CAtlStringW ret;

        try {
            const DBCOLUMNINFO *dbci = getColumnInfo(col, set);        // Check if column is valid
            if (dbci) {
                CAtlList<RowData *> *rd = getRowData((unsigned long) row, set);    // Check if row is valid
                if (rd) {
                    unsigned long count = 0;    // 0-based index
                    for (POSITION pos = rd->GetHeadPosition(); 0 != pos;) {
                        RowData *data = rd->GetNext(pos);
                        if (col == count++) {
                            ret = data->getData();        // found !!!
                            break;
                        }
                    }
                }
            }
        }
        catch(...)
        {
            // For SQL Server 7.0..
        }

        //TraceInfo((L"[%d,%d,%d]=%s", set, row, col, (const wchar_t *) ret));
        return ret;
    }

private:
    void clear() throw();
    bool getErrorInfoMessages(IUnknown *unknown, COutputWatcher* pWatcher) throw();

    CAtlArray< DBCOLUMNINFO * > m_dbcolinfo;                  /** The column information. */
    CAtlArray< LPOLESTR > m_strings;                          /** The helper for colinfo.*/
    unsigned long m_rowcount;                                 /** row count.*/
    unsigned long m_resultSets;                               /** num result sets.*/
    CAtlArray< CAtlArray< CAtlList<RowData *> * > * > m_data; /** The data list.*/

};
