// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/21/19     
// Assignment: Lab 5
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include <string.h>
#include "i2c.h"
#include "timer.h"
#include "adc.h"
#include "switch.h"
#include "lcd.h"

#define DELAY 1000

typedef enum{
  WAIT_PRESS,
  WAIT_RELEASE
} states;

volatile states state = WAIT_PRESS;
boolean On = true;

int main(){
  // initADC();
  initTimer1();
  initSwitchPB3();
  initLCD();
  sei();
  //initI2C();

  int Address = 0x18; // This is the slave address
  int x = 75;
  // int y=0;
  //int temperature = 0;

  Serial.begin(9600);
  Serial.flush();

  // begin transmission by passing in our slave address 0x53
  //beginTransmission(Address);
  // write(0x01); //Writing using our power control bit
  // write(0x05);
  //write(0x00);
  //write(0x08);
  // end the transmission
  //endTransmission();

  // begin transmission by passing in our slave address 0x53
  /*beginTransmission(Address);
  write(0x2D); //Writing using our power control bit
  write(0x08);
  // end the transmission*/
  //endTransmission();

	// Serial.flush();
     //char z[]  =" ";
    while(1){
       x=x+1;
      //const char v[] ={'a'};
      // v+='a';
      // begin transmission by passing in our slave address 0x53
      //beginTransmission(Address);
      //requestFrom(0x02, Address); // Requesting from address 0x05, the "Ambient Temperature"
      //x = (read() << 8); // set z to read()'s return value, shifted 8 bits to the left 
      // end the transmission
      //endTransmission();
      
      // begin transmission by passing in our slave address
      //beginTransmission(Address);
      //requestFrom(0x05, Address);// Requesting for DATAX0 (0X32)
      //x |= read();// OR'ing the bits returned from read() with the value currently in x
      // end the transmission
      //endTransmission();
      
      // begin transmission by passing in our slave address
      /*beginTransmission(Address);
      requestFrom(y1, Address);// Requesting for DATAY1 (0X34)
      y = (read() << 8);// set y to read()'s return value, shifted 8 bits to the left 
      // end the transmission
      endTransmission();
      
      // begin transmission by passing in our slave address
      beginTransmission(Address); 
      requestFrom(y0, Address);// Requesting for DATAY0 (0X33)
      y |= read(); // OR'ing the bits returned from read() with the value currently in y
      // end the transmission
      endTransmission();*/

      //Print the X coordinate
      // Serial.print("Temperature in Celsius is:");
      // Serial.print(x);
      // Serial.print("\t");

      //Print the Y coordinate
      /*Serial.print("Temperature in Farenheit is:");
      Serial.print(y);
      Serial.print("\t");*/
      // temperature = x;
      // char msg = (char)temperature;
      switch(state){
      case WAIT_PRESS:  
      delayMs(200);
      break;
      case WAIT_RELEASE:
      delayMs(200);
      break;
    }
      moveCursor(0,4);
      char arr[10] = "";
      itoa(x,arr,10);

      writeString(arr);
      Serial.println(x);
      delayMs(1000);
    }
    return 0;
}

ISR(PCINT0_vect){
  if(state == WAIT_PRESS){
    state = WAIT_RELEASE;
  }
  else if( state == WAIT_RELEASE ){
    state = WAIT_PRESS;
    On=~On;
    if(~On){
      turnOffLCD();
      turnOffLED();
      turnOffHeatPad();
      turnOffFan();
      turnOffSpeaker();
    }
    else{
      turOnLCD();
      turOnLED();
      turOnHeadPad();
      turnOnFan();
      turnOnSpeaker();
    }

  }
  delayMs(200);
}
