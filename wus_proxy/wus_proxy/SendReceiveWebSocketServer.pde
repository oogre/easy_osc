import java.nio.ByteBuffer;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;


import org.java_websocket.WebSocket;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.WebSocketServer;

public class SendReceiveWebSocketServer extends WebSocketServer {
  private ArrayList<WebSocket> clients;
  PApplet parent;
  Method onMessageString;
  Method onMessageByteBuffer;
  public SendReceiveWebSocketServer( PApplet parent, int port ) throws UnknownHostException {
    super( new InetSocketAddress( port ) );
    this.parent = parent;
    this.clients = new ArrayList<WebSocket>();
    this.parent.registerMethod("dispose", this);
    Class[] cArg1 = {String.class};
    Class[] cArg2 = {ByteBuffer.class};
    this.onMessageString = getOnMessageMethod(parent.getClass(), cArg1);
    this.onMessageByteBuffer = getOnMessageMethod(parent.getClass(), cArg2);
    this.setReuseAddr(true);
    this.start();
  }

  public SendReceiveWebSocketServer( PApplet parent, InetSocketAddress address ) {
    super( address );
    this.parent = parent;
    this.clients = new ArrayList<WebSocket>();
    this.parent.registerMethod("dispose", this);
    Class[] cArg1 = {String.class};
    Class[] cArg2 = {ByteBuffer.class};
    this.onMessageString = getOnMessageMethod(parent.getClass(), cArg1);
    this.onMessageByteBuffer = getOnMessageMethod(parent.getClass(), cArg2);
    this.setReuseAddr(true);
    this.start();
  }

  private Method getOnMessageMethod(Class parent, Class[] cArg) {
    try {
      return parent.getMethod("onMessage", cArg);
    } 
    catch(NoSuchMethodException e) {
      System.out.println(e.toString());
    }
    return null;
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
    if (onMessageString!=null) {
      try {
        onMessageString.invoke(this.parent, message);
      } 
      catch (IllegalArgumentException e) {
        e.printStackTrace();
      } 
      catch (IllegalAccessException e) {
        e.printStackTrace();
      } 
      catch (InvocationTargetException e) {
        e.printStackTrace();
      }
    }
  }

  @Override
    public void onMessage( WebSocket conn, ByteBuffer message ) {
    if (onMessageByteBuffer!=null) {
      try {
        onMessageByteBuffer.invoke(this.parent, message);
      } 
      catch (IllegalArgumentException e) {
        e.printStackTrace();
      } 
      catch (IllegalAccessException e) {
        e.printStackTrace();
      } 
      catch (InvocationTargetException e) {
        e.printStackTrace();
      }
    }
  }

  @Override
    public void onError( WebSocket conn, Exception ex ) {
    ex.printStackTrace();
    if ( conn != null ) {
      // some errors like port binding failed may not be assignable to a specific websocket
    }
  }

  public void send( String text ) {
    synchronized ( this.clients ) {
      for ( WebSocket c : this.clients ) {
        c.send( text );
      }
    }
  }

  public void send( ByteBuffer text) {
    synchronized ( this.clients ) {
      for ( WebSocket c : this.clients ) {
        c.send( text );
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
