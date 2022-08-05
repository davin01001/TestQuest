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
	public class TableItem
	{
		#region Properties

		private string _name;
		public string Name
		{
			get { return _name; }
			set { _name = value; }
		}

		private DBItem _db;
		public DBItem DB
		{
			get { return _db; }
		}

		private DataSet _ds = null;
		public DataSet DS
		{
			get
			{
				if (_ds != null)
					return _ds;

				_ds = new DataSet(_name + "DS");
				SqlConnection connection = new SqlConnection(_db.ConnectionString);
				try
				{
					connection.Open();

					SqlDataAdapter daTable = new SqlDataAdapter("SELECT TOP 10 * FROM " + _name, connection);
					daTable.Fill(_ds, _name);
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
				return _ds;
			}
		}

		private List<FieldItem> _dropFields = new List<FieldItem>();
		private List<FieldItem> _createdFields = new List<FieldItem>();

		private List<FieldItem> _fields = null;
		public List<FieldItem> Fields
		{
			get
			{
				if (_fields != null)
					return _fields;

				_fields = new List<FieldItem>();
				foreach (DataColumn dc in DS.Tables[_name].Columns)
				{
					string name = dc.ColumnName;
					string t = dc.DataType.ToString();
					_fields.Add(new FieldItem(name, t));
				}

				return _fields;
			}
		}

		public string FieldsData
		{
			get
			{
				string fd = "(";
				foreach (FieldItem fi in _createdFields)
				{
					if (fd != "(") fd += ",";
					fd += fi.Name + " " + fi.FieldType;
				}
				fd += ");";
				return fd;
			}
		}

		public List<string> ChangeData
		{
			get
			{
				List<string> chd = new List<string>();
				foreach (FieldItem fi in _dropFields)
				{
					chd.Add("ALTER TABLE " + _name + " DROP COLUMN " + fi.Name);
				}
				foreach (FieldItem fi in _createdFields)
				{
					chd.Add("ALTER TABLE " + _name + " ADD " + fi.Name + " " + fi.FieldType);
				}
				return chd;
			}
		}

		#endregion

		public TableItem(DBItem db, string name)
		{
			_db = db;
			_name = name;
		}

		public void ClearData()
		{
			_createdFields.Clear();
			_dropFields.Clear();
			_ds = null;
			_fields = null;
		}

		public void AddField(FieldItem fi)
		{
			_createdFields.Add(fi);
		}

		public void DeleteField(FieldItem fi)
		{
			if (_createdFields.Contains(fi))
				_createdFields.Remove(fi);
			else
				_dropFields.Add(fi);
		}
	}
}
