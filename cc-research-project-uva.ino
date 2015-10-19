//**************************************************************//
//  Name    : shiftOutCode, Predefined Dual Array Style         //
//  Author  : Carlyn Maw, Tom Igoe                              //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

#include "pitches.h"

#include <Ultrasonic.h>

// Pin A0 Input for the potentiometer
const int sensorPin = A0;    // pin that the sensor is attached to

// Trig = 4
// Echo = 7

//Init an Ultrasonic object
Ultrasonic ultrasonic(7, 4);
int distance = 0;
int distanceMap = 0;

// variables:
int sensorValue = 0;            // the sensor value
int sensorValueStep = 0;        // the sensor value
int sensorValueStep8 = 0;        // the sensor value
//int sensorMin = 1023;         // minimum sensor value
//int sensorMax = 0;            // maximum sensor value
int sensorMin = 0;              // minimum sensor value
int sensorMax = 1023;           // maximum sensor value

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//Bit Shift millis() timer
// will store last time LED was updated
unsigned long previousMillis = 0;

// constants won't change :
// interval at which to blink (milliseconds)
const long interval = 500;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  blinkAll_2Bytes(2,500);

  // calibrate during the first five seconds
//  while (millis() < 5000) {
//    sensorValue = analogRead(sensorPin);
//
//    // record the maximum sensor value
//    if (sensorValue > sensorMax) {
//      sensorMax = sensorValue;
//    }
//
//    // record the minimum sensor value
//    if (sensorValue < sensorMin) {
//      sensorMin = sensorValue;
//    }
//  }
}

void loop() {

  unsigned long currentMillis = millis();

  // read the sensor:
  sensorValue = analogRead(sensorPin);

  // group LED by chip
//  sensorValueStep = map(sensorValue, sensorMin, sensorMax, 0, 4);
//  sensorValueStep = constrain(sensorValueStep, 0, 4);

  // Potentiometer sensor input 
  // group LED by two sections per chip = total 8 sections plus off = 9
//  sensorValueStep8 = map(sensorValue, sensorMin, sensorMax, 0, 9);
//  sensorValueStep8 = constrain(sensorValueStep8, 0, 9);

  distance=ultrasonic.Ranging(CM);//get the current result;

  //  Added timer around the mapping to help with some flashing lights
  if(currentMillis - previousMillis >= interval && distance <= 250) {
    
    // save the last time you blinked the LED 
    previousMillis = currentMillis;  

    distanceMap = map(distance, 3, 250, 8, 0);
    distanceMap = constrain(distanceMap, 0, 8);
//    sensorValueStep8 = distanceMap;

//    Serial.print("Sensor input: ");
//    Serial.println(sensorValue);
//
//    Serial.print("Sensor Step: ");
//    Serial.println(sensorValueStep);
//
//    Serial.print("Sensor Step 8: ");
//    Serial.println(sensorValueStep8);

    // Could print some stuff to the serial if i want
//    Serial.println("******************");
//    Serial.print("the distance is ");
//    Serial.println(distance);
//    Serial.print("the distance Map is ");
//    Serial.println(distanceMap);
//    Serial.println("******************");

    Serial.write(distance);

    digitalWrite(latchPin, 0);
  
    if(distanceMap == 8) {
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 7) {
      shiftOut(dataPin, clockPin, 15);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 6) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 15);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 5) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 255);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 4) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 15);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 3) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 15);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 2) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 255);
    } else if (distanceMap == 1) {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 15);
    } else {
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
      shiftOut(dataPin, clockPin, 0);
    }
  
    digitalWrite(latchPin, 1);
  }
}

// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);

  for (int x = 0; x < n; x++) {
//    digitalWrite(latchPin, 0);
//    shiftOut(dataPin, clockPin, x);
//    shiftOut(dataPin, clockPin, x);
//    shiftOut(dataPin, clockPin, x);
//    shiftOut(dataPin, clockPin, x);
//    Serial.print("bits: ");
//    Serial.println(x);
//    digitalWrite(latchPin, 1);
//    delay(d);

    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}

