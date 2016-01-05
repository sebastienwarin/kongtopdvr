/*
 * 
 * Copyright 2013-2016 Sebastien.warin.fr
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

namespace CameraServer
{
    using System;
    using System.Configuration;
    using System.Drawing;
    using System.IO;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;
    using System.Windows.Forms;
    using CameraServer.Capture;
    using Microsoft.Owin;
    using Microsoft.Owin.Hosting;
    using Owin;
    using WinformDVRControl;

    public partial class frmMain : Form
    {
        private delegate Image GetControlAsImage();

        public static frmMain Instance { get; private set; }

        public frmMain()
        {
            Instance = this;
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            WebApp.Start<HttpServerStartup>("http://+:" + ConfigurationManager.AppSettings["HTTP_PORT"]);

            for (int i = 1; i <= 4; i++)
            {
                var dvr = new WinformDVRControlControl()
                {
                    Host = ConfigurationManager.AppSettings["DVR_IP"],
                    Port = Int32.Parse(ConfigurationManager.AppSettings["DVR_PORT"]),
                    Username = ConfigurationManager.AppSettings["DVR_USERNAME"],
                    Password = ConfigurationManager.AppSettings["DVR_PASSWORD"],
                    Channel = i,
                    Width = Int32.Parse(ConfigurationManager.AppSettings["IMG_WIDTH"]),
                    Height = Int32.Parse(ConfigurationManager.AppSettings["IMG_HEIGHT"])
                };
                dvr.Connect();
                dvr.PlayStream();
                flowLayoutPanel1.Controls.Add(dvr);
            }

            this.Height = Int32.Parse(ConfigurationManager.AppSettings["IMG_HEIGHT"]) * 2 + 50;
            this.Width = Int32.Parse(ConfigurationManager.AppSettings["IMG_WIDTH"]) * 2 + 50;
        }

        public static byte[] CaptureCameraAsJPEG(int channelId)
        {
            var dvrControl = frmMain.Instance.flowLayoutPanel1.Controls.OfType<Control>().FirstOrDefault(c => c is WinformDVRControlControl && ((WinformDVRControlControl)c).Channel == channelId) as WinformDVRControlControl;
            if (dvrControl != null)
            {
                return CaptureCameraAsJPEG(dvrControl);
            }
            else
            {
                return new byte[0];
            }
        }

        public static byte[] CaptureCameraAsJPEG(WinformDVRControlControl dvrControl)
        {
            Image image = null;

            if (dvrControl.InvokeRequired)
            {
                GetControlAsImage getControlAsImage = new GetControlAsImage(dvrControl.DrawToImage);
                image = frmMain.Instance.Invoke(getControlAsImage) as Image;
            }
            else
            {
                image = dvrControl.DrawToImage();
            }

            MemoryStream ms = new MemoryStream();
            image.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
            return ms.ToArray();
        }
    }

    public class HttpServerStartup
    {
        public void Configuration(IAppBuilder app)
        {
            app.Use<CameraMiddleware>();
        }
    }

    public class CameraMiddleware : OwinMiddleware
    {
        public CameraMiddleware(OwinMiddleware next)
            : base(next)
        {
        }

        public override System.Threading.Tasks.Task Invoke(IOwinContext context)
        {
            int channelId = 0;
            if (context.Request.Path.HasValue && context.Request.Path.Value.Equals("/stream", StringComparison.InvariantCultureIgnoreCase) &&
                context.Request.QueryString.HasValue && Int32.TryParse(context.Request.Query.Where(q => q.Key.ToLower() == "channelid").Select(a => a.Value.First()).FirstOrDefault(), out channelId))
            {
                context.Response.ContentType = "multipart/x-mixed-replace; boundary=--myboundary";
                context.Response.Body.Flush();

                int fps = 1;
                int count = 0;
                while ((count += 1000 / fps) <= 10000) //!Task.Factory.CancellationToken.IsCancellationRequested)
                {
                    try
                    {
                        System.Diagnostics.Debug.WriteLine("Processing " + channelId);
                        var img = frmMain.CaptureCameraAsJPEG(channelId);
                        byte[] boundary = ASCIIEncoding.ASCII.GetBytes("\r\n--myboundary\r\nContent-Type: image/jpeg\r\nContent-Length:" + img.Length + "\r\n\r\n");
                        MemoryStream mem = new System.IO.MemoryStream(boundary);
                        mem.WriteTo(context.Response.Body);
                        context.Response.Body.Write(img, 0, img.Length);
                        context.Response.Body.Flush();

                        //Thread.Sleep(1000 / fps);
                        Task.Delay(1000 / fps);
                        //Thread.Sleep(66); // = 15 FPS
                    }
                    catch
                    {
                        break;
                    }
                }
            }
            else if (context.Request.Path.HasValue && context.Request.Path.Value.Equals("/img", StringComparison.InvariantCultureIgnoreCase) &&
                context.Request.QueryString.HasValue && Int32.TryParse(context.Request.Query.Where(q => q.Key.ToLower() == "channelid").Select(a => a.Value.First()).FirstOrDefault(), out channelId))
            {
                context.Response.ContentType = "image/jpeg";
                context.Response.Write(frmMain.CaptureCameraAsJPEG(channelId));
            }
            else
            {
                context.Response.Write("Welcome on DVR MJPEG Streamer Server - by Sebastien.warin.fr");
            }

            return Next.Invoke(context);
        }
    }
}
