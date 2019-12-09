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
#include "led.h"
#include "pwm.h"
#include "beeper.h"
#include <Wire.h>
#include "Adafruit_MCP9808.h"
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

#define DELAY 1000

typedef enum{
  WAIT_PRESS,
  WAIT_RELEASE
} states;

volatile states state = WAIT_PRESS;
int On = 1;

int main(){
  initADC();
  initTimer1();
  initSwitchPB3();
  initLCD();
  initLED();
  initBeeper();
  sei();
  initPWMTimer3();
  initPWMTimer4();
  initPWMTimer5();
  //initI2C();

  float voltage;
  int Address = 0x18; // This is the slave address
  //int x = 75;
  // int y=0;
  float temperature = 0;
  int beeped = 0;
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

    if (!tempsensor.begin()){
    Serial.println("Couldn't find MCP9808!");
    while (1);
      }
    while(1){
      float c = tempsensor.readTempC();
      temperature = c * 9.0 / 5.0 + 32;
       char arr[10] = "";
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

        if(On == 0){
          turnOffFan();
          turnOffBeeper();
          Serial.println(On);
        }
        else{
      if(temperature >= 80){
        delayMs(1000);
        turnOnLED(1);
        IncFrequency(2000);
        if(temperature >= 90 && temperature < 100){
          changeDutyCycleFan(9.5);
          Serial.print(">=90");
        }
        else if(temperature >=100){
          changeDutyCycleFan(10.0);
          Serial.print(">=100");
        }
        else{
          changeDutyCycleFan(9.0);
          Serial.print(">=80 < 90");
        }
      }
      else if(temperature <= 70){
        turnOffLED();
        delayMs(1000);
        turnOnLED(2);
        IncFrequency(2000);
        if(temperature <= 60 && temperature > 50){
          changeDutyCycleHeater(10.0);
        }
        else if(temperature <= 50){
          changeDutyCycleHeater(20.0);
        }
        else{
          changeDutyCycleHeater(5.0);
        }
      }
      else{
        turnOffLED();
        changeDutyCycleFan(0.0);
      }
        }
      /******************************************************** WAIT_PRESS ************************************************************/
      switch(state){
      case WAIT_PRESS:  
      moveCursor(0,4);
      itoa(temperature,arr,10);
      writeString(arr);
      Serial.print(temperature);
      Serial.print("\t");
      delayMs(1000);
      Serial.println(On);
      break;

      /******************************************************** WAIT_RELEASE ************************************************************/
      case WAIT_RELEASE:
      moveCursor(0,4);
      itoa(temperature,arr,10);
      writeString(arr);
      Serial.print(temperature);
      delayMs(1000);
      break;
    }
      
      /*if(temperature > 80){
        turnOnBeeper();
        if(~beeped){
          BeeperMakeNoise();
          beeped = 1;
        }
        turnOffHeatPad();
        turnOnFan();
        changeFan(temperature);
      }
      else if(temperature < 70){
        turnOnBeeper();
        if(~beeped){
          BeeperMakeNoise();
          beeped = 1;
        }
        turnOffFan();
        turnOnHeatPad();
        changeHeatPad(temperature);
      }
      else{
        turnOffHeatPad();
        turnOffFan();
        turnOffBeeper();
        turnOffRedLED();
        turnOffGreenLED();
        beeped = 0;
      }*/
    }
    return 0;
}

ISR(PCINT0_vect){
  if(state == WAIT_PRESS){
    state = WAIT_RELEASE;
  }
  else if( state == WAIT_RELEASE ){
    state = WAIT_PRESS;
    if(On == 1){
      On = 0;
      turnOffLCD();
      turnOffLED();
      //turnOffHeatPad();
      //turnOffFan();
      //turnOffBeeper();
    }
    else{
      On = 1;
      turnOnLCD();
      //initLED();
      //turOnHeadPad();
      //turnOnFan();
      //turnOnBeeper();
    }

  }
  delayMs(200);
}


