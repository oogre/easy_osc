#include <easyOsc.h>

EasyOsc com("bonjour");

void setup() {
  Serial.begin(115200);
  IPAddress ip = com.begin();
  Serial.print("My IP is : ");
  Serial.println(ip);
}

void loop() {
  com.send("/touch/4", touchRead(4) );
  com.send("/touch/13", touchRead(13) );
  delay(33);
}
