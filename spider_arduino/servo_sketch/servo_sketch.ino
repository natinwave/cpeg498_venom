void setup() {
  
  //Set 8 of the PWM pins (pins 3, 4, 5, 6, 20, 21, 22, and 23) to have freq=50Hz.
  //Why 50Hz?
  //Answer: Because we need the PWM pins operating at 20ms period,
  //        since that's what the SG90 Servo datasheet says is the operating period.
  analogWriteFrequency(3, 50);
  analogWriteFrequency(4, 50);
  analogWriteFrequency(5, 50);
  analogWriteFrequency(6, 50);
  analogWriteFrequency(20, 50);
  analogWriteFrequency(21, 50);
  analogWriteFrequency(22, 50);
  analogWriteFrequency(23, 50);
  
  //Open a serial communication line with data rate = 9600 bits per second.
  //NOTE: The Raspberry Pi sends commands and the Arduino receives them.
  //      Nothing is sent back the other way.
  //NOTE: Make sure that the Raspberry Pi has a matching bit transmission rate,
  //      so that the Arduino is receiving new bits at the same rate that the 
  //      Raspberry Pi is sending them.
  Serial.begin(9600);
  
  Serial.println("setup done");
}

void loop() {

  test_all_legs();
  
  if (Serial.available()) {
    char ch = Serial.read();
    //Here, the Arduino reads serial USB input, 
    //which will be commands (in the form of characters) coming from the RaspberryPi.
    //The Arduino must translate those commands into servo PWM pin commands.
    if (ch == 'w') {
      Serial.println("Received 'move forward' command");
      move_forward();
    }
    else if (ch == 'a') {
      Serial.println("Received 'move left' command");
      move_left();
    }
    else if (ch == 's') {
      Serial.println("Received 'move backward' command");
      move_backward();
    }
    else if (ch == 'd') {
      Serial.println("Received 'move right' command");
      move_right();
    }
  }
}

void test_all_legs() {
  //NOTE: All of these analogWrite commands are just testing the 8 servos by moving them back and forth.
  //      The test works!
  analogWrite(3, 13); //13 divided by 255 = 5% duty cycle (1ms high time) --> servo goes to left pos
  analogWrite(4, 13);
  analogWrite(5, 13);
  analogWrite(6, 13);
  analogWrite(20, 13);
  analogWrite(21, 13);
  analogWrite(22, 13);
  analogWrite(23, 13);
  delay(100);
  analogWrite(3, 19); //19 divided by 255 = 7.5% duty cycle (1.5ms high time) --> servo goes to middle pos
  analogWrite(4, 19);
  analogWrite(5, 19);
  analogWrite(6, 19);
  analogWrite(20, 19);
  analogWrite(21, 19);
  analogWrite(22, 19);
  analogWrite(23, 19);
  delay(100);
  analogWrite(3, 25); //25 divided by 255 = 10% duty cycle (2ms high time) --> servo goes to right pos
  analogWrite(4, 25);
  analogWrite(5, 25);
  analogWrite(6, 25);
  analogWrite(20, 25);
  analogWrite(21, 25);
  analogWrite(22, 25);
  analogWrite(23, 25);
  delay(100);
  analogWrite(3, 19); //19 divided by 255 = 7.5% duty cycle (1.5ms high time) --> servo goes to middle pos
  analogWrite(4, 19);
  analogWrite(5, 19);
  analogWrite(6, 19);
  analogWrite(20, 19);
  analogWrite(21, 19);
  analogWrite(22, 19);
  analogWrite(23, 19);
  delay(100);
}

//NOTE: The following are all the leg names:
//      FL = front-left leg
//      FR = front-right leg
//      BL = back-left leg
//      BR = back-right leg

//NOTE: From here on, CW="clockwise" and CCW="counter-clockwise"

//NOTE: Movement is done at 3 levels of abstraction, which we'll call 
//      the "all-legs level", "single-leg level", and "servo level."
//      There are 4 movements, which are forward, left, backward, and right.
//      Each movement has its own section. 
//      Each section has functions for all 3 levels of abstraction.
//      The "servo level" works the same way for all movements,
//      so its functions are collected at the bottom of this whole program.

//SECTION: move_forward
void move_forward() { //all-legs level
  move_FL_forward();
  move_FR_forward();
  move_BL_forward();
  move_BR_forward();
}
//move_forward single-leg level
void move_FL_forward() {
  elevate_leg("FL", "up");
  rotate_leg("FL", "CW");
  elevate_leg("FL", "down");
  rotate_leg("FL", "CCW");
}
void move_FR_forward() {
  elevate_leg("FR", "up");
  rotate_leg("FR", "CCW");
  elevate_leg("FR", "down");
  rotate_leg("FR", "CW");
}
void move_BL_forward() {
  elevate_leg("BL", "up");
  rotate_leg("BL", "CW");
  elevate_leg("BL", "down");
  rotate_leg("BL", "CCW");
}
void move_BR_forward() {
  elevate_leg("BR", "up");
  rotate_leg("BR", "CCW");
  elevate_leg("BR", "down");
  rotate_leg("BR", "CW");
}

//NOTE: The rest is commented out until
//      we can get forward motion to work.

//SECTION: move_left
void move_left() {
  move_FL_left();
  move_BL_left();
  move_FR_left();
  move_BR_left();
}
void move_FL_left() {
  elevate_leg("FL", "up");
  rotate_leg("FL", "CCW");
  elevate_leg("FL", "down");
  rotate_leg("FL", "CW");
}
void move_FR_left() {
  elevate_leg("FR", "up");
  rotate_leg("FR", "CCW");
  elevate_leg("FR", "down");
  rotate_leg("FR", "CW");
}
void move_BL_left() {
  elevate_leg("BL", "up");
  rotate_leg("BL", "CW");
  elevate_leg("BL", "down");
  rotate_leg("BL", "CCW");
}
void move_BR_left() {
  elevate_leg("BR", "up");
  rotate_leg("BR", "CW");
  elevate_leg("BR", "down");
  rotate_leg("BR", "CCW");
}
//SECTION: move_backward
void move_backward() {
  move_BL_backward();
  move_BR_backward();
  move_FL_backward();
  move_FR_backward();
}
void move_FL_backward() {
  elevate_leg("FL", "up");
  rotate_leg("FL", "CCW");
  elevate_leg("FL", "down");
  rotate_leg("FL", "CW");
}
void move_FR_backward() {
  elevate_leg("FR", "up");
  rotate_leg("FR", "CW");
  elevate_leg("FR", "down");
  rotate_leg("FR", "CCW");
}
void move_BL_backward() {
  elevate_leg("BL", "up");
  rotate_leg("BL", "CCW");
  elevate_leg("BL", "down");
  rotate_leg("BL", "CW");
}
void move_BR_backward() {
  elevate_leg("BR", "up");
  rotate_leg("BR", "CW");
  elevate_leg("BR", "down");
  rotate_leg("BR", "CCW");
}

//SECTION: move_right
void move_right() {
  move_FR_right();
  move_BR_right();
  move_FL_right();
  move_BL_right();
}
void move_FL_right() {
  elevate_leg("FL", "up");
  rotate_leg("FL", "CW");
  elevate_leg("FL", "down");
  rotate_leg("FL", "CCW");
}
void move_FR_right() {
  elevate_leg("FR", "up");
  rotate_leg("FR", "CW");
  elevate_leg("FR", "down");
  rotate_leg("FR", "CCW");
}
void move_BL_right() {
  elevate_leg("BL", "up");
  rotate_leg("BL", "CCW");
  elevate_leg("BL", "down");
  rotate_leg("BL", "CW");
}
void move_BR_right() {
  elevate_leg("BR", "up");
  rotate_leg("BR", "CCW");
  elevate_leg("BR", "down");
  rotate_leg("BR", "CW");
}




//SECTION: servo-level (generalized for all movements by mapping string leg names to PWM pin numbers)
//NOTE: The following are the string leg names and their associated PWM pin numbers (subject to change):
//      "FL" --> shoulder=3, elbow=4
//      "FR" --> shoulder=5, elbow=6
//      "BL" --> shoulder=20, elbow=21
//      "BR" --> shoulder=22, elbow=23
//NOTE: Shoulders rotate the leg on the plane of the body (left and right)
//      and elbows elevate the leg on the plane perpendicular to the body (up and down).

void elevate_leg(String leg_name, String up_or_down) {
  //NOTE: Moving a leg up consists in the following steps:
  //      Step 1: Depending on which leg it is, determine the elbow PWM pin number.
  //              Then, depending on whether the leg must elevate up or down,
  //              determine whether to actuate the servo left or right.
  //              NOTE: The logic of this step is dependent on the physical orientation of the servo.
  //      Step 2: Write an analog frequency to the elbow PWM pin that actuates 
  //              the connected servo either left or right.
  //      Step 3: Have a small delay, so that whatever action is taken after 
  //              this action doesn't happen immediately.

  //Step 1
  int elbow_PWM_pin_number;
  String left_or_right;
  if (leg_name == "FL") {
    elbow_PWM_pin_number = 4;
    if (up_or_down == "up") {
      left_or_right = "left";
    }
    else { //up_or_down == "down"
      left_or_right = "right";
    }
  }
  else if (leg_name == "FR") {
    elbow_PWM_pin_number = 6;
    if (up_or_down == "up") {
      left_or_right = "right";
    }
    else { //up_or_down == "down"
      left_or_right = "left";
    }
  }
  else if (leg_name == "BL") {
    elbow_PWM_pin_number = 21;
    if (up_or_down == "up") {
      left_or_right = "left";
    }
    else { //up_or_down == "down"
      left_or_right = "right";
    }
  }
  else if (leg_name == "BR") {
    elbow_PWM_pin_number = 23;
    if (up_or_down == "up") {
      left_or_right = "right";
    }
    else { //up_or_down == "down"
      left_or_right = "left";
    }
  }

  //Step 2
  left_pos = 13;
  right_pos = 25;
  if (left_or_right == "left") {
    analogWrite(elbow_PWM_pin_number, left_pos);
  }
  else { //left_or_right == "right"
    analogWrite(elbow_PWM_pin_number, right_pos);
  }

  //Step 3
  delay(100);
}
void rotate_leg(String leg_name, String CW_or_CCW) {
  //NOTE: Rotating a leg CW consists in the following steps:
  //      Step 1: Depending on which leg it is, determine the shoulder PWM pin number.
  //              Then, depending on whether the leg must rotate CW or CCW,
  //              determine whether to actuate the servo left or right.
  //              NOTE: The logic of this step is dependent on the physical orientation of the servo.
  //      Step 2: Write an analog frequency to the shoulder PWM pin that actuates 
  //              the connected servo either left or right.
  //      Step 3: Have a small delay, so that whatever action is taken after 
  //              this action doesn't happen immediately.

  //Step 1
  int shoulder_PWM_pin_number;
  String left_or_right;
  if (leg_name == "FL") {
    shoulder_PWM_pin_number = 3;
    if (CW_or_CCW == "CW") {
      left_or_right = "left";
    }
    else { //CW_or_CCW == "CCW"
      left_or_right = "right";
    }
  }
  else if (leg_name == "FR") {
    shoulder_PWM_pin_number = 5;
    if (CW_or_CCW == "CW") {
      left_or_right = "right";
    }
    else { //CW_or_CCW == "CCW"
      left_or_right = "left";
    }
  }
  else if (leg_name == "BL") {
    shoulder_PWM_pin_number = 20;
    if (CW_or_CCW == "CW") {
      left_or_right = "left";
    }
    else { //CW_or_CCW == "CCW"
      left_or_right = "right";
    }
  }
  else if (leg_name == "BR") {
    shoulder_PWM_pin_number = 22;
    if (CW_or_CCW == "CW") {
      left_or_right = "right";
    }
    else { //CW_or_CCW == "CCW"
      left_or_right = "left";
    }
  }

  //Step 2
  left_pos = 13;
  right_pos = 25;
  if (left_or_right == "left") {
    analogWrite(shoulder_PWM_pin_number, left_pos);
  }
  else { //left_or_right == "right"
    analogWrite(shoulder_PWM_pin_number, right_pos);
  }

  //Step 3
  delay(100);
}
