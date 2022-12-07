/**
 * oscP5sendreceive by andreas schlegel
 * example shows how to send and receive osc messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 */

import oscP5.*;
import netP5.*;


final int UDP_IN_PORT = 12000;
final int UDP_OUT_PORT = 12001;
final String IP = "192.168.1.255";

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400, 400);
  frameRate(25);
  oscP5 = new OscP5(this, UDP_IN_PORT);
  myRemoteLocation = new NetAddress(IP, UDP_OUT_PORT);
}

void draw() {  

  background(random(255), random(255), random(255));
  OscMessage myMessage = new OscMessage("/led");
  myMessage.add(frameCount%2 == 0 ? 1 : 0);
  oscP5.send(myMessage, myRemoteLocation);
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  //print("### received an osc message.");
  //print(" addrpattern: "+theOscMessage.addrPattern());
  //println(" typetag: "+theOscMessage.typetag());
  String types = theOscMessage.typetag();
  //print("values : ");
  for(int i = 0 ; i < types.length(); i ++) {
    char type = types.charAt(i);
    if (type == 'f') {
      //println("\t", theOscMessage.get(i).floatValue());
    }else if (type == 'i') {
      println("\t", theOscMessage.get(i).intValue());
    }else if (type == 'F') {
      println("\t", theOscMessage.get(i).booleanValue());
    }else if (type == 'd') {
      println("\t", theOscMessage.get(i).doubleValue());
    }else if (type == 's') {
      println("\t", theOscMessage.get(i).stringValue());
    }else if (type == 'c') {
      println("\t", theOscMessage.get(i).charValue());
    }
  }
}
