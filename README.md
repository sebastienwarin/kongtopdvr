# HTTP Web Server & Windows Control for Kongtop DVR

In 2013, I bought a Kongtop 4CH Full D1 H.264 Network CCTV Camera DVR Digital Video Recorder (model KT79104AD) connected to 4 analog cameras.

To integrate the video cameras on a Web Page like my [home automation dashboard](http://sebastien.warin.fr/2015/07/15/3033-s-panel-une-interface-domotique-et-iot-multi-plateforme-avec-cordova-angularjs-et-constellation-ou-comment-crer-son-dashboard-domotique-mural/) I need to capture and expose on HTTP each channels.

After an exchange by email with the Kingtop support, I receive the Kongtop SDK. So I have created a .NET Winform control in C++/CLI to inject the video stream into a Windows UserControl.

So it's very easy to include the video channel on a Winform application :

    var cam1 = new WinformDVRControlControl()
    {
        Host = "192.168.0.123"
        Port = 40001,
        Username = "admin",
        Password = "00000000",
        Channel = 1,
        Width = 640,
        Height = 480)
    };
    cam1.Connect();
    cam1.PlayStream();
    this.Controls.Add(cam1);

Then to expose camera streams on HTTP, the Winform application capture the screen and expose it by using an OWIN server.

For example :

* Snapshot (Channel 1) : http://localhost:8080/img?channelid=1
* Streaming (Channel 1) :  http://localhost:8080/stream?channelid=1

Now it's very easy to play with your cameras connected on your Kongtop DVR !
