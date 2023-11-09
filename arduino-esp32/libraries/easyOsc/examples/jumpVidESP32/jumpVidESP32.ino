#include <easyOsc.h>

EasyOsc com("bonjour");

void setup() {
  Serial.begin(115200);
  IPAddress ip = com.begin();
  Serial.print("My IP is : ");
  Serial.println(ip);
}

void loop() {
  com.send("/video/jump", analogRead(36)*0.0002442 );
  delay(33);
}
