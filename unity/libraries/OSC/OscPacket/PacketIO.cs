using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PacketIO {
    
    /// <summary>
    /// Open a UDP socket and create a UDP sender.
    /// 
    /// </summary>
    /// <returns>True on success, false on failure.</returns>
    public virtual bool Open() { return false; }

    /// <summary>
    /// Close the socket currently listening, and destroy the UDP sender device.
    /// </summary>
    public virtual void Close() { }

    public virtual void OnDisable(){ }

    /// <summary>
    /// Query the open state of the UDP socket.
    /// </summary>
    /// <returns>True if open, false if closed.</returns>
    public virtual bool IsOpen() { return false; }

    /// <summary>
    /// Send a packet of bytes out via UDP.
    /// </summary>
    /// <param name="packet">The packet of bytes to be sent.</param>
    /// <param name="length">The length of the packet of bytes to be sent.</param>
    public virtual void SendPacket(byte[] packet, int length){ }

    /// <summary>
    /// Receive a packet of bytes over UDP.
    /// </summary>
    /// <param name="buffer">The buffer to be read into.</param>
    /// <returns>The number of bytes read, or 0 on failure.</returns>
    public virtual int ReceivePacket(byte[] buffer){ return 0; }



    /// <summary>
    /// The address of the board that you're sending to.
    /// </summary>
    public virtual string RemoteHostName{ get ; set; }

    /// <summary>
    /// The remote port that you're sending to.
    /// </summary>
    public virtual int RemotePort{ get; set; }

    /// <summary>
    /// The local port you're listening on.
    /// </summary>
    public virtual int LocalPort{ get; set; }
}
