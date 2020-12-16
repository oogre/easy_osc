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
  
  sendMessage("/cube/x", (int)random(-10, 10));

  delay(33);
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
    messageIN.dispatch("/bonjour", HelloWorld);
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

void HelloWorld(OSCMessage &msg)
{
  if (msg.isString(0))
  {
    String t = msg.getString(0);
    //do nothing with it
  }
}
