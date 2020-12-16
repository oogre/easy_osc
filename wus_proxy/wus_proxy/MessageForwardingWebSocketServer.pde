import java.nio.ByteBuffer;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;

import org.java_websocket.WebSocket;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.WebSocketServer;

public class MessageForwardingWebSocketServer extends WebSocketServer {
  private ArrayList<WebSocket> clients;

  public MessageForwardingWebSocketServer( PApplet parent, int port ) throws UnknownHostException {
    super( new InetSocketAddress( port ) );
    clients = new ArrayList<WebSocket>();
    parent.registerMethod("dispose", this);
    this.setReuseAddr(true);
    this.start();
  }

  public MessageForwardingWebSocketServer( PApplet parent, InetSocketAddress address ) {
    super( address );
    clients = new ArrayList<WebSocket>();
    parent.registerMethod("dispose", this);
    this.setReuseAddr(true);
    this.start();
  }

  @Override
    public void onStart() {
    System.out.println( "Started" );
  }

  @Override
    public void onOpen( WebSocket conn, ClientHandshake handshake ) {
    this.clients.add(conn);
    System.out.println( conn.getRemoteSocketAddress().getAddress().getHostAddress() + " entered the room!" );
  }

  @Override
    public void onClose( WebSocket conn, int code, String reason, boolean remote ) {
    this.clients.remove(conn);
    System.out.println( conn + " has left the room!" );
  }

  @Override
    public void onMessage( WebSocket conn, String message ) {
    this.messageForwarding( message, conn );
  }

  @Override
    public void onMessage( WebSocket conn, ByteBuffer message ) {
    this.messageForwarding( message, conn );
  }

  @Override
    public void onError( WebSocket conn, Exception ex ) {
    ex.printStackTrace();
    if ( conn != null ) {
      // some errors like port binding failed may not be assignable to a specific websocket
    }
  }

  public void messageForwarding( String text, WebSocket execpt ) {
    drawIncoming();
    drawOUTcoming();
    synchronized ( this.clients ) {
      for ( WebSocket c : this.clients ) {
        if (c != execpt) {
          c.send( text );
        }
      }
    }
  }

  public void messageForwarding( ByteBuffer text, WebSocket execpt ) {
    drawIncoming();
    drawOUTcoming();
    synchronized ( this.clients ) {
      for ( WebSocket c : this.clients ) {
        if (c != execpt) {
          c.send( text );
        }
      }
    }
  }

  public void dispose() {
    try {
      System.out.println("Killing WS server");
      this.stop();
      System.out.println("WS server closed");
    }
    catch(IOException e) {
      e.printStackTrace();
    }
    catch(InterruptedException e) {
      e.printStackTrace();
    }
  }
}
