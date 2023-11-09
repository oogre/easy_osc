#include <Dictionary.h>
#include <OSCMessage.h>
#include <OSCBoards.h>

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif

#ifdef ESP32
#include <WiFi.h>
#include <WiFiUdp.h>
#endif

class EasyOsc {
    typedef void (*MessageHandler)(OSCMessage &msg);
  public :
    
    enum CONNECTION_TYPE { ACCESS_POINT, REGULAR_WIFI, USB_SERIAL };

    #ifdef ESP32
      EasyOsc (String ssid = "easy-OSC", String pwd = "", uint16_t inPort = 8888, uint16_t outPort = 9999, IPAddress outIP = IPAddress (192, 168, 4, 255)) :
        ssid(ssid),
        pwd(pwd),
        inPort(inPort),
        outPort(outPort),
        outIP(outIP) 
      {}
    #else
      EasyOsc () {}
    #endif

    #ifdef ESP32
      IPAddress begin(CONNECTION_TYPE type = ACCESS_POINT) {
        con_type = type;
        switch (type) {
          case USB_SERIAL : break;

          case REGULAR_WIFI:
            if(pwd.equals(""))WiFi.begin(ssid);
            else WiFi.begin(ssid, pwd);
            Udp.begin(inPort);
           return WiFi.localIP();

          case ACCESS_POINT:
            if(pwd.equals("")){
              if(!WiFi.softAP(ssid)){
                Serial.println("Soft AP creation failed.");
                while(1);
              }
            } else {
              if(!WiFi.softAP(ssid, pwd)){
                Serial.println("Soft AP creation failed.");
                while(1);
              }
            }
            Udp.begin(inPort);
            return WiFi.softAPIP();
        }
      }
    #else
      void begin() {
        con_type = USB_SERIAL;
      }
    #endif

    void onMessage(String address, MessageHandler handler) {
      listeners.set(address, handler);
    }

    void update() {
      OSCMessage messageIN;
      int size;

      switch(con_type){
        case USB_SERIAL : 
          if (SLIPSerial.available())
            while (!SLIPSerial.endofPacket())
              while (SLIPSerial.available())
                messageIN.fill(SLIPSerial.read());
        break;
        default : 
          #ifdef ESP32
            if ( (size = Udp.parsePacket()) > 0)
              while (size--) messageIN.fill(Udp.read());
          #endif
        break;
      }
      
      if (messageIN.hasError()) return;

      char buffer[64];
      int result = messageIN.getAddress(buffer);

      if (listeners.contains(buffer))
        messageIN.dispatch(buffer, listeners.get(buffer));
    }

    template <typename T>
    void send(String address, T value) {
      char* char_array = new char[address.length() + 1];
      strcpy(char_array, address.c_str());
      send(char_array, value);
    }

    template <typename T>
    void send(char * address, T value) {
      OSCMessage msg(address);
      msg.add(value);
      send(&msg);
    }

    void send(OSCMessage * msg) {
      switch(con_type){
        case USB_SERIAL : 
          SLIPSerial.beginPacket();
          msg->send(SLIPSerial);
          SLIPSerial.endPacket();
          msg->empty();
        break;
        default : 
          #ifdef ESP32
            Udp.beginPacket(outIP, outPort);
            msg->send(Udp);
            Udp.endPacket();
            msg->empty();
          #endif
        break;
      }
    }

  private :
    CONNECTION_TYPE con_type;
    Dictionary<String, MessageHandler> listeners;
    #ifdef ESP32
      String ssid;
      String pwd;
      uint16_t inPort;
      uint16_t outPort;
      IPAddress outIP;
      WiFiUDP Udp;
    #endif
};