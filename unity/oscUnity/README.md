# How to use : *osc_unity*

Create an empty object with component OSC (Assets/Scripts/OSC/OSC.cs)

Setup *connection type* 

- UPD for standard osc communication (*In Port* + *Out Port* : must be different)

- WebSocket for webBrowser/websocket osc communication (*In Port* & *Out Port* : are the same)

*Out IP* 127.0.0.1 for local communication

Debugging checkbox let this scripts to log all message (Address + values)  into the Console.

![setup.gif](./../doc/setup.gif)

###### Recieve :

The component Receive Position (Assets/Scripts/ReceivePosition.cs) contains all the code needed to Receive data.

```csharp
public class ReceivePosition : MonoBehaviour {
    public OSC osc;
    ...
    void Start(){
        osc.SetAddressHandler("/cube/x", OnReceiveX);
        ...
    }

    void OnReceiveX(OscMessage message)
    {
        Vector3 position = transform.position;
        position.x = message.GetFloat(0);
        transform.position = position;
    }
    ...
```

###### Send :

The component Receive Position (Assets/Scripts/ReceivePosition.cs) contains all the code needed to Send data.

```csharp
...
    OscMessage msg = new OscMessage();
    msg.address = "/cursor";
    msg.values.Add(Input.mousePosition.x);
    msg.values.Add(Input.mousePosition.y);
    osc.Send(msg);
...
```

###### Troubleshooting Unity 2020...

This error may occure on Unity 2020

> Deterministic compilation failed. You can disable Deterministic builds in Player Settings
> Assets\Scripts\OSC\OscPacket\websocket-sharp\AssemblyInfo.cs(20,28): error CS8357: The specified version string contains wildcards, which are not compatible with determinism. Either remove wildcards from the version string, or disable determinism for this compilation

Solution : 

Go to *<u>Project Settings</u>* pannel, into the *<u>Player</u>* sub-menu uncheck *<u>Use Deterministic Compilation</u>*

### ### Dependencies

- [GitHub - sta/websocket-sharp: A C# implementation of the WebSocket protocol client and server](https://github.com/sta/websocket-sharp)

- Custom version of [GitHub - thomasfredericks/UnityOSC: Open Sound Control (OSC) for Unity](https://github.com/thomasfredericks/UnityOSC)

- [GitHub - Deadcows/MyBox: MyBox is a set of attributes, tools and extensions for Unity](https://github.com/Deadcows/MyBox)
