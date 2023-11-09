

void createOutput(OSCMessage &msg) {
  if (1 == msg.size()) {
    if (msg.isInt(0)) {
      pinMode(msg.getInt(0), OUTPUT);
    }
  }
}

void driveOutput(OSCMessage &msg) {
  if (1 == msg.size()) {
    if (msg.isInt(0) && msg.isInt(1)) {
      digitalWrite(msg.getInt(0), msg.isInt(1) % 2 == 0 ? LOW : HIGH);
    }
  }
}

void createPWM(OSCMessage &msg) {
  if (1 == msg.size()) {
    if (msg.isInt(0)) {
      pinMode(msg.getInt(0), OUTPUT);
    }
  }
}

void drivePWM(OSCMessage &msg) {
  if (1 == msg.size()) {
    if (msg.isInt(0) && msg.isInt(1)) {
      analogWrite(msg.getInt(0), msg.getInt(1) % 255);
    }
  }
}


void driveStepper(OSCMessage &msg) { // ID · DIST · SPEED
  if (3 == msg.size()) {
    if (msg.isInt(0) && msg.isInt(1) && msg.isInt(2)) {
      steppers[msg.getInt(0) % maxStepper].dist = msg.getInt(1);
      steppers[msg.getInt(0) % maxStepper].speed = msg.getInt(2);
    }
  }
}


void createStepper(OSCMessage &msg) {
  if (2 == msg.size()) {
    if (msg.isInt(0) && msg.isInt(1)) {
      steppers[stepperCounter % maxStepper] = EasyStepper(msg.getInt(0), msg.getInt(1));
      steppers[stepperCounter % maxStepper].begin();
      stepperCounter++;
    }
  }
  else if (4 == msg.size()) {
    if (msg.isInt(0) && msg.isInt(1) && msg.isInt(2) && msg.isInt(3)) {
      steppers[stepperCounter % maxStepper] = EasyStepper(msg.getInt(0), msg.getInt(1), msg.getInt(2), msg.getInt(3));
      steppers[stepperCounter % maxStepper].begin();
      stepperCounter++;
    }
  }
}


void driveTouch(OSCMessage &msg) {
  if (1 == msg.size()) {
    osc.send("/touch/"+ String(msg.getInt(0)), (int)touchRead(msg.getInt(0)));
  }
}

void driveAnalogRead(OSCMessage &msg) {
  if (1 == msg.size()) {
    osc.send("/analogRead/"+ String(msg.getInt(0)), (int)analogRead(msg.getInt(0)));
  }
}
void driveDigitalRead(OSCMessage &msg) {
  if (1 == msg.size()) {
    Serial.println("/touch/"+ String(msg.getInt(0)));
    Serial.println((int)touchRead(msg.getInt(0)));
    osc.send("/digitalRead/"+ String(msg.getInt(0)), (int)digitalRead(msg.getInt(0)));
  }
}
