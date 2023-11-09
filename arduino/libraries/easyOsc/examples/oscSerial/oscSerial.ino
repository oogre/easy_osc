#include <easyOsc.h>

EasyOsc osc;

int redChannel = 3;
int greenChannel = 5;
int blueChannel = 6;

void setup() {
  SLIPSerial.begin(9600);
  pinMode(redChannel, OUTPUT);
  pinMode(greenChannel, OUTPUT);
  pinMode(blueChannel, OUTPUT);
  osc.onMessage("/led", [](OSCMessage & msg) {
    if (msg.isInt(0)) {
      analogWrite(redChannel, msg.getInt(0));
    }
    if (msg.isInt(1)) {
      analogWrite(greenChannel, msg.getInt(1));
    }
    if (msg.isInt(2)) {
      analogWrite(blueChannel, msg.getInt(2));
    }
  });
}

void loop() {
  
  OSCMessage msg("/cube/x");
  msg.add((int)analogRead(A0));
  osc.send(&msg);
  
  delay(33);
}
