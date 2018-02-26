using ConsoleApplication1;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp3
{
    class Program
    {
        static void Main(string[] args)
        {
            string fp = @"./TextFile1.txt";
            string file = File.ReadAllText(fp);
            HtmlTable t = new HtmlTable(file);
            string x = t.getHTML();
            File.WriteAllText(fp+".html", x);
        }
    }
}