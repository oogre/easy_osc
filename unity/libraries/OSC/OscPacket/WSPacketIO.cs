using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using WebSocketSharp;
using WebSocketSharp.Server;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;

public class WSPacketIO : PacketIO
{
    
    //private UdpClient Sender;
    private WebSocketServer Receiver;
    private bool socketsOpen;
    private string remoteHostName;
    private int remotePort;
    private int localPort;

    private Incomming _i_;

    public WSPacketIO(string hostIP, int remotePort, int localPort)
    {
        RemoteHostName = hostIP;
        RemotePort = remotePort;
        LocalPort = localPort;
        socketsOpen = false;
    }


    ~WSPacketIO()
    {
        // latest time for this socket to be closed
        if (IsOpen())
        {
            Debug.Log("closing udpclient listener on port " + localPort);
            Close();
        }

    }

    /// <summary>
    /// Open a UDP socket and create a UDP sender.
    /// 
    /// </summary>
    /// <returns>True on success, false on failure.</returns>
    public override bool Open()
    {
        try
        {
            Debug.Log("Opening WS listener on port " + localPort);
            Receiver = new WebSocketServer(localPort);
            Receiver.WebSocketServices.Add<Incomming>("/", () => {
                _i_ = new Incomming();
                return _i_;
            });
            Receiver.Start();
            socketsOpen = true;
            return true;
        }
        catch (Exception e)
        {
            Debug.LogWarning("cannot open udp client interface at port " + localPort);
            Debug.LogWarning(e);
        }

        return false;
    }

    /// <summary>
    /// Close the socket currently listening, and destroy the UDP sender device.
    /// </summary>
    public override void Close()
    {
        //if (Sender != null)
        //    Sender.Close();

        if (Receiver != null)
            Receiver.Stop();

        Receiver = null;
        socketsOpen = false;
    }

    public override void OnDisable()
    {
        Close();
    }

    /// <summary>
    /// Query the open state of the UDP socket.
    /// </summary>
    /// <returns>True if open, false if closed.</returns>
    public override bool IsOpen()
    {
        return socketsOpen;
    }

    /// <summary>
    /// Send a packet of bytes out via UDP.
    /// </summary>
    /// <param name="packet">The packet of bytes to be sent.</param>
    /// <param name="length">The length of the packet of bytes to be sent.</param>
    public override void SendPacket(byte[] packet, int length)
    {
        if (!IsOpen())
            Open();
        if (!IsOpen())
            return;

        if (null == _i_) return;

        _i_.CustomSend(packet);
        Debug.Log("osc message sent to " + remoteHostName + " port " + remotePort + " len=" + length);
    }

    /// <summary>
    /// Receive a packet of bytes over UDP.
    /// </summary>
    /// <param name="buffer">The buffer to be read into.</param>
    /// <returns>The number of bytes read, or 0 on failure.</returns>
    public override int ReceivePacket(byte[] buffer)
    { 
        if (!IsOpen())
            Open();
        if (!IsOpen())
            return 0;

        if (null == _i_ || null == _i_._rawData) return 0;

        int count = Math.Min(buffer.Length, _i_._rawData.Length);
        string test = System.Text.Encoding.ASCII.GetString(_i_._rawData);
        System.Array.Copy(_i_._rawData, buffer, count);
        _i_._rawData = null;
        return count;
    }



    /// <summary>
    /// The address of the board that you're sending to.
    /// </summary>
    public override string RemoteHostName
    {
        get
        {
            return remoteHostName;
        }
        set
        {
            remoteHostName = value;
        }
    }

    /// <summary>
    /// The remote port that you're sending to.
    /// </summary>
    public override int RemotePort
    {
        get
        {
            return remotePort;
        }
        set
        {
            remotePort = value;
        }
    }

    /// <summary>
    /// The local port you're listening on.
    /// </summary>
    public override int LocalPort
    {
        get
        {
            return localPort;
        }
        set
        {
            localPort = value;
        }
    }
}


public class Incomming : WebSocketBehavior
{
    public byte[] _rawData;

    public void CustomSend(byte[] buffer) {
        Send(buffer);
    }
    protected override void OnMessage(MessageEventArgs e)
    {
        _rawData = e.RawData;
    }
    protected override void OnOpen()
    {
        Debug.Log("WS OPEN");
    }
    protected override void OnClose(CloseEventArgs e)
    {
        Debug.Log("WS CLOSE");
    }

    protected override void OnError(WebSocketSharp.ErrorEventArgs e)
    {
        Debug.Log("WS ERROR");
    }

}