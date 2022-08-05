#region Namespaces

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using TestQuest.DB;

#endregion

namespace TestQuest
{
	public partial class MainForm : Form
	{
		private DataBases _databases = new DataBases();

		public MainForm()
		{
			InitializeComponent();

			dataSourceTextBox.Text = _databases.DataSource;
			userTextBox.Text = _databases.Login;
			passwordTextBox.Text = _databases.Password;
			UpdateTree();
		}

		// пересобрать дерево баз/таблиц
		public void UpdateTree()
		{
			TreeNode node, tnode;

			DBTree.Nodes.Clear();
			foreach (DBItem db in _databases.Bases)
			{
				node = DBTree.Nodes.Add(db.Name);
				node.Tag = db;
				foreach (TableItem ti in db.Tables)
				{
					tnode = node.Nodes.Add(ti.Name);
					tnode.Tag = ti;
				}
			}
		}

		#region Event handlers

		// добавление таблицы
		private void addTableToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (DBTree.SelectedNode.Tag is DBItem)
			{
				DBItem db = (DBTree.SelectedNode.Tag as DBItem);
				using (TableForm form = new TableForm(true, null, db))
				{
					DialogResult result = form.ShowDialog(this);
					if (result == DialogResult.OK)
						using (SetNameForm snform = new SetNameForm())
						{
							DialogResult snresult = snform.ShowDialog(this);
							if (result == DialogResult.OK)
							{
								TableItem table = form.Table;
								table.Name = snform.nameTextBox.Text;
								db.AddTable(table);
								UpdateTree();
							}
						}
				}
			}
		}

		// удаление таблицы
		private void deleteTableToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (DBTree.SelectedNode.Tag is TableItem)
			{
				TableItem table = (DBTree.SelectedNode.Tag as TableItem);

				if (DialogResult.Yes == MessageBox.Show("Do you want to delete table " + table.Name + "?", "Warning", MessageBoxButtons.YesNo))
				{
					DBItem db = table.DB;
					db.DeleteTable(table);
					UpdateTree();
				}
			}
		}

		// редактирование полей таблицы
		private void editTableFieldsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			if (DBTree.SelectedNode.Tag is TableItem)
			{
				TableItem table = (DBTree.SelectedNode.Tag as TableItem);

				using (TableForm form = new TableForm(false, table))
				{
					form.ShowDialog(this);
					DBItem db = table.DB;
					db.UpdateTable(table);
				}
			}
		}

		// показать первые 10 записей БД
		private void DBTree_AfterSelect(object sender, TreeViewEventArgs e)
		{
			DBGrid.DataSource = null;
			DBGrid.DataMember = null;

			if (DBTree.SelectedNode.Tag is TableItem)
			{
				TableItem table = (DBTree.SelectedNode.Tag as TableItem);
				DBGrid.DataSource = table.DS;
				DBGrid.DataMember = table.Name;
			}
		}

		// обновить дерево по новым данным
		private void updateButton_Click(object sender, EventArgs e)
		{
			_databases.DataSource = dataSourceTextBox.Text;
			_databases.Login = userTextBox.Text;
			_databases.Password = passwordTextBox.Text;
			_databases.Update();
			UpdateTree();
		}

		// enable/disable элементов контекстного меню
		private void tableContextMenu_Opening(object sender, CancelEventArgs e)
		{
			if (DBTree.SelectedNode.Tag is DBItem)
			{
				addTableToolStripMenuItem.Enabled = true;
				deleteTableToolStripMenuItem.Enabled = false;
				editTableFieldsToolStripMenuItem.Enabled = false;
			}
			else
			{
				addTableToolStripMenuItem.Enabled = false;
				deleteTableToolStripMenuItem.Enabled = true;
				editTableFieldsToolStripMenuItem.Enabled = true;
			}
		}

		#endregion
	}
}
