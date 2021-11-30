
#include <OSCMessage.h>
#include <OSCBoards.h>

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif



int redChannel = 3;
int greenChannel = 5;
int blueChannel = 6;

void setup() {
  SLIPSerial.begin(9600);
  pinMode(redChannel, OUTPUT);
  pinMode(greenChannel, OUTPUT);
  pinMode(blueChannel, OUTPUT);
}

void loop() {
  OSCreceive();
  OSCMessage msg("/cube/x");
  msg.add((int)analogRead(A0));
  send(&msg);
  delay(33);
}

void send(OSCMessage * msg) {
  SLIPSerial.beginPacket();
  msg->send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg->empty(); // free space occupied by message
}

void OSCreceive() {
  OSCMessage messageIN;
  int size;
  if (SLIPSerial.available())
    while (!SLIPSerial.endofPacket())
      while (SLIPSerial.available())
        messageIN.fill(SLIPSerial.read());

  if (!messageIN.hasError()) {
    messageIN.dispatch("/led", LEDcontrol);
  }
}

void LEDcontrol(OSCMessage &msg) {
  if (msg.isInt(0)) {
    analogWrite(redChannel, msg.getInt(0));
  }
  if (msg.isInt(1)) {
    analogWrite(greenChannel, msg.getInt(1));
  }
  if (msg.isInt(2)) {
    analogWrite(blueChannel, msg.getInt(2));
  }
}
