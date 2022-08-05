#include "stdafx.h"

#include "DataBases.h"

wstring DataBases::GetConnectionString(const wstring & sDataSource, const bool bTrusted, const wstring & sUserName, const wstring & sPassword, const wstring & sAppName /*= L""*/, const wstring & sDatabaseName /*= L""*/)
{
	std::wstringstream ss;

	ss << L"Provider=SQLOLEDB;";
	if (bTrusted)
		ss << L"Integrated Security=SSPI;";
	ss << L"Data Source='" << sDataSource << "';";
	if (!bTrusted)
	{
		ss << L"User ID='" << sUserName << "';";
		ss << L"Password='" << sPassword << "';";
	}
	ss << L"Application Name='" << sAppName << "';";
	if (!sDatabaseName.empty())
		ss << L"database='" << sDatabaseName << "';";

	return ss.str();
}

CDataConnection m_dataConnection;

std::list<wstring> DataBases::GetBases(const wstring & sDataSource, const wstring & sUserName, const wstring & sPassword)
{
	HRESULT hr;
	list<wstring> bases;

	hr = ::CoInitialize(NULL);

	wstring connectionString = GetConnectionString(sDataSource, false, sUserName, sPassword);

	CDataSource ds;
	hr = ds.OpenFromInitializationString(connectionString.c_str());
	if (FAILED(hr))
		return bases;
	CSession session;
	hr = session.Open(ds);
	if (FAILED(hr))
		return bases;

	CCommand<CDynamicAccessor> cmd;
	hr = cmd.Open(session, L"EXEC sp_databases");
	if (hr == S_OK)
		if (cmd.MoveFirst() == S_OK)
			do
			{
				bases.push_back((wchar_t*)cmd.GetValue(1));
			}
			while (cmd.MoveNext() == S_OK);

	return bases;
}
