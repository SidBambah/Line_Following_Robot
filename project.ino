/*
  
  Program to run car around a Figure 8 track 
  Created by Sidharth Bambah
  
 */
//These are the definitions of states
const int STRAIGHT = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int DETECT = 3;
 
// These constants won't change.  They're used to give names
// to the pins used:
const int leftMotor = 9;
const int rightMotor = 5;
const int rightSignal = 13;
const int leftSignal = 12;
  //IR LEDs
const int rightSensorLED = 3;
const int leftSensorLED = 4;
  //Phototransistors
const int rightSensorPHOTO = 6;
const int leftSensorPHOTO = 7;
 
//DEFINE LED PINS HERE

void setup() {
    pinMode(leftMotor, OUTPUT);
    pinMode(rightMotor, OUTPUT);
    pinMode(rightSignal, OUTPUT);
    pinMode(leftSignal, OUTPUT);
    pinMode(rightSensorLED, OUTPUT);
    pinMode(leftSensorLED, OUTPUT);
    pinMode(rightSensorPHOTO, OUTPUT);
    pinMode(leftSensorPHOTO, OUTPUT);
}

//Auxillary Functions
void go_forward(){
  
  analogWrite(leftMotor, 150);
  analogWrite(rightMotor, 130);
}

void go_left(){
  analogWrite(leftMotor, 30);
  analogWrite(rightMotor, 130);
}


void go_right(){
  analogWrite(leftMotor, 145);
  analogWrite(rightMotor, 20);
}


void loop(){

  digitalWrite(rightSensorLED, HIGH);
  digitalWrite(leftSensorLED, HIGH);
  digitalWrite(leftSensorPHOTO, HIGH);
  digitalWrite(rightSensorPHOTO, HIGH);

  //Finite State Machine

 static int state = DETECT;        //Starting State, will change to Detect

 switch (state){
  case DETECT:
    {
      digitalWrite(leftSignal, LOW);
      digitalWrite(rightSignal, LOW);
      int rightSensorValue = analogRead(A0);
      int leftSensorValue = analogRead(A1);

      if((rightSensorValue > 600 && leftSensorValue > 800) || (rightSensorValue < 600 && leftSensorValue < 800))
        state = STRAIGHT;
      else if(leftSensorValue < 800)
        state = LEFT;
      else if(rightSensorValue < 600)
        state = RIGHT;
      else
        state = STRAIGHT;
      break;
    }
  case STRAIGHT:
    {
      digitalWrite(leftSignal, LOW);
      digitalWrite(rightSignal, LOW);
      go_forward();
      state = DETECT;
      break;
    }
  case LEFT:
    {
      digitalWrite(leftSignal, HIGH);
      digitalWrite(rightSignal, LOW);
      go_left();
      state = DETECT;
      break;
    }
  case RIGHT:
    {
      digitalWrite(rightSignal, HIGH);
      digitalWrite(leftSignal, LOW);
      go_right();
      state = DETECT;
      break;
    }
  }
}
