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
	public class DBItem
	{
		private DataBases _dbs;

		#region Properties

		private string _name;
		public string Name
		{
			get { return _name; }
			set { _name = value; }
		}

		public string ConnectionString
		{
			get
			{
				return "server=" + _dbs.DataSource + ";Integrated Security=SSPI;database=" + _name + ";User ID=" + _dbs.Login + ";Password=" + _dbs.Password;
			}
		}

		private List<TableItem> _tables = new List<TableItem>();
		public List<TableItem> Tables
		{
			get { return _tables; }
		}

		#endregion

		public DBItem(DataBases dbs, string name)
		{
			_dbs = dbs;
			_name = name;

			Update();
		}

		public void Update()
		{
			SqlConnection connection = new SqlConnection(ConnectionString);
			try
			{
				connection.Open();

				SqlCommand command = new SqlCommand("sp_tables", connection);
				command.CommandType = System.Data.CommandType.StoredProcedure;
				command.Parameters.AddWithValue("@table_type", "'TABLE'");

				SqlDataReader reader = command.ExecuteReader();
				if (reader.HasRows)
					while (reader.Read())
					{
						string tableName = reader.GetString(2);
						if (tableName.Length < 9 || tableName.Substring(0, 9) != "trace_xe_")
							_tables.Add(new TableItem(this, tableName));
					}
			}
			catch (SqlException ex)
			{
				MessageBox.Show(ex.Message);
			}
			finally
			{
				connection.Close();
				connection.Dispose();
			}
		}

		public void AddTable(TableItem table)
		{
			SqlConnection connection = new SqlConnection(ConnectionString);
			try
			{
				connection.Open();

				SqlCommand command = new SqlCommand("CREATE TABLE " + table.Name + table.FieldsData, connection);
				command.ExecuteNonQuery();

				table.ClearData();
				_tables.Add(table);
			}
			catch (SqlException ex)
			{
				MessageBox.Show(ex.Message);
			}
			finally
			{
				connection.Close();
				connection.Dispose();
			}
		}

		public void UpdateTable(TableItem table)
		{
			SqlConnection connection = new SqlConnection(ConnectionString);
			try
			{
				connection.Open();

				List<string> chd = table.ChangeData;

				SqlCommand command = new SqlCommand("", connection);
				foreach (string s in chd)
				{
					command.CommandText = s;
					command.ExecuteNonQuery();
				}

				table.ClearData();
			}
			catch (SqlException ex)
			{
				MessageBox.Show(ex.Message);
			}
			finally
			{
				connection.Close();
				connection.Dispose();
			}
		}

		public void DeleteTable(TableItem table)
		{
			SqlConnection connection = new SqlConnection(ConnectionString);
			try
			{
				connection.Open();

				SqlCommand command = new SqlCommand("DROP TABLE " + table.Name, connection);
				command.ExecuteNonQuery();

				_tables.Remove(table);
			}
			catch (SqlException ex)
			{
				MessageBox.Show(ex.Message);
			}
			finally
			{
				connection.Close();
				connection.Dispose();
			}
		}
	}
}
