/*
  Switch statement  with serial input
 
 Demonstrates the use of a switch statement.  The switch
 statement allows you to choose from among a set of discrete values
 of a variable.  It's like a series of if statements.
 
 To see this sketch in action, open the Serial monitor and send any character.
 The characters a, b, c, d, and e, will turn on LEDs.  Any other character will turn
 the LEDs off.
 
 The circuit:
 * 5 LEDs attached to digital pins 2 through 6 through 220-ohm resistors
 
 created 1 Jul 2009
 by Tom Igoe 
 
This example code is in the public domain.
   
 http://www.arduino.cc/en/Tutorial/SwitchCase2
 */



#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
   AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(150);
  myMotor1->run(FORWARD);
  // turn on motor
  myMotor1->run(RELEASE); 
  
  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor2->run(RELEASE);
  
  myMotor3->setSpeed(150);
  myMotor3->run(FORWARD);
  // turn on motor
  myMotor3->run(RELEASE);
  
  myMotor4->setSpeed(150);
  myMotor4->run(FORWARD);
  // turn on motor
  myMotor4->run(RELEASE);
 
}

void loop() {
  uint8_t i;
  // give ample warmup time for readings to stabilize

  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.  
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For 
    // example 'a' = 97, 'b' = 98, and so forth:

    switch (inByte) {
    
      case 'w':    
      Serial.println("FORWARD1");
      myMotor1->run(FORWARD);
      for (i=0; i<255; i++) {
      myMotor1->setSpeed(i);  
      delay(10);
       }    
      break;
    
    case 's':    
      Serial.println("BACKWARD1");
      
      myMotor1->run(BACKWARD);
      for (i=0; i<255; i++) {
      myMotor1->setSpeed(i);  
      delay(10);
       }   
      break;
    
    case 'e':    
      Serial.println("RELEASE1");
      myMotor1->run(RELEASE);
      delay(1000);
      break;

      case 'x':    
      Serial.println("FORWARD2");
      myMotor2->run(FORWARD);
      for (i=0; i<255; i++) {
      myMotor2->setSpeed(i);  
      delay(10);
       }    
      break;
    
    case 'd':    
      Serial.println("BACKWARD2");    
      myMotor2->run(BACKWARD);
      for (i=0; i<255; i++) {
      myMotor2->setSpeed(i);  
      delay(10);
       }   
      break;
    
    case 'r':    
      Serial.println("RELEASE2");
      Serial.print("tech");
      myMotor2->run(RELEASE);
      delay(1000);
      break;
  
  
      case 'c':    
      Serial.println("FORWARD3");
      myMotor3->run(FORWARD);
      for (i=0; i<255; i++) {
      myMotor3->setSpeed(i);  
      delay(10);
       }    
      break;
    
    case 'f':    
      Serial.println("BACKWARD3");   
      myMotor3->run(BACKWARD);
      for (i=0; i<255; i++) {
      myMotor3->setSpeed(i);  
      delay(10);
       }   
      break;
    
    case 't':
      Serial.println("RELEASE3");
      myMotor3->run(RELEASE);
      delay(1000);
      break;

      case 'v':    
      Serial.println("FORWARD4");
      myMotor4->run(FORWARD);
      for (i=0; i<255; i++) {
      myMotor4->setSpeed(i);  
      delay(10);
       }    
      break;
    
    case 'g':    
      Serial.println("BACKWARD4");  
      myMotor4->run(BACKWARD);
      for (i=0; i<255; i++) {
      myMotor4->setSpeed(i);  
      delay(10);
       }   
      break;
    
    case 'y':
      Serial.println("RELEASE4");
      myMotor4->run(RELEASE);
      delay(1000);
      break;      



} 
  }
}

