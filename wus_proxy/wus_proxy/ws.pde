

int PORT = 6969;
ServerThread wsThread;

public class ServerThread extends Thread {
  PApplet parent;
  public SendReceiveWebSocketServer wsServer;
  ServerThread(PApplet parent) {
    this.parent = parent;
  }
  @Override
    public void run() {
    try {
      wsServer = new SendReceiveWebSocketServer( this.parent, PORT );
    }
    catch(IOException e) {
      e.printStackTrace();
    }
  }
  
  public void dispose() {
    wsServer.dispose();
  }
  
  public void send(byte[] data) {
    ByteBuffer d = ByteBuffer.wrap(data);
    wsServer.send(d);
  }
}


void setupWSServer() {
  wsThread = new ServerThread(this);
  wsThread.start();
}

void stopWS() {
  wsThread.dispose();
}

void wsSendBuffer(byte[] data) {
  wsThread.send(data);
}

void onMessage(String message) {
  drawOUTcoming();
  //send it over to serial
  if (PROXY_TYPE == Serial__WebSocket) {
    serialSend(message);
  }
}

void onMessage(ByteBuffer message) {
  drawOUTcoming();
  if (PROXY_TYPE == Serial__WebSocket) {
    serialSend(message.array());
  }
}
