#include <easyOsc.h>

/*
  Create EasyOsc (an osc helper object)
  Default String ssid : easy-OSC
  Default String pwd : null
  Default uint16_t inputPort : 8888
  Default uint16_t outputPort : 9999
  Default IPAddress outputIP : 192.168.4.255 (broadcast output on all machines on the local network)
*/
EasyOsc osc;
long timaAtLastSend = 0;

void setup() {
  Serial.begin(115200);

  #ifdef ESP32
    IPAddress ip = osc.begin();
    Serial.print("My IP is : ");
    Serial.println(ip);
  #else
    osc.begin();
  #endif

  osc.onMessage("/led", ledControler);

  pinMode(2, OUTPUT);
}

void loop() {
  osc.update();
  if (millis() - timaAtLastSend > 500) {
    osc.send("/time", (int)millis());
    timaAtLastSend = millis();
  }
}

void ledControler(OSCMessage &msg ) {
  if (msg.isInt(0)) {
    if (msg.getInt(0) == 1) {
      digitalWrite(2, HIGH);
    } else {
      digitalWrite(2, LOW);
    }
  }
}
