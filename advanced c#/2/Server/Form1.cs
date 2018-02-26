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
using lab2;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private Server server=null;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (server != null)
            {
                server.Stop();
                this.textBox5.Text = "Server down.";
                return;
            }
            MessageBox.Show("Server not working.");
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!Directory.Exists(this.textBox3.Text))
            {
                MessageBox.Show("Dir does not exist.");
                return;
            }
            int p;
            try
            {
                p = Int32.Parse(this.textBox2.Text);
            }
            catch (Exception x)
            {
                MessageBox.Show("Port is invalid.");
                return;
            }
            try
            {
                server = new Server(this.textBox3.Text, p);
            }
            catch (Exception x)
            {
                MessageBox.Show("Port is taken.");
                return;
            }
            this.textBox5.Text = "Server is working ;)";
        }
    }
}
