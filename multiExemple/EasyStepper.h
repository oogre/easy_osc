
class EasyStepper {
  public :
    EasyStepper   () :
      valid(false)
    {}

    EasyStepper   (int STEPPER_PIN_1, int STEPPER_PIN_2) :
      STEPPER_PIN_1(STEPPER_PIN_1),
      STEPPER_PIN_2(STEPPER_PIN_2),
      twoPin(true),
      valid(true)
    {}

    EasyStepper   (int STEPPER_PIN_1, int STEPPER_PIN_2, int STEPPER_PIN_3, int STEPPER_PIN_4) :
      STEPPER_PIN_1(STEPPER_PIN_1),
      STEPPER_PIN_2(STEPPER_PIN_2),
      STEPPER_PIN_3(STEPPER_PIN_3),
      STEPPER_PIN_4(STEPPER_PIN_4),
      twoPin(false),
      valid(true)
    {}

    long dist = 0;
    int speed = 10;

    void begin() {
      if(!valid)return;
      pinMode(STEPPER_PIN_1, OUTPUT);
      pinMode(STEPPER_PIN_2, OUTPUT);
      if (!twoPin) {
        pinMode(STEPPER_PIN_3, OUTPUT);
        pinMode(STEPPER_PIN_4, OUTPUT);
      }
    }

    bool isValid() {
      return valid;
    }

    void update() {
      if(!valid)return;
      if (dist > 0) {
        OneStep(speed > 0);
        delay(abs(speed));
      }
    }
  private :
    bool valid = false;
    bool twoPin = false;
    uint8_t step_number = 0;
    uint8_t STEPPER_PIN_1;
    uint8_t STEPPER_PIN_2;
    uint8_t STEPPER_PIN_3;
    uint8_t STEPPER_PIN_4;

    void OneStep(bool dir) {
      if (twoPin) {
        digitalWrite(STEPPER_PIN_1, dir);
        digitalWrite(STEPPER_PIN_2, HIGH);
        delayMicroseconds(20);
        digitalWrite(STEPPER_PIN_2, LOW);
        delayMicroseconds(20);
      } else {
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
      }
      step_number++;
      step_number %= 4;
      dist--;
    }
};
