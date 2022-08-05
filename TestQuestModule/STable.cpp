#include "stdafx.h"

#include "STable.h"

//#include <irrxml\irrXML.h>
//using namespace irr;
//using namespace io;

CSTable::CSTable()
       : m_bTableIsOpen(false)
{
}

CSTable::~CSTable()
{
}

void CSTable::ClearData()
{
    for (size_t i = 0; i < m_arrayRows.GetCount(); ++i) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[i];
        delete pRow;
    }
    m_arrayRows.RemoveAll();
}


void CSTable::ClearAll()
{
    ClearData();
    m_arrayColNames.RemoveAll();
}


size_t CSTable::GetColumnCount()
{
    return m_arrayColNames.GetCount();
}


size_t CSTable::GetRowCount()
{
    return m_arrayRows.GetCount();
}


const TCHAR* CSTable::GetTablename()
{
    return (const TCHAR*) m_sTableName;
}


const CAtlString& CSTable::GetRowElement(size_t nRow, size_t nCol)
{
    if (nRow < GetRowCount() && nCol < GetColumnCount()) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[nRow];
        return (*pRow)[nCol];
    }
    return m_sNull;
}

bool CSTable::SetRowElement(size_t nRow, size_t nCol, const TCHAR* pElement)
{
    if (pElement && nRow < GetRowCount() && nCol < GetColumnCount()) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[nRow];
        (*pRow)[nCol] = pElement;
        return true;
    }
    return false;
}

bool CSTable::SetColumnName(size_t nCol, const TCHAR* pColName)
{
    if (pColName && nCol < GetColumnCount()) {
        m_arrayColNames[nCol] = pColName;
        return true;
    }
    return false;
}

const CAtlString& CSTable::GetColumnName(size_t nCol)
{
    if (nCol < GetColumnCount()) {
        return m_arrayColNames[nCol];
    }
    return m_sNull;
}


size_t CSTable::FindColumn(const TCHAR* pColName)
{
    size_t nCol((size_t)-1);
    if (pColName) {
        for (size_t i = 0; i < GetColumnCount(); ++i) {
            if (GetColumnName(i) == pColName) {
                nCol = i;
                break;
            }
        }
    }
    return nCol;
}


bool CSTable::Begin(const TCHAR* pTableName/*=0*/)
{
    // do not ClearAll()!- This class supports appending table sets.
    // clearing should be done explicitly if current table should be wiped
    if (pTableName) m_sTableName = pTableName;
    else            m_sTableName.Empty();
    m_bTableIsOpen = true;

    return true;
}

bool CSTable::End()
{
    m_bTableIsOpen = false;
    return true;
}

bool CSTable::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    bool brc(false);
    if (arrayNames.GetCount()) {
        if (GetColumnCount() == 0) {
            m_arrayColNames.Append(arrayNames);
            brc = true;
        }
        else if (arrayNames.GetCount() == GetColumnCount()) {
            // Perhaps check that incoming columns matches current table
            brc = true;
        }
    }
    m_bTableIsOpen = brc;
    return brc;
}

bool CSTable::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    bool brc(false);
    if (m_bTableIsOpen) {
        size_t colcount = arrayValues.GetCount();
        if (colcount && (colcount == GetColumnCount())) {
            CAtlArray<CAtlString>* pRow = new CAtlArray<CAtlString>;
            pRow->SetCount(colcount);
            for (size_t i = 0; i < colcount; ++i) {
                pRow->SetAt(i, arrayValues[i]);
            }
            m_arrayRows.Add(pRow);
            brc = true;
        }
    }
    return brc;
}

bool CSTable::Export(ISTableSink& sink)
{
    bool brc(false);
    if (GetColumnCount()) {
        sink.Begin(GetTablename());
        sink.SetColumns(m_arrayColNames);
        for (size_t i = 0; i < GetRowCount(); ++i)  {
            sink.AddRowSet(*(m_arrayRows[i]));
        }
        sink.End();
        brc = true;
    }
    return brc;
}



// ------------------------------------------------------------------------------------------
//
// class CResultSet
//
// ------------------------------------------------------------------------------------------
bool CResultSet::Export(const TCHAR* /*sResultsXML*/, ISTableSink& /*sink*/)
{
    bool brc(false);
//
//    CMarkup xml;
//    if (! xml.SetDoc(sResultsXML)) return(false);
//
//    // Get the Info Messages
//    if (xml.FindElem(_T("MESSAGES"))) {
//        xml.IntoElem();
//        if (xml.FindElem(_T("ResultSet"))) {
//            CAtlString sResultSet = xml.GetData();
//            xml.SetDoc(sResultSet);
//        }
//    }
//
//    if (xml.FindElem(_T("TABLES"))) xml.IntoElem(); // optional (If multi, includes only the first)
//    brc = Export(xml, sink);
    return brc;
}


bool CResultSet::Export(CMarkup& /*xml*/, ISTableSink& /*sink*/)
{
    bool brc(false);
//
//    // NOTE! xml must be prepositioned such that find of TABLE will succeed
//    if (!xml.FindElem(_T("TABLE"))) return(false);
//
//    CAtlString sTableName = xml.GetAttrib(_T("name"));
//    sink.Begin(sTableName);
//
//    if (xml.IntoElem()) {
//        if (xml.FindElem(_T("COLUMNS"))) {
//            CAtlArray<CAtlString> arrayColumns;
//            while (xml.FindChildElem(L"COLUMN")) {
//                arrayColumns.Add(xml.GetChildData());
//            }
//            sink.SetColumns(arrayColumns);
//            brc = true;
//
//            if (!xml.FindElem(L"ROWS")) return(false);
//            if (xml.IntoElem()) {
//                CAtlArray<CAtlString> arrayValues;
//                while (xml.FindElem(L"ROW")) {
//                    arrayValues.RemoveAll();
//                    while (xml.FindChildElem(L"COLUMN")) {
//                        arrayValues.Add(xml.GetChildData());
//                    }
//                    sink.AddRowSet(arrayValues);
//                }
//                xml.OutOfElem();
//            }
//        }
//        xml.OutOfElem();
//    }
//    sink.End();
//
    return brc;
}


void CResultSet::SetResultSet(const TCHAR* sResultSet)
{
    m_sResultSet = sResultSet;
}


const CAtlString& CResultSet::GetResultSet()
{
    return m_sResultSet;
}


bool CResultSet::Export(ISTableSink& sink)
{
    return Export(m_sResultSet, sink);
}


bool CResultSet::Begin(const TCHAR* pTableName/*=0*/)
{
    if (pTableName && *pTableName) {
        CAtlString sTableName(pTableName);
        EscapeText(sTableName, true);
        m_sResultSet.Format(_T("<TABLE name='%s'>"), (const TCHAR*) sTableName);
    }
    else m_sResultSet=_T("<TABLE>");

    return true;
}


bool CResultSet::End()
{
    m_sResultSet+=_T("</ROWS>");
    m_sResultSet+=_T("</TABLE>");
    return true;
}


bool CResultSet::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    m_sResultSet += _T("<COLUMNS>");
    CAtlString sValue;
    for (size_t i = 0; i < arrayNames.GetCount(); ++i) {
        sValue = arrayNames.GetAt(i);
        EscapeText(sValue);
        m_sResultSet += _T("<COLUMN>");
        m_sResultSet += (const TCHAR*) sValue;
        m_sResultSet += _T("</COLUMN>");
    }
    m_sResultSet+=_T("</COLUMNS>");
    m_sResultSet+=_T("<ROWS>");
    return true;
}


bool CResultSet::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    m_sResultSet+=_T("<ROW>");
    CAtlString sValue;
    for (size_t i = 0; i < arrayValues.GetCount(); ++i) {
        sValue = arrayValues.GetAt(i);
        EscapeText(sValue);
        m_sResultSet += _T("<COLUMN>");
        m_sResultSet += (const TCHAR*) sValue;
        m_sResultSet += _T("</COLUMN>");
    }

    m_sResultSet+=_T("</ROW>");
    return true;
}

unsigned CResultSet::EscapeText(CAtlString& sText, bool bAttrib/*=false*/) 
{
    unsigned count(0);
    count += sText.Replace(_T("&"), _T("&amp;"));
    count += sText.Replace(_T("<"), _T("&lt;"));
    count += sText.Replace(_T(">"), _T("&gt;"));
    if (bAttrib) {
        count += sText.Replace(_T("'"),  _T("&apos;"));
        count += sText.Replace(_T("\""), _T("&quot;"));
    }
    return(count);
}

// ------------------------------------------------------------------------------------------
//
// class CFileResultSet
//
// ------------------------------------------------------------------------------------------
void CFileResultSet::UseFile(const TCHAR* pszFileName)
{
    m_sFileName = pszFileName;
}

bool CFileResultSet::Export(const wchar_t* pwszFile, ISTableSink& sink)
{
    CAtlStringA sFile(pwszFile);
    return Export(sFile, sink);
}

bool CFileResultSet::Export(const char* /*pszFile*/, ISTableSink& /*sink*/)
{
    bool brc(false);
//
//    IrrXMLReaderUTF16* xml = createIrrXMLReaderUTF16(pszFile);
//    if (xml) {
//        CAtlStringW s, sTableName, sValue;;
//        bool bTableFound(false);
//        while (xml->read()) {
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"TABLE") {
//                    sTableName = (wchar_t *) xml->getAttributeValue(L"name");
//                    bTableFound = true;
//                    break;
//                }
//            }
//        }
//        if (bTableFound) {
//            CAtlArray<CAtlString> arrayColumns;
//            sink.Begin(sTableName);
//
//header_columns:
//            if (!xml->read()) goto fail;
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"COLUMNS") goto header_column;
//            }
//            goto header_columns;
//
//header_column:
//            if (!xml->read()) goto fail;
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"COLUMN") goto header_column;
//            }
//            if (xml->getNodeType() == EXN_ELEMENT_END) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"COLUMN") goto header_column;
//                if (s == L"COLUMNS") {
//                    sink.SetColumns(arrayColumns);
//                    goto rows;
//                }
//            }
//            if (xml->getNodeType() == EXN_TEXT) {
//                s = (wchar_t *)xml->getNodeData();
//                arrayColumns.Add(s);
//                goto header_column;;
//            }
//            goto header_column;
//
//rows:
//            if (!xml->read()) goto fail;
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"ROWS") {
//                    if (xml->isEmptyElement()) goto done;
//                    goto row;
//                }
//            }
//            goto rows;
//
//row:
//            if (!xml->read()) goto fail;
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"ROW") {
//                    if (xml->isEmptyElement()) goto row;
//                    arrayColumns.RemoveAll();
//                    goto row_column;
//                }
//            }
//            if (xml->getNodeType() == EXN_ELEMENT_END) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"ROWS") {
//                    goto done;
//                }
//            }
//            goto row;
//
//row_column:
//            if (!xml->read()) goto fail;
//            if (xml->getNodeType() == EXN_ELEMENT) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"COLUMN") {
//                    sValue.Empty();
//                    if (xml->isEmptyElement()) arrayColumns.Add(s);
//                    goto row_column;
//                }
//            }
//            if (xml->getNodeType() == EXN_ELEMENT_END) {
//                s = (wchar_t *)xml->getNodeName();
//                if (s == L"COLUMN") {
//                    arrayColumns.Add(sValue);
//                    goto row_column;
//                }
//                if (s == L"ROW") {
//                    sink.AddRowSet(arrayColumns);
//                    goto row;
//                }
//            }
//            if (xml->getNodeType() == EXN_TEXT) {
//                sValue = (wchar_t *)xml->getNodeData();
//                goto row_column;
//            }
//            goto row_column;
//
//done:
//            brc = true;
//fail:
//            sink.End();
//        }
//        delete xml;
//    }
//
    return brc;
}


bool CFileResultSet::Export(ISTableSink& sink)
{
    bool brc = Export(m_sFileName, sink);
    m_err = brc ? 0 : 10502 /*E_DISK_READ_ERROR*/;
    return brc;
}


bool CFileResultSet::Begin(const TCHAR* pTableName/*=0*/)
{
    bool brc(false);
    m_err = 0;
    if (!m_fp) {
        //m_fp = _wfopen(m_sFileName, L"w,ccs=UTF-16LE");
        _wfopen_s(&m_fp, m_sFileName, L"w");
        if (!m_fp) m_err = 11501 /*E_OPEN_FILE_FAILED*/;
        else {
            // Write BOM if needed
            unsigned char szBOM[] = { 0xff, 0xfe };
            size_t wlen = fwrite(szBOM, sizeof(szBOM), 1, m_fp);
            brc = (wlen == 1);

            if (brc) {
                CAtlString s;
                if (pTableName && *pTableName) {
                    CAtlString sTableName(pTableName);
                    EscapeText(sTableName, true);
                    s.Format(_T("<TABLE name='%s'>"), (const TCHAR*) sTableName);
                }
                else s = _T("<TABLE>");


                size_t wlen = fwrite((const TCHAR*) s, sizeof(TCHAR), s.GetLength(), m_fp);
                brc = (wlen == (size_t)s.GetLength());
            }
            if (!brc) m_err = 10501 /*E_DISK_WRITE_ERROR*/;
        }
    }
    return brc;
}

bool CFileResultSet::End()
{
    bool brc(false);
    if (m_fp) {
        CAtlString s(_T("</ROWS></TABLE>"));
        size_t wlen = fwrite((const TCHAR*) s, sizeof(TCHAR), s.GetLength(), m_fp);
        brc = (wlen == (size_t)s.GetLength());
        if (fclose(m_fp) == EOF) brc = false;
        m_fp = 0;
    }
    if (!brc) m_err = 10501 /*E_DISK_WRITE_ERROR*/;
    return brc;
}

bool CFileResultSet::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    bool brc(false);
    if (m_fp) {
        CAtlString s;
        s += _T("<COLUMNS>");
        CAtlString sValue;
        for (size_t i = 0; i < arrayNames.GetCount(); ++i) {
            sValue = arrayNames.GetAt(i);
            EscapeText(sValue);
            s += _T("<COLUMN>");
            s += (const TCHAR*) sValue;
            s += _T("</COLUMN>");
        }
        s+=_T("</COLUMNS>");
        s+=_T("<ROWS>");
        size_t wlen = fwrite((const TCHAR*) s, sizeof(TCHAR), s.GetLength(), m_fp);
        brc = (wlen == (size_t)s.GetLength());
    }
    if (!brc) m_err = 10501 /*E_DISK_WRITE_ERROR*/;
    return brc;
}


bool CFileResultSet::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    bool brc(false);
    if (m_fp) {
        CAtlString s;
        s+=_T("<ROW>");
        CAtlString sValue;
        for (size_t i = 0; i < arrayValues.GetCount(); ++i) {
            sValue = arrayValues.GetAt(i);
            EscapeText(sValue);
            s += _T("<COLUMN>");
            s += (const TCHAR*) sValue;
            s += _T("</COLUMN>");
        }

        s+=_T("</ROW>");
        size_t wlen = fwrite((const TCHAR*) s, sizeof(TCHAR), s.GetLength(), m_fp);
        brc = (wlen == (size_t)s.GetLength());
    }
    if (!brc) m_err = 10501 /*E_DISK_WRITE_ERROR*/;
    return brc;
}

unsigned CFileResultSet::EscapeText(CAtlString& sText, bool bAttrib/*=false*/) 
{
    unsigned count(0);
    count += sText.Replace(_T("&"), _T("&amp;"));
    count += sText.Replace(_T("<"), _T("&lt;"));
    count += sText.Replace(_T(">"), _T("&gt;"));
    if (bAttrib) {
        count += sText.Replace(_T("'"),  _T("&apos;"));
        count += sText.Replace(_T("\""), _T("&quot;"));
    }
    return(count);
}

// ------------------------------------------------------------------------------------------
//
// class CSTableTxtLog
//
// ------------------------------------------------------------------------------------------
CSTableTxtLog::CSTableTxtLog(unsigned uEvalRows)
               : m_uEvalRows(uEvalRows)
               , m_uRcvdRows(0)
               , m_uSentRows(0)
               , m_uFormattingFlags(0)
               , m_pFile(stdout)
               , m_bActive(false)
               , m_bFlushing(false)
{
}


CSTableTxtLog::~CSTableTxtLog()
{
    Clear();
    if (m_pFile != stdout) fclose(m_pFile);
}

bool CSTableTxtLog::SetFile(const wchar_t * pFileName)
{
    bool brc(false);
    if (!m_bActive && pFileName)
	{
        FILE * fp = nullptr;
		_wfopen_s(&fp, pFileName, L"a");
        if (fp)
		{
            m_pFile = fp;
            brc = true;
        }
    }
    return brc;
}


bool CSTableTxtLog::Begin(const TCHAR * /*pTableName*/ /*=0*/)
{
    if (m_bActive) return false;
    return m_bActive = true;
}


bool CSTableTxtLog::End()
{
    if (m_bActive) {
        if (!m_uSentRows) {
            Evaluate();
            DisplayHdr();
        }
        m_uRcvdRows = 0;
        m_uSentRows = 0;
        Clear();
        m_bActive = false;
    }
    return true;
}


bool CSTableTxtLog::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    bool brc(false);
    if (m_bActive && arrayNames.GetCount() && (m_arrayColNames.GetCount() == 0)) {
        m_arrayColNames.Append(arrayNames);
        brc = true;
    }
    return brc;
}


bool CSTableTxtLog::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    bool brc(false);
    size_t colcount = arrayValues.GetCount();
    if (m_bActive && colcount && (colcount == m_arrayColNames.GetCount())) {
        if (m_uRcvdRows < m_uEvalRows) {

            CAtlArray<CAtlString>* pRow = new CAtlArray<CAtlString>;
            pRow->Append(arrayValues);
            m_arrayRows.Add(pRow);

            if (++m_uRcvdRows == m_uEvalRows) {
                Evaluate();
                DisplayHdr();
            }
        }
        else {
            DisplayRow(arrayValues);
            ++m_uSentRows;
        }
        brc = true;
    }

    return brc;
}


bool CSTableTxtLog::Evaluate()
{
    size_t cols = m_arrayColNames.GetCount();
    m_arrayColumnWidths.SetCount(cols);
    for (size_t col = 0; col < cols; ++col) {
        m_arrayColumnWidths[col] = m_arrayColNames[col].GetLength();
    }
    size_t rows = m_arrayRows.GetCount();
    for (size_t row = 0; row < rows; ++row) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[row];
        for (size_t col = 0; col < cols; ++col) {
            int length = pRow->GetAt(col).GetLength();
            if (length > (int) m_arrayColumnWidths[col]) m_arrayColumnWidths[col] = length;
        }
    }
    return true;
}


bool CSTableTxtLog::DisplayHdr()
{
    DisplayRow(m_arrayColNames);

    CAtlArray<CAtlString> arraySep;
    arraySep.SetCount(m_arrayColNames.GetCount());
    DisplayRow(arraySep, _T('-'));

    size_t rows = m_arrayRows.GetCount();
    for (size_t row = 0; row < rows; ++row) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[row];
        if (pRow) {
            DisplayRow(*pRow);
            ++m_uSentRows;
        }
    }
    ClearEvalCache();

    return true;
}


bool CSTableTxtLog::DisplayRow(CAtlArray<CAtlString>& arrayValues, TCHAR cPad /*=_T(' ')*/)
{
    size_t cols = arrayValues.GetCount();
    for (size_t col = 0; col < cols; ++col) {
        CAtlString sField(arrayValues[col]);
        int fieldlen = m_arrayColumnWidths[col];
        if (sField.GetLength() > fieldlen) {
            if (m_uFormattingFlags & CD_TRUNCATE_FIELDS) sField.Truncate(fieldlen);
        }
        else {
            while (sField.GetLength() < fieldlen) sField += cPad;
        }
        if (col) _ftprintf(m_pFile, _T(" "));
        _ftprintf(m_pFile, _T("%s"), (const TCHAR*) sField);
    }
    _ftprintf(m_pFile, _T("\n"));
    if (m_bFlushing) fflush(m_pFile);
    return true;
}


void CSTableTxtLog::ClearEvalCache()
{
    for (size_t i = 0; i < m_arrayRows.GetCount(); ++i) {
        CAtlArray<CAtlString>* pRow = m_arrayRows[i];
        delete pRow;
    }
    m_arrayRows.RemoveAll();
}


void CSTableTxtLog::Clear()
{
    ClearEvalCache();
    m_arrayColNames.RemoveAll();
    m_arrayColumnWidths.RemoveAll();
}


// ------------------------------------------------------------------------------------------
//
// class CSTableCSVLog
//
// ------------------------------------------------------------------------------------------
CSTableCSVLog::CSTableCSVLog()
             : m_pFile(stdout)
{
}


CSTableCSVLog::~CSTableCSVLog()
{
    if (m_pFile != stdout) fclose(m_pFile);
}


bool CSTableCSVLog::SetFile(const TCHAR * pFileName)
{
    bool brc(false);
    if (pFileName)
	{
        FILE* fp = nullptr;
		_wfopen_s(&fp, pFileName, L"a");
        if (fp)
		{
            m_pFile = fp;
            brc = true;
        }
    }
    return brc;
}


bool CSTableCSVLog::DisplayRow(CAtlArray<CAtlString>& arrayValues)
{
    size_t cols = arrayValues.GetCount();
    for (size_t col = 0; col < cols; ++col) {
        CAtlString sField(arrayValues[col]);
        if (col) _ftprintf(m_pFile, _T(","));
        _ftprintf(m_pFile, _T("%s"), (const TCHAR*) sField);
    }
    _ftprintf(m_pFile, _T("\n"));
    return true;
}


// ------------------------------------------------------------------------------------------
//
// class CConsoleTupleDisplay
//
// ------------------------------------------------------------------------------------------
CConsoleTupleDisplay::CConsoleTupleDisplay()
               : m_uColumn0Width(0)
{
}

CConsoleTupleDisplay::~CConsoleTupleDisplay()
{
    Clear();
}

bool CConsoleTupleDisplay::Begin(const wchar_t * /*pTableName*/ /*=0*/)
{
    Clear();
    return true;
}

bool CConsoleTupleDisplay::End()
{
    return true;
}

bool CConsoleTupleDisplay::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    bool brc(false);
    if (arrayNames.GetCount() && (m_arrayColNames.GetCount() == 0)) {
        m_arrayColNames.Append(arrayNames);
        Evaluate();
        brc = true;
    }
    return brc;
}


bool CConsoleTupleDisplay::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    size_t colcount = arrayValues.GetCount();
    if (colcount && (colcount == m_arrayColNames.GetCount())) {
        for (size_t i = 0; i < m_arrayColNames.GetCount(); ++i) {
            CAtlString sName = m_arrayColNames[i];
            sName += _T(":");
            _tprintf(_T("%*.*s %s\n"), m_uColumn0Width+1, m_uColumn0Width+1, sName, arrayValues[i]);
        }
    }

    return true;
}


bool CConsoleTupleDisplay::Evaluate()
{
    m_uColumn0Width = 0;
    for (size_t i = 0; i < m_arrayColNames.GetCount(); ++i) {
        unsigned width = m_arrayColNames[i].GetLength();
        if (m_uColumn0Width < width) m_uColumn0Width = width;
    }

    return true;
}


void CConsoleTupleDisplay::Clear()
{
    m_arrayColNames.RemoveAll();
}


// ------------------------------------------------------------------------------------------
//
// class CDefinedTable
//
// ------------------------------------------------------------------------------------------
CDefinedTable::CDefinedTable()
             : m_nFilenumber(0)
{
}


bool CDefinedTable::Begin(const TCHAR* pTableName/*=0*/)
{
    TCHAR* pNewTableName = GetTableName();
    if (pNewTableName) pTableName = pNewTableName;
    return CSTable::Begin(pTableName);
}

bool CDefinedTable::SetColumns(CAtlArray<CAtlString>& arrayNames)
{
    // Determine index mappings
    CAtlArray<CAtlString> arrayDefinedNames;
    m_arrayMapIndex.RemoveAll();

    hdrColumn_t* m_pColumns = GetTableDef();
    for (hdrColumn_t* pColumn = &m_pColumns[0]; pColumn->wszColumnName; ++pColumn) {
        size_t index((size_t)-1);
        arrayDefinedNames.Add(pColumn->wszColumnName);
        if (pColumn->type == ColTypeData) {
            wchar_t* pwszMapTo = pColumn->wszMapTo ? pColumn->wszMapTo : pColumn->wszColumnName;
            for (size_t i = 0; i < arrayNames.GetCount(); ++i) {
                if (arrayNames[i].CompareNoCase(pwszMapTo) == 0) {
                    index = i;
                    break;
                }
            }
        }
        m_arrayMapIndex.Add(index);
    }

    return CSTable::SetColumns(arrayDefinedNames);
}


bool CDefinedTable::AddRowSet(CAtlArray<CAtlString>& arrayValues)
{
    CAtlArray<CAtlString> arrayTransform;
    hdrColumn_t* m_pColumns = GetTableDef();
    for (hdrColumn_t* pColumn = &m_pColumns[0]; pColumn->wszColumnName; ++pColumn) {
        CAtlString sValue;

        if (pColumn->type == ColTypeRowIndex) {
            sValue.Format(_T("%d"), GetRowCount());
        }
        else  if (pColumn->type == ColTypeFileNumber) {
            sValue.Format(_T("%d"), m_nFilenumber);
        }
        else if (pColumn->type == ColTypeData) {
            size_t mapIndex = m_arrayMapIndex[arrayTransform.GetCount()];
            if (mapIndex != -1) {
                sValue = arrayValues[mapIndex];
            }
            else {
                // Default
                if (pColumn->wszDefault) sValue = pColumn->wszDefault;
            }
        }
        arrayTransform.Add(sValue);
    }

    return CSTable::AddRowSet(arrayTransform);
}

TCHAR* CDefinedTable::GetTableName()
{
    return 0;
}
