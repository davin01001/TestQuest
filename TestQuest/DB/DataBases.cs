#region Namespaces

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

#endregion

namespace TestQuest.DB
{
	public class DataBases
	{
		#region Properties

		private string _dataSource = @"DAVIN\SQLEXPRESS2012";
		public string DataSource
		{
			get { return _dataSource; }
			set { _dataSource = value; }
		}

		private string _login = "sa";
		public string Login
		{
			get { return _login; }
			set { _login = value; }
		}

		private string _password = "1";
		public string Password
		{
			get { return _password; }
			set { _password = value; }
		}

		public string ConnectionString
		{
			get { return "server=" + _dataSource + ";Integrated Security=SSPI;User ID=" + _login + ";Password=" + _password; }
		}

		private List<DBItem> _bases = new List<DBItem>();
		public List<DBItem> Bases
		{
			get { return _bases; }
		}

		#endregion

		public DataBases()
		{
			Update();
		}

		public void Update()
		{
			_bases.Clear();

			StringBuilder basesStr = new StringBuilder(255);
			UnsafeModule.GetBases(_dataSource, _login, _password, basesStr);
			string[] bases = basesStr.ToString().Split(new char[] { ';' });
			foreach (string b in bases)
				_bases.Add(new DBItem(this, b));
		}
	}
}
