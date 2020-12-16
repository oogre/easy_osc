# Easy OSC

## Processing

This piece of code is written in Processing (Java), you could find into oscUDP and oscWS folders all the code needed. To run this code install [Processing](http://processing.org), then install dependencies [oscP5]() and [webSockets]() (you'll find these dependencies into the libraries folder).

### oscUDP

#### Initialization

```processing
import oscP5.*;
import netP5.*;

final int UDP_IN_PORT = 12000;
final int UDP_OUT_PORT = 12001;
final String IP = "127.0.0.1";

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  oscP5 = new OscP5(this, UDP_IN_PORT);
  myRemoteLocation = new NetAddress(IP, UDP_OUT_PORT);
}
```

#### Read

```processing
void draw(){   
}

void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  // theOscMessage.get(0).floatValue() // to get first param as float
  // theOscMessage.get(1).intValue() // to get second param as integer
}
```

#### Write

```processing
void draw(){
  OscMessage myMessage = new OscMessage("/test");
  myMessage.add(123.0); /* add an float to the osc message */
  myMessage.add(987);   /* add an int to the osc message */
  oscP5.send(myMessage, myRemoteLocation); 
}
```

### oscWS

#### Initialization

By default oscP5 will run with UDP but we can inject WebSocket message in this object for interpretation. As wll every UDP setup won't be used, neither they are needed.

```processing
import java.net.DatagramPacket;
import websockets.*;
import oscP5.*;
import netP5.*;

final int UDP_IN_PORT = 12000; // unused
final int UDP_OUT_PORT = 12001;// unused
final int WS_PORT = 6969; // WebSocket port
final String IP = "127.0.0.1";

OscP5 oscP5;
NetAddress myRemoteLocation;
WebsocketServer ws;

void setup() {
  oscP5 = new OscP5(this, UDP_IN_PORT);
  myRemoteLocation = new NetAddress(IP, UDP_OUT_PORT);
  ws= new WebsocketServer(this, WS_PORT, "/");
}
```

#### Read

```processing
void draw(){   
}

void webSocketServerEvent(byte[] data, int offset, int length) {
  DatagramPacket myPacket = new DatagramPacket(data, length, myRemoteLocation.inetaddress(), WS_PORT);
  oscP5.process(myPacket, WS_PORT);
}

void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
  // theOscMessage.get(0).floatValue() // to get first param as float
  // theOscMessage.get(1).intValue() // to get second param as integer
}
```

#### Write

```processing
void draw(){
  OscMessage myMessage = new OscMessage("/test");
  myMessage.add(123); /* add an int to the osc message */ 
  ws.sendMessage(myMessage.getBytes());
}
```
