//UDP communication
UDP udp;

int inPort = 6161;
int outPort = 6969;
String ipAddress = "127.0.0.1";

void setupUDP() {
  udp = new UDP( this, inPort );
  //udp.log( true );     // <-- printout the connection activity
  udp.listen( true );
}

void stopUDP() {
  udp.close();
}

void UDPSendBuffer(byte[] data) {
  udp.send( data, ipAddress, outPort );
}

//called when UDP receives some data
void receive( byte[] data) {
  drawOUTcoming();
  if (PROXY_TYPE == Serial__UDP) {
    serialSend(data);
  }
}
