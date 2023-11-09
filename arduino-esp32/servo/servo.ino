// Carte d'extension ESP32 Shield,
// ESP-WROOM-32 extends
// https://fr.aliexpress.com/item/1005004500127370.html
// https://fr.aliexpress.com/item/1005005564949759.html

#include "easyOsc.h";
#include "stepper.h";

/*
  Create EasyOsc (an osc helper object)
  Default String ssid : easy-OSC
  Default uint16_t inputPort : 8888
  Default uint16_t outputPort : 9999
  Default IPAddress outputIP : 192.168.4.255 (broadcast output on all machines on the local network)
*/
EasyOsc osc("stepper");
Stepper stepper(13, 12, 14, 27);
void setup() {
  Serial.begin(115200);
  stepper.begin();
  osc.begin();
  osc.onMessage("/stepper", stepperControler);
}

void loop() {
  osc.update();
  stepper.update();
}

void stepperControler(OSCMessage &msg ) {
  if (msg.isInt(0)) {
    stepper.dist = msg.getInt(0);
  }
  if (msg.isInt(1)) {
    stepper.speed = msg.getInt(1);
  }
}
