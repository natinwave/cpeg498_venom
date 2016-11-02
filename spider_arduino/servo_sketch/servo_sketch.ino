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

void actuate_servo_left_to_right(Servo servo, bool shoulder) {
  Serial.println("actuate_servo_left_to_right");
  int MAX = 0;
  int MIN = 0;
  if (shoulder) {
    MAX = 360;
    MIN = 100;
  }
  else {
    MAX = 100;
  }
  for (pos = MIN; pos <= MAX; pos += 1) {
    servo.write(pos);
    delay(3); //wait for servo to reach pos
  }
}

void actuate_servo_right_to_left(Servo servo, bool shoulder) {
  Serial.println("actuate_servo_right_to_left");
  int MAX = 0;
  int MIN = 0;
  if (shoulder) {
    MAX = 360;
    MIN = 100;
  }
  else {
    MAX = 100;
  }
  for (pos = MAX; pos >= MIN; pos -= 1) {
    servo.write(pos);
    delay(3);
  }
}

void move_front_left_leg_and_back_right_leg() {
  actuate_servo_right_to_left(servoPin6, true);
  delay(10);
  actuate_servo_right_to_left(servoPin11, false);
  delay(10);
  actuate_servo_left_to_right(servoPin6, true);
  delay(10);
  actuate_servo_left_to_right(servoPin11, false);
  delay(10);
}

void loop() {

  //TODO: Read Serial USB input, which will be commands
  //      coming from the Raspberry Pi.

  if (move_legs) {
    move_front_left_leg_and_back_right_leg();
  }
  
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'a') {
      actuate_servo_left_to_right(servoPin6, true);
    }
    else if (ch == 's') {
      actuate_servo_right_to_left(servoPin6, true);
    }
    else if (ch == 'd') {
      actuate_servo_left_to_right(servoPin9, false);
    }
    else if (ch == 'f') {
      actuate_servo_right_to_left(servoPin9, false);
    }
    else if (ch == 'g') {
      actuate_servo_left_to_right(servoPin10, true);
    }
    else if (ch == 'h') {
      actuate_servo_right_to_left(servoPin10, true);
    }
    else if (ch == 'j') {
      actuate_servo_left_to_right(servoPin11, false);
    }
    else if (ch == 'k') {
      actuate_servo_right_to_left(servoPin11, false);
    }
    else if (ch == 'm') {
      move_legs = !move_legs;
    }
  }
}

