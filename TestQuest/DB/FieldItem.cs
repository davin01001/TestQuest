#region Namespaces

using System;
using System.Collections.Generic;
using System.Text;

#endregion

namespace TestQuest.DB
{
	public class FieldItem
	{
		private string _name;
		public string Name
		{
			get { return _name; }
		}

		private string _type;
		public string FieldType
		{
			get { return _type; }
		}

		public FieldItem(string name, string t)
		{
			_name = name;
			_type = t;
		}

		public override string ToString()
		{
			return _name;
		}
	}
}
