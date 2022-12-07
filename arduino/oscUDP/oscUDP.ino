#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

const char* ssid     = "WiFi-2.4-F600";
const char* password = "Jr7X4aXm7U4h";

WiFiUDP Udp;
IPAddress outIp(192, 168, 1, 255);
unsigned int outPort = 12000; // local port to listen on
unsigned int inPort = 12001; // local port to listen on

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Udp.begin(inPort);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Receive OSC at : udp://");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(inPort);

  Serial.print("Send OSC to udp://");
  Serial.print(outIp);
  Serial.print(":");
  Serial.println(outPort);

  pinMode(LED_BUILTIN, OUTPUT);
}

void ledHandler(OSCMessage &msg, int addrOffset ) {
  if (msg.isInt(0)) {
    if (msg.getInt(0) == 0) {
      digitalWrite(LED_BUILTIN, LOW);
    }
    if (msg.getInt(0) == 1) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

void loop() {

  
  OSCMessage messageIN;
  int size;
  if ( (size = Udp.parsePacket()) > 0)
  {
    while (size--){
      messageIN.fill(Udp.read());
    }
    if (!messageIN.hasError()) {
      Serial.println("received");
      messageIN.route("/led", ledHandler);
    }
  }



  OSCMessage messageOut("/cube/x");
  int r = (int)random(100);
  messageOut.add(r);

  // SEND OSC message to network
  Udp.beginPacket(outIp, outPort);
  messageOut.send(Udp);
  Udp.endPacket();
  messageOut.empty();

  delay(33);
}
