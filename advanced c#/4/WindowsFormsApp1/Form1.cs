using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Dictionary<string, List<string>> two = new Dictionary<string, List<string>>();
        Dictionary<string, List<string>> three = new Dictionary<string, List<string>>();
        public Form1()
        {
            var watch1 = System.Diagnostics.Stopwatch.StartNew();
            string file = System.IO.File.ReadAllText(@"nazwiska.txt");
            watch1.Stop();
            time1 = watch1.ElapsedMilliseconds.ToString() + "ms";

            var watch2 = System.Diagnostics.Stopwatch.StartNew();
            foreach (string line in file.Split('\n'))
            {
                string name = line.Substring(line.IndexOf(" ") + 1);
                string name2 = name.Substring(0, 2).ToLower();
                if (!two.ContainsKey(name2))
                    two.Add(name2, new List<string>());
                two[name2].Add(name);
            }
            watch2.Stop();
            time2 = watch2.ElapsedMilliseconds.ToString() + "ms";

            var watch3 = System.Diagnostics.Stopwatch.StartNew();
            foreach (string line in file.Split('\n'))
            {
                string name = line.Substring(line.IndexOf(" ") + 1);
                string name3 = name.Substring(0, 3).ToLower();
                if (!three.ContainsKey(name3))
                    three.Add(name3, new List<string>());
                three[name3].Add(name);
            }
            watch3.Stop();
            time3 = watch3.ElapsedMilliseconds.ToString() + "ms";
            InitializeComponent();

            this.label2.Text = time2;
            this.label3.Text = time3;
            this.label6.Text = time1;

            this.timer1.Tick += new EventHandler(this.timer1_Tick);
            this.timer1.Interval=500;
        }

        private bool _canUpdate = true;
        private bool _needUpdate = false;
        System.Windows.Forms.Timer timer1 = new System.Windows.Forms.Timer();
        List<string> searchData;
        private void combobox1_TextChanged(object sender, EventArgs e)
        {
            if (_needUpdate)
            {
                if (_canUpdate)
                {
                    _canUpdate = false;
                    UpdateData();
                }
                else
                {
                    RestartTimer();
                }
            }
        }

        private bool recursive = false;
        private void UpdateData()
        {
            if (recursive)
                return;
            if (this.comboBox1.Text.Length == 3) {
                if (three.ContainsKey(this.comboBox1.Text.ToLower()))
                    searchData = three[this.comboBox1.Text.ToLower()];
                else
                    searchData = new List<string>();
            }
            else if (this.comboBox1.Text.Length == 2)
            {
                if (two.ContainsKey(this.comboBox1.Text.ToLower()))
                    searchData = two[this.comboBox1.Text.ToLower()];
                 else
                    searchData = new List<string>();
            }
            this.recursive = true;
            if (searchData != null)
                HandleTextChanged(searchData);
            this.recursive = false;
        }
        
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            _needUpdate = false;
        }
        private void combobox1_TextUpdate(object sender, EventArgs e)
        {
            _needUpdate = true;
        }
        private void RestartTimer()
        {
            timer1.Stop();
            _canUpdate = false;
            timer1.Start();
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            _canUpdate = true;
            timer1.Stop();
            UpdateData();
        }
        private void HandleTextChanged(List<string> dataSource)
        {
            var text = this.comboBox1.Text;

            if (dataSource.Count() > 0)
            {
                this.comboBox1.DataSource = dataSource;

                var sText = this.comboBox1.Items[0].ToString();
                this.comboBox1.SelectionStart = text.Length;
                this.comboBox1.SelectionLength = sText.Length - text.Length;
                this.comboBox1.DroppedDown = true;


                return;
            }
            else
            {
                this.comboBox1.DroppedDown = false;
                this.comboBox1.SelectionStart = text.Length;
            }
        }
    }
}
