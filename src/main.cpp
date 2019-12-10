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
  sei();
  initPWMTimer3();
  initPWMTimer4();
  initPWMTimer5();

  float temperature = 0;
  Serial.begin(9600);
  Serial.flush();

    if (!tempsensor.begin()){
    Serial.println("Couldn't find MCP9808!");
    while (1);
      }
    while(1){
      float c = tempsensor.readTempC();
      temperature = c * 9.0 / 5.0 + 32;
       char arr[10] = "";

        if(On == 0){
          turnOffFan();
        }
        else{
          /*If h*/
        if(temperature >= 77){
        turnOffLED();
        delayMs(1000);
        IncFrequency(4000);
        turnOnLED(1);
        if(temperature >= 85 && temperature < 95){
          changeDutyCycleFan(4.0);
        }
        else if(temperature >=95){
          changeDutyCycleFan(5.0);
        }
        else{
          changeDutyCycleFan(3.0);
        }
      }
      else if(temperature <= 70){
        turnOffLED();
        delayMs(1000);
        turnOnLED(2);
        IncFrequency(4000);
        if(temperature <= 65 && temperature > 60){
          changeDutyCycleHeater(4.0);
        }
        else if(temperature <= 60){
          changeDutyCycleHeater(5.0);
        }
        else{
          changeDutyCycleHeater(3.0);
        }
      }
      else{
        turnOffLED();
        IncFrequency(0);
        changeDutyCycleFan(0.0);
      }
        }
      /******************************************************** WAIT_PRESS ************************************************************/
      switch(state){
      case WAIT_PRESS:  
      moveCursor(0,4);
      itoa(temperature,arr,10);
      writeString(arr);
      delayMs(1000);
      Serial.println(On);
      break;

      /******************************************************** WAIT_RELEASE ************************************************************/
      case WAIT_RELEASE:
      moveCursor(0,4);
      itoa(temperature,arr,10);
      writeString(arr);
      delayMs(1000);
      break;
    }
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
    }
    else{
      On = 1;
      turnOnLCD();
    }

  }
  delayMs(200);
}


