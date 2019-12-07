// Author: Ariel Villasenor     
// Net ID: arielv
// Date: 9/14/19
// Assignment: Lab 1
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

// initLED which returns void and takes no parameters. Initializes pins 4 -11
void initLED(){
  // Initialize pins 4-11 on the development board to outputs
  DDRG |= (1 << DDG2);
  DDRD |= (1 << DDD7);
}

void turnOnLED(int led){
if(led == 1){
    PORTD |= (1 << DDD7); // Hot LED
}
else{
    PORTG |= (1 << DDG2);
}
}
void turnOffLED(){
    PORTG &= ~(1 << DDG2);
    PORTD &= ~(1 << DDD7);
}