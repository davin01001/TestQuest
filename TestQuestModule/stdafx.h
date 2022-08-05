#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atldbcli.h>
#include <atlcoll.h>

#include <string>
#include <sstream>
#include <list>
using namespace std;

#ifdef TESTQUESTMODULE_EXPORTS
#  define TESTQUESTMODULE_API __declspec(dllexport)
#else
#  define TESTQUESTMODULE_API __declspec(dllimport)
#endif