#include "StdAfx.h"

#include "DataBases.h"

STDAPI GetBases(LPCWSTR pszDataSource, LPCWSTR pszLogin, LPCWSTR pszPassword, LPWSTR basesStr)
{
	list<wstring> bases = DataBases::It().GetBases(pszDataSource, pszLogin, pszPassword);

	auto pos = 0;
    for (auto it = bases.begin(); it != bases.end(); it++)
		if (pos + it->length() < 255)
		{
			wcscpy_s(basesStr + pos, 255 - pos, it->c_str()); pos += it->length();
			wcscpy_s(basesStr + pos, 255 - pos, L";"); pos++;
		}

	return S_OK;
}
