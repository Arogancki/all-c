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
                    string dirPath = fbd.SelectedPath;
                    string[] files = Directory.GetFiles(dirPath, "*.sln");
                    if (files == null || files.Length ==0) {
                        MessageBox.Show("No .sln file found");
                        return;
                    }
                    
                    foreach (string file in files)
                        checkSlnFiles(dirPath, file);
                }
            }
        }

        private void checkSlnFiles(string dirPath, string file) {

            string sln = File.ReadAllText(file);

            string format = ".csproj";

            int end = sln.IndexOf(format);

            if (end == -1) {
                MessageBox.Show("No " + format + " found");
            }

            sln = sln.Substring(0, end);
            int start = sln.LastIndexOf("\"") + 1;
            sln = sln.Substring(start) + format;
            string csvPath = Path.Combine(dirPath, sln);

            if (!File.Exists(csvPath))
            {
                MessageBox.Show("File " + csvPath + " does not exist.");
                return;
            }
            string csf = File.ReadAllText(csvPath);

            string projectDir = Path.GetDirectoryName(csvPath);
            string copyDirPath = Path.Combine(dirPath, "copy");
            if (Directory.Exists(copyDirPath))
            {
                MessageBox.Show("Directory " + copyDirPath + " already exist.");
                return;
            }
            Directory.CreateDirectory(copyDirPath);
            File.Copy(file, Path.Combine(copyDirPath, Path.GetFileName(file)));
            string projectCopyPath = Path.Combine(copyDirPath, Path.GetFileName(projectDir));
            Directory.CreateDirectory(projectCopyPath);
            DirectoryCopy(projectDir, projectCopyPath, true);
            
            List<string> whiteList = new List<string>();
            // do whitelisty dodac 2 zeby byla prawdziwa warotsc skopiowanych
            do
            {
                int startCsf = csf.IndexOf("Include=");
                if (startCsf == -1)
                    break; // no more includes
                startCsf += 9;
                csf = csf.Substring(startCsf);
                int endCsf = csf.IndexOf("\"");

                string projectFileRelative = csf.Substring(0, endCsf);

                try
                {
                    string projectFile = Path.Combine(projectCopyPath, projectFileRelative);

                    if (File.Exists(projectFile))
                    {
                        whiteList.Add(projectFileRelative);
                    }
                }
                catch (Exception ex)
                {
                    //not a file
                }
            } while (true);

            // Leave only files frome white list
            int howMany = whiteList.Count + 2;
            DeleteAllOther(projectCopyPath, projectCopyPath, whiteList);

            // compres
            // .net 4.5 zip file
            string zipFile = copyDirPath + ".zip";
            if (File.Exists(zipFile))
            {
                MessageBox.Show("Zipping aborted. File " + zipFile + " already exists.");
            }
            else if (!Directory.Exists(copyDirPath))
            {
                MessageBox.Show("Copy directory doesnt exists");
                return;

            }
            else
            {
                // Comend this if < .net4.5
                System.IO.Compression.ZipFile.CreateFromDirectory(copyDirPath, zipFile);
                Directory.Delete(copyDirPath, true);
            }

            MessageBox.Show("Copied " + howMany + " files.");

        }
        private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();
            // If the destination directory doesn't exist, create it.
            if (!Directory.Exists(destDirName))
            {
                Directory.CreateDirectory(destDirName);
            }

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }
        }
        private void DeleteAllOther(string sourceDirName, string rootDir,  List<string> whiteList) {
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);
            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string relative = file.FullName.Replace(rootDir, "").Substring(1);
                int index = whiteList.IndexOf(relative);
                if (index == -1)
                {
                    File.Delete(file.FullName);
                    System.Diagnostics.Debug.WriteLine("Deleted " + relative);
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("Not deleted " + relative);
                    whiteList.RemoveAt(index);
                }
            }
            // teraz to samo dla folderow
            // ale sie zaglebiac
            // na koncu jesli folder zsotal bpusty to usunac

            DirectoryInfo[] directories = dir.GetDirectories();
            foreach (DirectoryInfo directory in directories)
            {
                DeleteAllOther(directory.FullName, sourceDirName, whiteList);
                if (directory.GetFiles().Length < 1)
                    Directory.Delete(directory.FullName);
            }
        }
    }
}
