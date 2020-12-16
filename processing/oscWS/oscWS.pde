import java.net.DatagramPacket;
import websockets.*;
import oscP5.*;
import netP5.*;

final int UDP_IN_PORT = 12000;
final int UDP_OUT_PORT = 12001;
final int WS_PORT = 6969;
final String IP = "127.0.0.1";

OscP5 oscP5;
NetAddress myRemoteLocation;
WebsocketServer ws;

void setup() {
  size(400, 400);
  oscP5 = new OscP5(this, UDP_IN_PORT);
  myRemoteLocation = new NetAddress(IP, UDP_OUT_PORT);
  ws= new WebsocketServer(this, WS_PORT, "/");
}

void draw(){
}

void webSocketServerEvent(byte[] data, int offset, int length) {
  DatagramPacket myPacket = new DatagramPacket(data, length, myRemoteLocation.inetaddress(), WS_PORT);
  oscP5.process(myPacket, WS_PORT);
}

void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print(theOscMessage.addrPattern());
  println(theOscMessage.get(0).floatValue());
}

void mousePressed(){
  OscMessage myMessage = new OscMessage("/test");
  myMessage.add(123); /* add an int to the osc message */ 
  ws.sendMessage(myMessage.getBytes());
}
