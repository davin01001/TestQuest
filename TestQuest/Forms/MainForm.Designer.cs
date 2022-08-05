namespace TestQuest
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.DBTree = new System.Windows.Forms.TreeView();
			this.tableContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.addTableToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.deleteTableToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.editTableFieldsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.DBGrid = new System.Windows.Forms.DataGridView();
			this.dataSourceTextBox = new System.Windows.Forms.TextBox();
			this.dataSourceLabel = new System.Windows.Forms.Label();
			this.userLabel = new System.Windows.Forms.Label();
			this.userTextBox = new System.Windows.Forms.TextBox();
			this.passwordLabel = new System.Windows.Forms.Label();
			this.passwordTextBox = new System.Windows.Forms.TextBox();
			this.updateButton = new System.Windows.Forms.Button();
			this.tableContextMenu.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.DBGrid)).BeginInit();
			this.SuspendLayout();
			// 
			// DBTree
			// 
			this.DBTree.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
			this.DBTree.ContextMenuStrip = this.tableContextMenu;
			this.DBTree.Location = new System.Drawing.Point(12, 51);
			this.DBTree.Name = "DBTree";
			this.DBTree.Size = new System.Drawing.Size(261, 299);
			this.DBTree.TabIndex = 0;
			this.DBTree.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.DBTree_AfterSelect);
			// 
			// tableContextMenu
			// 
			this.tableContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addTableToolStripMenuItem,
            this.deleteTableToolStripMenuItem,
            this.editTableFieldsToolStripMenuItem});
			this.tableContextMenu.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.VerticalStackWithOverflow;
			this.tableContextMenu.Name = "tableContextMenu";
			this.tableContextMenu.Size = new System.Drawing.Size(160, 92);
			this.tableContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.tableContextMenu_Opening);
			// 
			// addTableToolStripMenuItem
			// 
			this.addTableToolStripMenuItem.Name = "addTableToolStripMenuItem";
			this.addTableToolStripMenuItem.Size = new System.Drawing.Size(159, 22);
			this.addTableToolStripMenuItem.Text = "Add Table";
			this.addTableToolStripMenuItem.Click += new System.EventHandler(this.addTableToolStripMenuItem_Click);
			// 
			// deleteTableToolStripMenuItem
			// 
			this.deleteTableToolStripMenuItem.Name = "deleteTableToolStripMenuItem";
			this.deleteTableToolStripMenuItem.Size = new System.Drawing.Size(159, 22);
			this.deleteTableToolStripMenuItem.Text = "Delete Table";
			this.deleteTableToolStripMenuItem.Click += new System.EventHandler(this.deleteTableToolStripMenuItem_Click);
			// 
			// editTableFieldsToolStripMenuItem
			// 
			this.editTableFieldsToolStripMenuItem.Name = "editTableFieldsToolStripMenuItem";
			this.editTableFieldsToolStripMenuItem.Size = new System.Drawing.Size(159, 22);
			this.editTableFieldsToolStripMenuItem.Text = "Edit Table Fields";
			this.editTableFieldsToolStripMenuItem.Click += new System.EventHandler(this.editTableFieldsToolStripMenuItem_Click);
			// 
			// DBGrid
			// 
			this.DBGrid.AllowUserToAddRows = false;
			this.DBGrid.AllowUserToDeleteRows = false;
			this.DBGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.DBGrid.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.DBGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.DBGrid.Location = new System.Drawing.Point(279, 51);
			this.DBGrid.Name = "DBGrid";
			this.DBGrid.ReadOnly = true;
			this.DBGrid.Size = new System.Drawing.Size(373, 299);
			this.DBGrid.TabIndex = 1;
			// 
			// dataSourceTextBox
			// 
			this.dataSourceTextBox.Location = new System.Drawing.Point(12, 25);
			this.dataSourceTextBox.Name = "dataSourceTextBox";
			this.dataSourceTextBox.Size = new System.Drawing.Size(261, 20);
			this.dataSourceTextBox.TabIndex = 2;
			// 
			// dataSourceLabel
			// 
			this.dataSourceLabel.AutoSize = true;
			this.dataSourceLabel.Location = new System.Drawing.Point(9, 9);
			this.dataSourceLabel.Name = "dataSourceLabel";
			this.dataSourceLabel.Size = new System.Drawing.Size(67, 13);
			this.dataSourceLabel.TabIndex = 3;
			this.dataSourceLabel.Text = "Data Source";
			// 
			// userLabel
			// 
			this.userLabel.AutoSize = true;
			this.userLabel.Location = new System.Drawing.Point(276, 9);
			this.userLabel.Name = "userLabel";
			this.userLabel.Size = new System.Drawing.Size(29, 13);
			this.userLabel.TabIndex = 4;
			this.userLabel.Text = "User";
			// 
			// userTextBox
			// 
			this.userTextBox.Location = new System.Drawing.Point(279, 25);
			this.userTextBox.Name = "userTextBox";
			this.userTextBox.Size = new System.Drawing.Size(148, 20);
			this.userTextBox.TabIndex = 5;
			// 
			// passwordLabel
			// 
			this.passwordLabel.AutoSize = true;
			this.passwordLabel.Location = new System.Drawing.Point(430, 9);
			this.passwordLabel.Name = "passwordLabel";
			this.passwordLabel.Size = new System.Drawing.Size(53, 13);
			this.passwordLabel.TabIndex = 6;
			this.passwordLabel.Text = "Password";
			// 
			// passwordTextBox
			// 
			this.passwordTextBox.Location = new System.Drawing.Point(433, 25);
			this.passwordTextBox.Name = "passwordTextBox";
			this.passwordTextBox.Size = new System.Drawing.Size(138, 20);
			this.passwordTextBox.TabIndex = 7;
			this.passwordTextBox.UseSystemPasswordChar = true;
			// 
			// updateButton
			// 
			this.updateButton.Location = new System.Drawing.Point(577, 22);
			this.updateButton.Name = "updateButton";
			this.updateButton.Size = new System.Drawing.Size(75, 23);
			this.updateButton.TabIndex = 8;
			this.updateButton.Text = "Update";
			this.updateButton.UseVisualStyleBackColor = true;
			this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(664, 362);
			this.Controls.Add(this.updateButton);
			this.Controls.Add(this.passwordTextBox);
			this.Controls.Add(this.passwordLabel);
			this.Controls.Add(this.userTextBox);
			this.Controls.Add(this.userLabel);
			this.Controls.Add(this.dataSourceLabel);
			this.Controls.Add(this.dataSourceTextBox);
			this.Controls.Add(this.DBGrid);
			this.Controls.Add(this.DBTree);
			this.MinimumSize = new System.Drawing.Size(680, 400);
			this.Name = "MainForm";
			this.Text = "Test for Quest";
			this.tableContextMenu.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.DBGrid)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TreeView DBTree;
		private System.Windows.Forms.DataGridView DBGrid;
		private System.Windows.Forms.ContextMenuStrip tableContextMenu;
		private System.Windows.Forms.ToolStripMenuItem addTableToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem deleteTableToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem editTableFieldsToolStripMenuItem;
		private System.Windows.Forms.TextBox dataSourceTextBox;
		private System.Windows.Forms.Label dataSourceLabel;
		private System.Windows.Forms.Label userLabel;
		private System.Windows.Forms.TextBox userTextBox;
		private System.Windows.Forms.Label passwordLabel;
		private System.Windows.Forms.TextBox passwordTextBox;
		private System.Windows.Forms.Button updateButton;
	}
}

