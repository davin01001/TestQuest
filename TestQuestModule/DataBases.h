#pragma once

class DataBases
{
private:
	DataBases() {}
	~DataBases() {}

	wstring GetConnectionString(const wstring & sDataSource, const bool bTrusted, const wstring & sUserName, const wstring & sPassword, const wstring & sAppName = L"", const wstring & sDatabaseName = L"");

public:

	static DataBases & It() {
		static DataBases singletone;
		return singletone;
	}

	std::list<wstring> GetBases(const wstring & sDataSource, const wstring & sUserName, const wstring & sPassword);
};
