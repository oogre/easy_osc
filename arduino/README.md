# Easy OSC

## Arduino

Install this dependency : [GitHub - CNMAT/OSC: OSC: Arduino and Teensy implementation of OSC encoding](https://github.com/CNMAT/OSC) 

_OSC_ Library may be found in the libraries directory. Drop the _OSC_ directory into ```$HOME/Documents/Arduino/libraries```.
Then restart processing.

### Initialization

```arduino
#include <OSCMessage.h>
#include <OSCBoards.h>

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif
```

```arduino
void setup() {
  SLIPSerial.begin(9600);
}
```

### Read

```arduino
void loop() {
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
  if (msg.isFloat(0)){
    pinMode(LED_BUILTIN, OUTPUT);
    bool state = LOW;
    if(msg.getFloat(0) > 0){
      state = HIGH;
    }
    digitalWrite(LED_BUILTIN, state);
  }
}
```

### Write

```arduino
void loop() {
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
```
