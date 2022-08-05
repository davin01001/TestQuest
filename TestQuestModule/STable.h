#pragma once

class ISTableSink {
public:
    virtual bool Begin(const wchar_t * pTableName = 0)         = 0;
    virtual bool End()                                         = 0;
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames) = 0;
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues) = 0;
};

class ISTableSource {
public:
    virtual bool Export(ISTableSink& sink) = 0;
};

class CSTable : public ISTableSink, public ISTableSource
{
public:
    CSTable();
    virtual ~CSTable();

    virtual void ClearData();
    virtual void ClearAll();

    virtual const wchar_t * GetTablename();
    virtual size_t          GetColumnCount();
    virtual size_t          GetRowCount();

    virtual const CAtlString& GetRowElement(size_t nRow, size_t nCol);
    virtual const CAtlString& GetColumnName(size_t nCol);
    virtual bool SetRowElement(size_t nRow, size_t nCol, const TCHAR* pElement);
    virtual bool SetColumnName(size_t nCol, const TCHAR* pColName);
    virtual size_t            FindColumn(const TCHAR* pColName);

    virtual bool Begin(const TCHAR* pTableName=0);
    virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

    virtual bool Export(ISTableSink& sink);

protected:
    CAtlString                        m_sTableName;
    CAtlArray<CAtlString>             m_arrayColNames;
    CAtlArray<CAtlArray<CAtlString>*> m_arrayRows;
    CAtlString                        m_sNull;
    bool                              m_bTableIsOpen;
};


class CMarkup;
class CResultSet : public ISTableSink, public ISTableSource
{
public:
    CResultSet() {};
    virtual ~CResultSet() {};

    void              SetResultSet(const TCHAR* sResultSet);
    const CAtlString& GetResultSet();

    static bool Export(const TCHAR* sResultSet, ISTableSink& sink);
    static bool Export(CMarkup& xml, ISTableSink& sink);

    virtual bool Export(ISTableSink& sink);
    virtual bool Begin(const TCHAR* pTableName=0);
    virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

private:
    unsigned EscapeText(CAtlString& sText, bool bAttrib=false); 

    CAtlString m_sResultSet;
};

class CFileResultSet : public ISTableSink, public ISTableSource
{
public:
    CFileResultSet() : m_fp(0), m_err(0) {}
    CFileResultSet(const TCHAR* pszFileName) : m_fp(0), m_err(0) { UseFile(pszFileName); }
    virtual ~CFileResultSet() {};

    void              UseFile(const TCHAR* pszFileName);
    const CAtlString& GetFileName()  { return m_sFileName; }
    unsigned          LSResultCode() { return m_err; }

    static bool Export(const char* pszFile, ISTableSink& sink);
    static bool Export(const wchar_t* pwszFile, ISTableSink& sink);

    virtual bool Export(ISTableSink& sink);
    virtual bool Begin(const TCHAR* pTableName=0);
    virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

private:
    unsigned EscapeText(CAtlString& sText, bool bAttrib=false); 

    CAtlString m_sFileName;
    FILE*      m_fp;
    unsigned   m_err;
};


class CSTableTxtLog : public ISTableSink
{
public:
    CSTableTxtLog(unsigned uEvalRows);
    virtual ~CSTableTxtLog();

    bool SetFile(const TCHAR* pFileName);
    bool SetFlushing(bool bFlushing) { return m_bFlushing= bFlushing; }

    virtual bool Begin(const TCHAR* pTableName=0);
    virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

#define CD_TRUNCATE_FIELDS 0x01
    unsigned SetFormatting(unsigned uFlags) { return m_uFormattingFlags = uFlags; }
    unsigned GetFormatting()                { return m_uFormattingFlags; }

protected:
    bool Evaluate();
    bool DisplayHdr();
    bool DisplayRow(CAtlArray<CAtlString>& arrayValues, TCHAR cPad=_T(' '));
    void Clear();
    void ClearEvalCache();

private:
    unsigned                          m_uEvalRows,
                                      m_uRcvdRows,
                                      m_uSentRows,
                                      m_uFormattingFlags;
    CAtlArray<unsigned>               m_arrayColumnWidths;
    CAtlArray<CAtlString>             m_arrayColNames;
    CAtlArray<CAtlArray<CAtlString>*> m_arrayRows;
    FILE*                             m_pFile;
    bool                              m_bActive,
                                      m_bFlushing;
};

class CSTableCSVLog : public ISTableSink
{
public:
    CSTableCSVLog();
    virtual ~CSTableCSVLog();

    bool SetFile(const TCHAR* pFileName);

    virtual bool Begin(const TCHAR* /*pTableName*/=0)               { return true; }
    virtual bool End()                                          { return true; }
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames)  { return DisplayRow(arrayNames); }
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues)  { return DisplayRow(arrayValues); }

protected:
    bool DisplayRow(CAtlArray<CAtlString>& arrayValues);

private:
    FILE*  m_pFile;
};

class CConsoleTupleDisplay : public ISTableSink
{
public:
    CConsoleTupleDisplay();
    virtual ~CConsoleTupleDisplay();

    virtual bool Begin(const TCHAR* pTableName=0);
    virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

protected:
    bool Evaluate();
    void Clear();

private:
    unsigned                          m_uColumn0Width,
                                      m_uFormattingFlags;
    CAtlArray<CAtlString>             m_arrayColNames;
    CAtlArray<CAtlArray<CAtlString>*> m_arrayRows;
};

#define ColTypeData       0
#define ColTypeRowIndex   1
#define ColTypeFileNumber 2
struct hdrColumn_t
{
    wchar_t*       wszColumnName;
    wchar_t*       wszDefault;
    wchar_t*       wszMapTo;
    unsigned       type;
};


class CDefinedTable : public CSTable
{
public:
    CDefinedTable();
    virtual ~CDefinedTable() {};
    void SetFilenumber(int nFilenumber) { m_nFilenumber = nFilenumber; };

    virtual bool Begin(const TCHAR* pTableName=0);
    //virtual bool End();
    virtual bool SetColumns(CAtlArray<CAtlString>& arrayNames);
    virtual bool AddRowSet(CAtlArray<CAtlString>& arrayValues);

    virtual hdrColumn_t* GetTableDef() = 0;
    virtual TCHAR* GetTableName();

private:
    CAtlArray<size_t> m_arrayMapIndex;
    int               m_nFilenumber;
};
