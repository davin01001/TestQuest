namespace TestQuest
{
	partial class TableForm
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
			this.cancelButton = new System.Windows.Forms.Button();
			this.createButton = new System.Windows.Forms.Button();
			this.closeButton = new System.Windows.Forms.Button();
			this.addFieldButton = new System.Windows.Forms.Button();
			this.deleteFieldButton = new System.Windows.Forms.Button();
			this.listFields = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// cancelButton
			// 
			this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancelButton.Location = new System.Drawing.Point(410, 338);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(75, 23);
			this.cancelButton.TabIndex = 0;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			// 
			// createButton
			// 
			this.createButton.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.createButton.Location = new System.Drawing.Point(329, 338);
			this.createButton.Name = "createButton";
			this.createButton.Size = new System.Drawing.Size(75, 23);
			this.createButton.TabIndex = 1;
			this.createButton.Text = "Create";
			this.createButton.UseVisualStyleBackColor = true;
			// 
			// closeButton
			// 
			this.closeButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.closeButton.Location = new System.Drawing.Point(410, 338);
			this.closeButton.Name = "closeButton";
			this.closeButton.Size = new System.Drawing.Size(75, 23);
			this.closeButton.TabIndex = 2;
			this.closeButton.Text = "Close";
			this.closeButton.UseVisualStyleBackColor = true;
			// 
			// addFieldButton
			// 
			this.addFieldButton.Location = new System.Drawing.Point(410, 12);
			this.addFieldButton.Name = "addFieldButton";
			this.addFieldButton.Size = new System.Drawing.Size(75, 23);
			this.addFieldButton.TabIndex = 3;
			this.addFieldButton.Text = "Add Field";
			this.addFieldButton.UseVisualStyleBackColor = true;
			this.addFieldButton.Click += new System.EventHandler(this.addFieldButton_Click);
			// 
			// deleteFieldButton
			// 
			this.deleteFieldButton.Location = new System.Drawing.Point(410, 41);
			this.deleteFieldButton.Name = "deleteFieldButton";
			this.deleteFieldButton.Size = new System.Drawing.Size(75, 23);
			this.deleteFieldButton.TabIndex = 4;
			this.deleteFieldButton.Text = "Delete Field";
			this.deleteFieldButton.UseVisualStyleBackColor = true;
			this.deleteFieldButton.Click += new System.EventHandler(this.deleteFieldButton_Click);
			// 
			// listFields
			// 
			this.listFields.FormattingEnabled = true;
			this.listFields.Location = new System.Drawing.Point(12, 12);
			this.listFields.Name = "listFields";
			this.listFields.Size = new System.Drawing.Size(392, 316);
			this.listFields.TabIndex = 5;
			// 
			// TableForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(497, 373);
			this.Controls.Add(this.listFields);
			this.Controls.Add(this.deleteFieldButton);
			this.Controls.Add(this.addFieldButton);
			this.Controls.Add(this.closeButton);
			this.Controls.Add(this.createButton);
			this.Controls.Add(this.cancelButton);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "TableForm";
			this.Text = "Table Fields";
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button cancelButton;
		private System.Windows.Forms.Button createButton;
		private System.Windows.Forms.Button closeButton;
		private System.Windows.Forms.Button addFieldButton;
		private System.Windows.Forms.Button deleteFieldButton;
		private System.Windows.Forms.ListBox listFields;
	}
}