#include "easyOsc.h";
#include "EasyStepper.h";

EasyOsc osc("easyOSC");

const uint8_t maxStepper = 2;
uint8_t stepperCounter = 0;
EasyStepper steppers [2];

void setup() {
  Serial.begin(115200);
  osc.begin();

  osc.onMessage("/setStepper", createStepper);
  osc.onMessage("/stepper", driveStepper);
  osc.onMessage("/setOutput", createOutput);
  osc.onMessage("/output", driveOutput);
  osc.onMessage("/setPWM", createPWM);
  osc.onMessage("/pwm", drivePWM);

  osc.onMessage("/touch", driveTouch);
  osc.onMessage("/analogRead", driveAnalogRead);
  osc.onMessage("/digitalRead", driveDigitalRead);

}

void loop() {
  osc.update();
  for (uint8_t i = 0 ; i < maxStepper ; i ++) {
    if (steppers[i].isValid()) {
      steppers[i].update();
    }
  }
}
