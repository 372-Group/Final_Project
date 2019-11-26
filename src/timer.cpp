// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/21/19     
// Assignment: Lab 5
//----------------------------------------------------------------------//

#include "timer.h"
#include <Arduino.h>

/* Initializing timer 1. Using CTC mode  .*/
// this timer is for the motor fan and lcd
void initTimer1(){
    TCCR1A&=~(1<<WGM10);
    TCCR1A&=~(1<<WGM11);
    TCCR1B|=(1<<WGM12);
    TCCR1B&=~(1<<WGM13);
    
    // Here we are setting our prescaler to 1.
    TCCR1B&=~(1<<CS12);
    TCCR1B&=~(1<<CS11);
    TCCR1B|=(1<<CS10);
    
    // This sets our output compare register to 16, thus allowing us to have 1 microsecond delay
    OCR1A = 16;
    
}

// this timer is for the i2c
void initTimer1(){
    TCCR1A&=~(1<<WGM10);
    TCCR1A&=~(1<<WGM11);
    TCCR1B|=(1<<WGM12);
    TCCR1B&=~(1<<WGM13);
    
    // Here we are setting our prescaler to 64.
    TCCR1B |= (1<<CS11) | (1<<CS10);
    TCCR1B &= ~(1<<CS12);
    
    // This sets our output compare register to 16, thus allowing us to have 1 microsecond delay
    OCR1A = 16000/64;
    
}

/* This delays the program an amount specified by unsigned int delay.
 */
// delay for the motor fan and lcd
void delayUs(unsigned int delay){
    //setthecounterto0
    TIFR1|=(1<<OCF1A);

    TCNT1=0;
    unsigned int count = 0;
    
    while(count<delay){
        if((TIFR1&(1<<OCF1A))){//increment everytime the timerr aises a flag
            count++;
            TIFR1|=(1<<OCF1A);//set timer to start counting again
        }
    }   
}

// delay for the i2c
void delayMs(unsigned int delay){
    //setthecounterto0
    TIFR1|=(1<<OCF1A);

    TCNT1=0;
    unsigned int count = 0;
    
    while(count<delay){
        if((TIFR1&(1<<OCF1A))){//increment everytime the timerr aises a flag
            count++;
            TIFR1|=(1<<OCF1A);//set timer to start counting again
        }
    }   
}
