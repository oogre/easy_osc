
class Stepper {

  public :
    Stepper (int STEPPER_PIN_1, int STEPPER_PIN_2, int STEPPER_PIN_3, int STEPPER_PIN_4) :
      STEPPER_PIN_1(STEPPER_PIN_1),
      STEPPER_PIN_2(STEPPER_PIN_2),
      STEPPER_PIN_3(STEPPER_PIN_3),
      STEPPER_PIN_4(STEPPER_PIN_4)
    {}

    long dist = 0;
    int speed = 10;

    void begin() {
      pinMode(STEPPER_PIN_1, OUTPUT);
      pinMode(STEPPER_PIN_2, OUTPUT);
      pinMode(STEPPER_PIN_3, OUTPUT);
      pinMode(STEPPER_PIN_4, OUTPUT);

    }
    void update() {
      if (dist > 0) {
        OneStep(speed > 0);
        delay(abs(speed));
      }
    }
  private :
    uint8_t step_number = 0;
    uint8_t STEPPER_PIN_1;
    uint8_t STEPPER_PIN_2;
    uint8_t STEPPER_PIN_3;
    uint8_t STEPPER_PIN_4;

    void OneStep(bool dir) {
      Serial.println(dir);
      if (dir) {
        switch (step_number) {
          case 0:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
          case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
          case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
          case 3:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        }
      } else {
        switch (step_number) {
          case 0:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
          case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
          case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
          case 3:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);


        }
      }
      step_number++;
      step_number %= 4;
      dist--;
    }
};
