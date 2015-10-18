//**************************************************************//
//  Name    : shiftOutCode, Predefined Dual Array Style         //
//  Author  : Carlyn Maw, Tom Igoe                              //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

#include "pitches.h"


////Adding Mozzi Includes
//#include <MozziGuts.h>
//#include <Oscil.h> // oscillator template
//#include <tables/sin2048_int8.h> // sine table for oscillator
//
//// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
//Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
//
//const char INPUT_PIN = 0; // set the input for the knob to analog pin 0
//
//// to convey the volume level from updateControl() to updateAudio()
//byte volume;

//Ending Mozzi setup

// notes in the melody:
int melody[] = {
  NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_FS1, NOTE_F1, NOTE_E1, NOTE_DS1, NOTE_D1, NOTE_CS1, NOTE_C1, NOTE_B0
};

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//holders for infromation you're going to pass to shifting function
byte dataRED;
byte dataORANGE;
byte dataYELLOW;
byte dataGREEN;
byte dataArrayRED[15];
byte dataArrayORANGE[15];
byte dataArrayYELLOW[15];
byte dataArrayGREEN[15];

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 

  dataArrayRED[0] = 0xFF; //11111111
  dataArrayRED[1] = 0x7F; //01111111
  dataArrayRED[2] = 0x3F; //00111111
  dataArrayRED[3] = 0x1F; //00011111
  dataArrayRED[4] = 0x0F; //00001111
  dataArrayRED[5] = 0x07; //00000111
  dataArrayRED[6] = 0x03; //00000011
  dataArrayRED[7] = 0x01; //00000001
  dataArrayRED[8] = 0x00; //00000000
  dataArrayRED[9] = 0x01; //00000001
  dataArrayRED[10] = 0x03; //00000011
  dataArrayRED[11] = 0x07; //00000111
  dataArrayRED[12] = 0x0F; //00001111
  dataArrayRED[13] = 0x1F; //00011111
  dataArrayRED[14] = 0x3F; //00111111
  dataArrayRED[15] = 0x7F; //01111111

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayORANGE[0] = 0xFF; //11111111
  dataArrayORANGE[1] = 0x7F; //01111111
  dataArrayORANGE[2] = 0x3F; //00111111
  dataArrayORANGE[3] = 0x1F; //00011111
  dataArrayORANGE[4] = 0x0F; //00001111
  dataArrayORANGE[5] = 0x07; //00000111
  dataArrayORANGE[6] = 0x03; //00000011
  dataArrayORANGE[7] = 0x01; //00000001
  dataArrayORANGE[8] = 0x00; //00000000
  dataArrayORANGE[9] = 0x01; //00000001
  dataArrayORANGE[10] = 0x03; //00000011
  dataArrayORANGE[11] = 0x07; //00000111
  dataArrayORANGE[12] = 0x0F; //00001111
  dataArrayORANGE[13] = 0x1F; //00011111
  dataArrayORANGE[14] = 0x3F; //00111111
  dataArrayORANGE[15] = 0x7F; //01111111

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayYELLOW[0] = 0xFF; //11111111
  dataArrayYELLOW[1] = 0x7F; //01111111
  dataArrayYELLOW[2] = 0x3F; //00111111
  dataArrayYELLOW[3] = 0x1F; //00011111
  dataArrayYELLOW[4] = 0x0F; //00001111
  dataArrayYELLOW[5] = 0x07; //00000111
  dataArrayYELLOW[6] = 0x03; //00000011
  dataArrayYELLOW[7] = 0x01; //00000001
  dataArrayYELLOW[8] = 0x00; //00000000
  dataArrayYELLOW[9] = 0x01; //00000001
  dataArrayYELLOW[10] = 0x03; //00000011
  dataArrayYELLOW[11] = 0x07; //00000111
  dataArrayYELLOW[12] = 0x0F; //00001111
  dataArrayYELLOW[13] = 0x1F; //00011111
  dataArrayYELLOW[14] = 0x3F; //00111111
  dataArrayYELLOW[15] = 0x7F; //01111111

    //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayGREEN[0] = 0xFF; //11111111
  dataArrayGREEN[1] = 0x7F; //01111111
  dataArrayGREEN[2] = 0x3F; //00111111
  dataArrayGREEN[3] = 0x1F; //00011111
  dataArrayGREEN[4] = 0x0F; //00001111
  dataArrayGREEN[5] = 0x07; //00000111
  dataArrayGREEN[6] = 0x03; //00000011
  dataArrayGREEN[7] = 0x01; //00000001
  dataArrayGREEN[8] = 0x00; //00000000
  dataArrayGREEN[9] = 0x01; //00000001
  dataArrayGREEN[10] = 0x03; //00000011
  dataArrayGREEN[11] = 0x07; //00000111
  dataArrayGREEN[12] = 0x0F; //00001111
  dataArrayGREEN[13] = 0x1F; //00011111
  dataArrayGREEN[14] = 0x3F; //00111111
  dataArrayGREEN[15] = 0x7F; //01111111

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  blinkAll_2Bytes(2,500);

  //  Mozzi
//  aSin.setFreq(440);
//  aSin.setFreq(2093);

//  startMozzi(); // :))
}

void loop() {

  // TODO: There's something here that's weird that interferes with the Mozzi audio loops
  //  If this for loop is commented out we are ok.
  // As well, if we comment out the shiftOut function call it also works ok.

  // Also might have blown out a pin on the chip
  // TODO: END

  for (int j = 0; j < 15; j++) {
    //load the light sequence you want from array
    dataRED = dataArrayRED[j];
    dataORANGE = dataArrayORANGE[j];
    dataYELLOW = dataArrayYELLOW[j];
    dataGREEN = dataArrayGREEN[j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, dataGREEN);
    shiftOut(dataPin, clockPin, dataYELLOW);
    shiftOut(dataPin, clockPin, dataORANGE);
    shiftOut(dataPin, clockPin, dataRED);    
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
//    tone(7, melody[j], 300);
    delay(300);
  }

// ORIGINAL SHIFTING
//  for (int j = 0; j < 15; j++) {
//    //load the light sequence you want from array
//    dataRED = dataArrayRED[j];
//    dataORANGE = dataArrayORANGE[j];
//    dataYELLOW = dataArrayYELLOW[j];
//    dataGREEN = dataArrayGREEN[j];
//    //ground latchPin and hold low for as long as you are transmitting
//    digitalWrite(latchPin, 0);
//    //move 'em out
//    shiftOut(dataPin, clockPin, dataGREEN);
//    shiftOut(dataPin, clockPin, dataYELLOW);
//    shiftOut(dataPin, clockPin, dataORANGE);
//    shiftOut(dataPin, clockPin, dataRED);
//    //return the latch pin high to signal chip that it 
//    //no longer needs to listen for information
//    digitalWrite(latchPin, 1);
//    tone(7, melody[j], 300);
//    delay(300);
//  }

//  audioHook(); // required here
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

// Testing the first four / last four led flash
//    digitalWrite(latchPin, 0);
// First four on
//    shiftOut(dataPin, clockPin, 15);
//    shiftOut(dataPin, clockPin, 15);
//    shiftOut(dataPin, clockPin, 15);
//    shiftOut(dataPin, clockPin, 15);

// Last four on
//    shiftOut(dataPin, clockPin, 240);
//    shiftOut(dataPin, clockPin, 240);
//    shiftOut(dataPin, clockPin, 240);
//    shiftOut(dataPin, clockPin, 240);
//    digitalWrite(latchPin, 1);
//    delay(d);
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


//Mozzi Functions
//void updateControl(){
//  // read the variable resistor for volume
//  int sensor_value = mozziAnalogRead(INPUT_PIN); // value is 0-1023
//  
//  // map it to an 8 bit range for efficient calculations in updateAudio
//  volume = map(sensor_value, 0, 1023, 0, 255);  
//  
//  // print the value to the Serial monitor for debugging
//  Serial.print("volume = ");
//  Serial.println((int)volume);
//}
//
//int updateAudio(){
//  return ((int)aSin.next() * volume)>>8; // shift back into range after multiplying by 8 bit value
//}

