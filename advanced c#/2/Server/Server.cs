using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab2
{
    class Server
    {
        private string path;
        private int port;
        private Thread thread;
        private HttpListener listener;

        public Server(string path, int port)
        {
            this.port = port;
            //check if port is ok
            TcpListener l = new TcpListener(IPAddress.Loopback, this.port);
            l.Start();
            l.Stop();
            this.path = path;
            this.port = port;
            this.thread = new Thread(this.Listen);
            this.thread.Start();
        }

        private void Listen()
        {
            listener = new HttpListener();
            try
            {
                listener.Prefixes.Add("http://localhost:" + this.port.ToString() + "/");
                listener.Start();
                while (true)
                {
                    try
                    {
                        HttpListenerContext context = listener.GetContext();
                        Process(context);
                    }
                    catch (Exception ex)
                    {
                    }
                }
            }
            catch (Exception x)
            {
                MessageBox.Show("error: " + x);
            }
        }

        private void Process(HttpListenerContext context)
        {
            string filename = context.Request.Url.AbsolutePath;
            Console.WriteLine(filename);
            filename = filename.Substring(1);
            if (filename.Equals("/") || filename.Equals(""))
                filename = "index.html";
            filename = Path.Combine(Path.GetFullPath(this.path), filename);

            if (File.Exists(filename))
            {
                try
                {
                    Stream input = new FileStream(filename, FileMode.Open);
                    //Adding permanent http response headers
                    string mime;
                    context.Response.ContentType = "text/html";
                    context.Response.ContentLength64 = input.Length;
                    context.Response.AddHeader("Date", DateTime.Now.ToString("r"));
                    byte[] buffer = new byte[1024 * 16];
                    int nbytes;
                    while ((nbytes = input.Read(buffer, 0, buffer.Length)) > 0)
                        context.Response.OutputStream.Write(buffer, 0, nbytes);
                    input.Close();
                    context.Response.StatusCode = (int)HttpStatusCode.OK;
                    context.Response.OutputStream.Flush();
                }
                catch (Exception ex)
                {
                    context.Response.StatusCode = (int)HttpStatusCode.InternalServerError;
                }
            }
            else
            {
                context.Response.StatusCode = (int)HttpStatusCode.NotFound;
            }
            context.Response.OutputStream.Close();
        }

        public void Stop()
        {
            this.thread.Abort();
            this.listener.Stop();
        }
    }
}
