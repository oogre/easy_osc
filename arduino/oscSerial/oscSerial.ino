#include <OSCMessage.h>
#include <OSCBoards.h>

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif

void setup() {
  // put your setup code here, to run once:
  SLIPSerial.begin(9600);

}

void loop() {
  OSCreceive();
  
  OSCMessage msg("/cube/x");
  msg.add((int)random(-10, 10));
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

void LEDcontrol(OSCMessage &msg)
{
  if (msg.isFloat(0))
  {
    pinMode(LED_BUILTIN, OUTPUT);
    bool state = LOW;
    if(msg.getFloat(0) > 0){
      state = HIGH;
    }
    digitalWrite(LED_BUILTIN, state);
  }
}
