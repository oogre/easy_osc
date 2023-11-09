#include <WiFi.h>
#include <WiFiUdp.h>
#include <Dictionary.h>
#include <OSCMessage.h>

class EasyOsc {
    typedef void (*MessageHandler)(OSCMessage &msg);
  public :
    EasyOsc (String ssid = "easy-OSC", uint16_t inPort = 8888, uint16_t outPort = 9999, IPAddress outIP = IPAddress (192, 168, 4, 255)) :
      ssid(ssid),
      inPort(inPort),
      outPort(outPort),
      outIP(outIP) {}

    void begin() {
      WiFi.softAP(ssid);
      Udp.begin(inPort);
    }

    void onMessage(String address, MessageHandler handler) {
      listeners.set(address, handler);
    }

    void update() {
      OSCMessage messageIN;
      int size;
      if ( (size = Udp.parsePacket()) > 0)
      {
        while (size--) messageIN.fill(Udp.read());
        if (messageIN.hasError()) return;
        char buffer[64];
        int result = messageIN.getAddress(buffer);
        if (listeners.contains(buffer)) {
          messageIN.dispatch(buffer, listeners.get(buffer));
        }
      }
    }

    template <typename T>
    void send(char * address, T value) {
      OSCMessage msg(address);
      msg.add(value);
      Udp.beginPacket(outIP, outPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
    }

  private :
    String ssid;
    uint16_t inPort;
    uint16_t outPort;
    IPAddress outIP;
    Dictionary<String, MessageHandler> listeners;
    WiFiUDP Udp;
};
