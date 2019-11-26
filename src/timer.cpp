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
    OCR1A = 16; // 16 for lcd display and motor fans
    OCR1A = 255; // 255 for i2c
    
}

void initTimer0LED(){
    TCCR0A&= ~(1<< WGM00);
    TCCR0A|= (1 << WGM01);
    TCCR0B&= ~(1<< WGM02);
}

/* This delays the program an amount specified by unsigned int delay using timer 0.
 * This is implemented by creating an accurate 1ms delay, which loops the total amount of
 * times specified. If we were to pass in 200, our timer would loop 200 times.
 * */
void delayMs(unsigned int delay){
OCR0A = 250; //The calculated value of the per ms delay and a 1024 prescaler
// Turning on the timer by setting the prescaler to 1024
TCCR0B |= (1 << CS01) | (1 << CS00);
TCCR0B &= ~(1 << CS02); 
TIFR0 |= (1 << OCF0A); // set the flag down
TCNT0 = 0; // This clears the timer.
int delaycount = 0;

while(delaycount < delay){
    // while flag is up, we will increase the delay count.
    if((TIFR0 & (1 << OCF0A))){
        // set the flag as down.
        TIFR0 |= (1 << OCF0A);
    delaycount=delaycount + 1;
    }
}
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
