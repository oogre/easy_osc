import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;
int flag = 1;

void setup() {
  size(400, 400);
  oscP5 = new OscP5(this, 9999);
  myRemoteLocation = new NetAddress("192.168.4.1", 8888);
}

void draw() {
  background(0);
}

void mousePressed() {
  OscMessage myMessage = new OscMessage("/led");
  myMessage.add(flag); /* add an int to the osc message */
  flag = 1-flag;
  oscP5.send(myMessage, myRemoteLocation);
}

void oscEvent(OscMessage theOscMessage) {
  print("### received an osc message.");
  print(" addrpattern : "+theOscMessage.addrPattern());
  println(" value :  "+theOscMessage.get(0).intValue());
}
