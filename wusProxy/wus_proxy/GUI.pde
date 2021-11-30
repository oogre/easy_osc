
final int Serial__WebSocket = 0;
final int Serial__UDP = 1;
final int WebSocket__WebSocket = 2;
int PROXY_TYPE = -1;

ControlP5 cp5;

void setupGUI() {
  //the ControlP5 object
  cp5 = new ControlP5(this);


  Group nav = cp5.addGroup("nav")
    .hideBar();                
  cp5.addButton("Serial_WebSocket")
    .setLabel("serial2ws")
    .setPosition(width/10, 30)
    .setSize(width/5, 20)
    .setGroup(nav);
  cp5.addButton("Serial_UDP")
    .setLabel("serial2udp")
    .setPosition(4*width/10, 30)
    .setSize(width/5, 20)
    .setGroup(nav);
  cp5.addButton("WebSocket_WebSocket")
    .setLabel("ws2ws")
    .setPosition(7*width/10, 30)
    .setSize(width/5, 20)
    .setGroup(nav);

  Group sug = cp5.addGroup("sug")
    .setPosition(0, 50).hideBar();
  Group serial = cp5.addGroup("serial")
    .setGroup(sug)
    .hideBar();
  DropdownList baudRate = cp5.addDropdownList("BaudRate")
    .setPosition(50, 130)
    .setSize(200, 90)
    .setItemHeight(20)
    .setBarHeight(20)
    .setId(4).close()
    .setGroup(serial);
  baudRate.getCaptionLabel().getStyle().marginTop = 3;
  baudRate.getCaptionLabel().getStyle().marginLeft = 3;
  baudRate.getCaptionLabel().set("SELECT THE BAUD RATE");
  for (int i=0; i<serialRateStrings.length; i++) baudRate.addItem(serialRateStrings[i], i);
  DropdownList serialddl = cp5.addDropdownList("SerialPort")
    .setPosition(50, 30)
    .setSize(200, 90)
    .setItemHeight(20)
    .setBarHeight(20)
    .setId(0).close()
    .setGroup(serial);
  ControllerStyle serialStyle = serialddl.getCaptionLabel().getStyle();
  serialddl.getCaptionLabel().set("SELECT ARDUINO SERIAL PORT");
  serialddl.getCaptionLabel().getStyle().marginTop = 3;
  serialddl.getCaptionLabel().getStyle().marginLeft = 3;
  String SerialList[] = Serial.list(); 
  for (int i=0; i<SerialList.length; i++) serialddl.addItem(SerialList[i], i);
  
  Group udp = cp5.addGroup("udp")
    .setGroup(sug)
    .hideBar();
  cp5.addTextfield("IP address")
    .setPosition(300, 30)
    .setAutoClear(false)
    .setText(ipAddress)
    .setGroup(udp);
  cp5.addTextfield("Incoming Port Number")
    .setPosition(300, 80)
    .setAutoClear(false)
    .setText(str(inPort))
    .setGroup(udp);
  cp5.addTextfield("Outgoing Port Number")
    .setPosition(300, 130)
    .setAutoClear(false)
    .setText(str(outPort))
    .setGroup(udp);
  cp5.addTextlabel("arduinoLabel")
    .setText("Serial")
    .setPosition(50, 10)
    .setColorValue(0xffffff00)
    .setFont(createFont("SansSerif", 11))
    .setGroup(udp);
  cp5.addTextlabel("UDPLabel")
    .setText("UDP")
    .setPosition(300, 10)
    .setColorValue(0xffffff00)
    .setFont(createFont("SansSerif", 11))
    .setGroup(udp);

  Group swg = cp5.addGroup("swg")
    .setPosition(0, 50)
    .hideBar();
  serial.setGroup(swg);
  Group ws = cp5.addGroup("ws")
    .hideBar()
    .setGroup(swg);
  cp5.addTextfield("Port Number")
    .setPosition(300, 80)
    .setAutoClear(false)
    .setText(str(PORT))
    .setGroup(ws);

  Group wwg = cp5.addGroup("wwg")
    .setPosition(0, 50).hideBar();
  ws.setGroup(wwg);

  Group submit = cp5.addGroup("submit")
    .hideBar();
  cp5.addButton("START")
    .setPosition(width/2 - 100, height-30)
    .setSize(200, 20)
    .setGroup(submit);
  cp5.addButton("STOP")
    .setPosition(width/2 - 100, height-30)
    .setSize(200, 20)
    .hide()
    .setGroup(submit);
    
    swg.hide();
    wwg.hide();
    sug.hide();
    submit.hide();
}

public void Serial_WebSocket(){
  cp5.get(Group.class, "serial").setGroup(cp5.get(Group.class, "swg"));
  cp5.get(Group.class, "ws").setGroup(cp5.get(Group.class, "swg"));
  cp5.get(Group.class, "swg").show();
  cp5.get(Group.class, "wwg").hide();
  cp5.get(Group.class, "sug").hide();
  cp5.get(Group.class, "submit").show();
  cp5.get(Group.class, "submit").show();
  PROXY_TYPE = Serial__WebSocket;
}

public void Serial_UDP(){
  cp5.get(Group.class, "serial").setGroup(cp5.get(Group.class, "sug"));
  cp5.get(Group.class, "udp").setGroup(cp5.get(Group.class, "sug"));
  cp5.get(Group.class, "swg").hide();
  cp5.get(Group.class, "wwg").hide();
  cp5.get(Group.class, "sug").show();
  cp5.get(Group.class, "submit").show();
  PROXY_TYPE = Serial__UDP;
}

public void WebSocket_WebSocket(){
  cp5.get(Group.class, "ws").setGroup(cp5.get(Group.class, "wwg"));
  cp5.get(Group.class, "swg").hide();
  cp5.get(Group.class, "wwg").show();
  cp5.get(Group.class, "sug").hide();
  cp5.get(Group.class, "submit").show();
  PROXY_TYPE = WebSocket__WebSocket;
}


void controlEvent(ControlEvent theEvent) {
  String eventName = theEvent.getName();
  if (eventName == "SerialPort") {
    //set the serial port 
    serialListNumber = int(theEvent.getValue());
  } else if (eventName == "BaudRate") {
    int index = int(theEvent.getValue());
    baud = Integer.parseInt(serialRateStrings[index]);
  } else if (eventName == "IP address") {
    cp5.get(Textfield.class, eventName).setFocus(false);
    ipAddress = theEvent.getStringValue();
  } else if (eventName == "Incoming Port Number") {
    cp5.get(Textfield.class, eventName).setFocus(false);
    inPort = Integer.parseInt(theEvent.getStringValue());
  } else if (eventName == "Outgoing Port Number") {
    cp5.get(Textfield.class, eventName).setFocus(false);
    outPort = Integer.parseInt(theEvent.getStringValue());
  } else if (eventName == "Port Number") {
    cp5.get(Textfield.class, eventName).setFocus(false);
    PORT = Integer.parseInt(theEvent.getStringValue());
  }
}

//start everything
public void START() {
  switch(PROXY_TYPE){
    case Serial__WebSocket:{
      Textfield portField = cp5.get(Textfield.class, "Port Number");
      PORT = Integer.parseInt(portField.getText());
      setupWSServer();
      setupSerial();
    }
    break;
    case Serial__UDP:{
      Textfield inPortField = cp5.get(Textfield.class, "Incoming Port Number");
      inPort = Integer.parseInt(inPortField.getText());
      Textfield outPortField = cp5.get(Textfield.class, "Outgoing Port Number");
      outPort = Integer.parseInt(outPortField.getText());
      Textfield ipField = cp5.get(Textfield.class, "IP address");
      ipAddress = ipField.getText();
      setupUDP();
      setupSerial();
    }
    break;
    case WebSocket__WebSocket:{
      Textfield portField = cp5.get(Textfield.class, "Port Number");
      PORT = Integer.parseInt(portField.getText());
      setupForward();
    }
    break;
  }
  cp5.get(Group.class, "nav").hide();
  cp5.get(Group.class, "swg").hide();
  cp5.get(Group.class, "wwg").hide();
  cp5.get(Group.class, "sug").hide();
  cp5.get(Button.class, "START").hide();
  cp5.get(Button.class, "STOP").show();
  
  applicationRunning = true;
}

public void STOP() {
  switch(PROXY_TYPE){
    case Serial__WebSocket:
    stopSerial();
    stopWS();
    cp5.get(Group.class, "swg").show();
    break;
    case Serial__UDP:
    stopSerial();
    stopUDP();
    cp5.get(Group.class, "sug").show();
    break;
    case WebSocket__WebSocket:
    stopForward();
    cp5.get(Group.class, "wwg").show();
    break;
  }
  cp5.get(Group.class, "nav").show();
  cp5.get(Button.class, "START").show();
  cp5.get(Button.class, "STOP").hide();
  applicationRunning = false;
}
