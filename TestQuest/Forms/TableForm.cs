#region Namespaces

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using TestQuest.DB;

#endregion

namespace TestQuest
{
	public partial class TableForm : Form
	{
		private bool _isNew = false;
		private DBItem _db = null;

		private TableItem _table = null;
		public TableItem Table
		{
			get { return _table; }
		}

		public TableForm(bool isNew = false, TableItem table = null, DBItem db = null)
		{
			InitializeComponent();

			_isNew = isNew;
			_table = table;
			_db = db;

			if (_isNew)
			{
				createButton.Visible = true;
				cancelButton.Visible = true;
				closeButton.Visible = false;
			}
			else
			{
				createButton.Visible = false;
				cancelButton.Visible = false;
				closeButton.Visible = true;
			}

			if (_table == null)
				_table = new TableItem(_db, "NewTable");
			else
			{
				foreach (FieldItem fi in _table.Fields)
					listFields.Items.Add(fi);
			}
		}

		private string GetTypeByName(string typeName)
		{
			switch (typeName)
			{
				case "Bool": return "tinyint";
				case "Int": return "int";
				case "Double": return "decimal";
				case "DateTime": return "datetime";
				case "String": return "text";
			}
			return "TEXT";
		}

		#region Event handlers

		private void addFieldButton_Click(object sender, EventArgs e)
		{
			using (AddFieldForm form = new AddFieldForm())
			{
				DialogResult result = form.ShowDialog(this);
				if (result == DialogResult.OK)
				{
					if (form.nameTextBox.Text.Length > 0 && form.typeComboBox.SelectedItem != null)
					{
						FieldItem fi = new FieldItem(form.nameTextBox.Text, GetTypeByName(form.typeComboBox.SelectedItem.ToString()));
						_table.AddField(fi);
						listFields.Items.Add(fi);
					}
				}
			}
		}

		private void deleteFieldButton_Click(object sender, EventArgs e)
		{
			if (listFields.SelectedItem is FieldItem)
			{
				FieldItem field = (listFields.SelectedItem as FieldItem);
				if (DialogResult.Yes == MessageBox.Show("Do you want to delete field " + field.Name + "?", "Warning", MessageBoxButtons.YesNo))
				{
					_table.DeleteField(field);
					listFields.Items.Remove(field);
				}
			}
		}

		#endregion
	}
}
