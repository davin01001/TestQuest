#include "stdafx.h"

#include "OleDbConnection.h"

OleDbConnection::OleDbConnection(const std::wstring & sDataSource, const bool bTrusted, const std::wstring & sUserName, const std::wstring & sPassword,
                                 const std::wstring & sAppName /*= L""*/, const std::wstring & sDatabaseName /*= L""*/)
               : m_sDataSource(sDataSource)
			   , m_bTrusted(bTrusted)
			   , m_sUserName(sUserName)
			   , m_sPassword(sPassword)
			   , m_sAppName(sAppName)
			   , m_sDatabaseName(sDatabaseName)
			   , m_dwConnectTimeout(15)
			   , m_dwConnectRetries(0)
               , m_rci(new RowColumnInfo())
{
	m_sConnectionString = GetConnectionString();
}

OleDbConnection::~OleDbConnection()
{
    try
	{
        m_dataConnection.CloseDataSource();
        delete m_rci;
    }
    catch (...)
	{
    }
}

std::wstring OleDbConnection::GetConnectionString()
{
	std::wstringstream ss;

	ss << L"Provider=SQLOLEDB;";
	if (m_bTrusted)
		ss << L"Integrated Security=SSPI;";
	ss << L"Data Source='" << m_sDataSource << "';";
	if (!m_bTrusted)
	{
		ss << L"User ID='" << m_sUserName << "';";
		ss << L"Password='" << m_sPassword << "';";
	}
	ss << L"Application Name='" << m_sAppName << "';";
	if (!m_sDatabaseName.empty())
		ss << L"database='" << m_sDatabaseName << "';";

	ss << L"Connect Timeout='" << m_dwConnectTimeout << "';";

	return ss.str();
}

bool OleDbConnection::Connect() throw()
{
    HRESULT hr = S_OK;
	unsigned int dwConnectRetries = m_dwConnectRetries;

	try
	{
		do
		{
			Disconnect();
			hr = m_dataConnection.Open(m_sConnectionString.c_str());
		}
		while (FAILED(hr) && dwConnectRetries--);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void OleDbConnection::Disconnect()
{
    try
	{
        m_dataConnection.CloseDataSource();
    }
    catch(...)
	{

    }
}

bool OleDbConnection::ExecTSql(COutputWatcher * pWatcher, const wstring & sTSql, const wstring & sDatabaseName /*= L""*/)
{
    HRESULT hr = E_UNEXPECTED;

	if (m_rci && !sTSql.empty())
	{
		std::wstringstream ssSql;
        if (!sDatabaseName.empty())
		{
			std::wstring sDB = sDatabaseName;
			size_t ind;
			while ((ind = sDB.find(L"]")) != std::wstring::npos)
				sDB.replace(ind, 1, L"]]");

            ssSql << L"USE [" << sDB << L"] ";
        }
		ssSql << sTSql;

		hr = m_rci->Execute(m_dataConnection, ssSql.str().c_str(), pWatcher);
    }

    return SUCCEEDED(hr);
}
