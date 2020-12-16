void sendMessage(char * addr, int value) {
  OSCMessage msg(addr);
  msg.add(value);
  SLIPSerial.beginPacket();
  msg.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}

void sendMessage(char * addr, char * value) {
  OSCMessage msg(addr);
  msg.add(value);
  SLIPSerial.beginPacket();
  msg.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}

void sendMessage(char * addr, float value) {
  OSCMessage msg(addr);
  msg.add(value);
  SLIPSerial.beginPacket();
  msg.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}
