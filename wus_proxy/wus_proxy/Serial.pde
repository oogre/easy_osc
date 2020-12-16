
//the Serial communication to the Arduino
Serial serial;

String[] serialRateStrings = {
  "9600", "14400", "19200", "28800", "38400", "57600", "115200"
};
int baud = 9600;
int serialListNumber = 3;
boolean serialActive = false;
ArrayList<Byte> serialBuffer = new ArrayList<Byte>();

void setupSerial() {
  if (serial == null) {
    serial = new Serial(this, Serial.list()[serialListNumber], baud);
  }
  serialActive = true;
}



void stopSerial() {
  serialActive = false;
}

void disposeSerial() {
  println("disposeSerial");
  serial.dispose();
  serial.stop();
  serial.clear();
}

void serialEvent(Serial serial) { 
  if (!serialActive)return;
  drawIncoming();
  while (serial.available () > 0) {
    slipDecode(byte(serial.read()));
  }
}

void SerialSendToWS() {
  byte [] buffer = new byte[serialBuffer.size()];
  //copy the buffer over
  for (int i = 0; i < serialBuffer.size(); i++) {
    buffer[i] = serialBuffer.get(i);
  }
  //send it off
  wsSendBuffer(buffer);
  //clear the buffer
  serialBuffer.clear();
  
}

void SerialSendToUDP() {
  byte [] buffer = new byte[serialBuffer.size()];
  //copy the buffer over
  for (int i = 0; i < serialBuffer.size(); i++) {
    buffer[i] = serialBuffer.get(i);
  }
  //send it off
  UDPSendBuffer(buffer);
  //clear the buffer
  serialBuffer.clear();
}

void serialSend(byte[] data) {
  //encode the message and send it
  for (int i = 0; i < data.length; i++) {
    slipEncode(data[i]);
  }
  //write the eot
  serial.write(eot);
}

void serialSend(String data) {
  //encode the message and send it
  for (int i = 0; i < data.length(); i++) {
    slipEncode(data.charAt(i));
  }
  //write the eot
  serial.write(eot);
}

/************************************************************************************
 SLIP ENCODING
 ************************************************************************************/

byte eot = byte(192);
byte slipesc = byte(219);
byte slipescend = byte(220);
byte slipescesc = byte(221);

byte previousByte;


void slipDecode(byte incoming) {
  byte previous = previousByte;
  previousByte = incoming;
  //if the previous was the escape char
  if (previous == slipesc) {
    //if this one is the esc eot
    if (incoming==slipescend) { 
      serialBuffer.add(eot);
    } else if (incoming==slipescesc) {
      serialBuffer.add(slipesc);
    }
  } else if (incoming==eot) {
    switch(PROXY_TYPE) {
    case Serial__WebSocket:
      SerialSendToWS();
      break;
    case Serial__UDP:
      SerialSendToUDP();
      break;
    }
  } else if (incoming != slipesc) {
    serialBuffer.add(incoming);
  }
}

void slipEncode(char incoming) {
  slipEncode((byte)incoming);
}
void slipEncode(byte incoming) {
  if (incoming == eot) { 
    serial.write(slipesc);
    serial.write(slipescend);
  } else if (incoming==slipesc) {  
    serial.write(slipesc);
    serial.write(slipescesc);
  } else {
    serial.write(incoming);
  }
}
