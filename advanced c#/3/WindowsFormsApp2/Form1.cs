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

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private OpenFileDialog openFileDialog1;
        private void pictureBox3_Click(object sender, EventArgs e)
        {

            using (var fbd = new FolderBrowserDialog())
            {
                DialogResult result = fbd.ShowDialog();

                if (result == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
                {

                    string[] files = Directory.GetFiles(fbd.SelectedPath, "*.sln");
                    if (files == null) {
                        MessageBox.Show("No .sln file found");
                        return;
                    }

                    string File = files[0];



                }
            }
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}
