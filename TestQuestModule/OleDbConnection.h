#pragma once

#include <atldbcli.h>
#include "RowColumnInfo.h"

class OleDbConnection
{
public:
    OleDbConnection(const wstring & sDataSource, const bool bTrusted, const wstring & sUserName, const wstring & sPassword,
                    const wstring & sAppName = L"", const wstring & sDatabaseName = L"") throw();
    virtual ~OleDbConnection() throw();

    inline CSession & getSession() throw()  { return (CSession&)m_dataConnection; }
    inline RowColumnInfo & getRci() throw() { return (*m_rci); }

    virtual bool Connect() throw();
    void Disconnect() throw();

    bool isConnected() { return !!m_dataConnection; };

    inline bool ExecTSql(const wstring & sTSql, const wstring & sDatabaseName = L"", COutputWatcher * pWatcher = nullptr) throw()
    {
        return ExecTSql(pWatcher, sTSql, sDatabaseName);
    }

private:
    OleDbConnection (const OleDbConnection&) throw();            // No copy constructor- the actual OLE connection is not shared
    OleDbConnection & operator=(const OleDbConnection&) throw(); // No assignment operator- the actual OLE connection is not shared

	std::wstring GetConnectionString();

    bool ExecTSql(COutputWatcher * pWatcher, const wstring & sTSql, const wstring & sDatabaseName = L"") throw();

private:
	std::wstring         m_sDataSource;
	std::wstring         m_sUserName;
	std::wstring         m_sPassword;
	std::wstring         m_sAppName;
	std::wstring         m_sDatabaseName;
	bool                 m_bTrusted;
	std::wstring         m_sConnectionString;
    ATL::CDataConnection m_dataConnection;
	unsigned int         m_dwConnectTimeout;
	unsigned int         m_dwConnectRetries;
	RowColumnInfo *      m_rci;

};
