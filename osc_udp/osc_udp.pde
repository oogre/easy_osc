import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400,400);
  /* start oscP5, listening for incoming messages at port 6161 */
  oscP5 = new OscP5(this,6161);
  /* start oscP5, outgoing messages at port 6969 */
  myRemoteLocation = new NetAddress("127.0.0.1", 6969);
}


void draw() {
  background(0);  
}

void mousePressed() {
  OscMessage myMessage = new OscMessage("/cube/x");
  myMessage.add(random(10)); /* add an int to the osc message */
  oscP5.send(myMessage, myRemoteLocation); 
}

/* incoming osc message are forwarded to the oscEvent method. */
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" origine: "+theOscMessage.netAddress());
  println(" addrpattern: "+theOscMessage.addrPattern());
  println((char)(theOscMessage.getTypetagAsBytes()[0]));
  //println(" value: "+theOscMessage.get(0).intValue());
}
