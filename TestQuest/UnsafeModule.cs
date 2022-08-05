using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace TestQuest
{
	static class UnsafeModule
	{
		const string _dllName = "TestQuestModule.dll";
		[DllImport(_dllName, CharSet = CharSet.Unicode)]
		public static extern int GetBases(string dataSource, string login, string password, [Out, MarshalAs(UnmanagedType.LPWStr)] StringBuilder bases);
	}
}
