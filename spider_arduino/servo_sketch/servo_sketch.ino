#include <Servo.h>

Servo servoPin6;
Servo servoPin9;
Servo servoPin10;
Servo servoPin11;
int pos = 0;
bool move_legs = true;

void setup() {
  servoPin6.attach(6, 1000, 2000);
  servoPin9.attach(9, 1000, 2000); //attach to digital PWM pin 9
                                  //min (0 deg) = 1000 us = 1 ms
                                  //max (180 deg) = 2000 us = 2 ms
  servoPin10.attach(10, 1000, 2000);
  servoPin11.attach(11, 1000, 2000);
  Serial.begin(9600); //open a serial communication line with data rate = 9600 bps
  Serial.println("setup done");
}

void actuate_servo_left_to_right(Servo servoPin, String servoName) {
  Serial.println("actuate_servo_left_to_right");
  int MAX = 0;
  int MIN = 0;
  if (servoName == "FRS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "BRS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "FLS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "BLS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "FRK") {
    MAX = 40;
    MIN = 0;
  }
  else if (servoName == "FLK") {
    MAX = 140;
    MIN = 100;
  }
  else if (servoName == "BRK") {
    MAX = 140;
    MIN = 100;
  }
  else if (servoName == "BLK") {
    MAX = 40;
    MIN = 0;
  }
  for (pos = MIN; pos <= MAX; pos += 1) {
    servoPin.write(pos);
    delay(3); //wait for servo to reach pos
  }
}

void actuate_servo_right_to_left(Servo servoPin, String servoName) {
  Serial.println("actuate_servo_right_to_left");
  int MAX = 0;
  int MIN = 0;
  if (servoName == "FRS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "BRS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "FLS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "BLS") {
    MAX = 60;
    MIN = 0;
  }
  else if (servoName == "FRK") {
    MAX = 40;
    MIN = 0;
  }
  else if (servoName == "FLK") {
    MAX = 140;
    MIN = 100;
  }
  else if (servoName == "BRK") {
    MAX = 140;
    MIN = 100;
  }
  else if (servoName == "BLK") {
    MAX = 40;
    MIN = 0;
  }
  for (pos = MAX; pos >= MIN; pos -= 1) {
    servoPin.write(pos);
    delay(3);
  }
}

void loop() {

  //TODO: Read Serial USB input, which will be commands
  //      coming from the Raspberry Pi.
  
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'a') {
      actuate_servo_left_to_right(servoPin6, "FRS");
    }
    else if (ch == 's') {
      actuate_servo_right_to_left(servoPin6, "FRS");
    }
    else if (ch == 'd') {
      actuate_servo_left_to_right(servoPin6, "FRK");
    }
    else if (ch == 'f') {
      actuate_servo_right_to_left(servoPin6, "FRK");
    }
    else if (ch == 'g') {
      actuate_servo_left_to_right(servoPin6, "BRS");
    }
    else if (ch == 'h') {
      actuate_servo_right_to_left(servoPin6, "BRS");
    }
    else if (ch == 'j') {
      actuate_servo_left_to_right(servoPin6, "BRK");
    }
    else if (ch == 'k') {
      actuate_servo_right_to_left(servoPin6, "BRK");
    }
    else if (ch == 'z') {
      actuate_servo_left_to_right(servoPin6, "BLS");
    }
    else if (ch == 'x') {
      actuate_servo_right_to_left(servoPin6, "BLS");
    }
    else if (ch == 'c') {
      actuate_servo_left_to_right(servoPin6, "BLK");
    }
    else if (ch == 'v') {
      actuate_servo_right_to_left(servoPin6, "BLK");
    }
    else if (ch == 'b') {
      actuate_servo_left_to_right(servoPin6, "FLS");
    }
    else if (ch == 'n') {
      actuate_servo_right_to_left(servoPin6, "FLS");
    }
    else if (ch == 'm') {
      actuate_servo_left_to_right(servoPin6, "FLK");
    }
    else if (ch == 'o') {
      actuate_servo_right_to_left(servoPin6, "FLK");
    }
  }
}

