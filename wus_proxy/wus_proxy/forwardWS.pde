



ServerForwardThread wsForwardThread;

public class ServerForwardThread extends Thread {
  PApplet parent;
  public MessageForwardingWebSocketServer wsServer;
  ServerForwardThread(PApplet parent) {
    this.parent = parent;
  }
  @Override
    public void run() {
    try {
      wsServer = new MessageForwardingWebSocketServer( this.parent, PORT );
    }
    catch(IOException e) {
      e.printStackTrace();
    }
  }

  public void dispose() {
    wsServer.dispose();
  }
}

void setupForward() {
  wsForwardThread = new ServerForwardThread(this);
  wsForwardThread.start();
}

void stopForward() {
  wsForwardThread.dispose();
}
