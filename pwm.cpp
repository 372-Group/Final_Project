// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18
// Date: 11/03/19     
// Assignment: Lab 4
// Description: The is the execution file for pulse width modulation
//----------------------------------------------------------------------//

#include "pwm.h"
#include <avr/io.h>


/* The changeDutyCycle will be changing the amount of
 * voltage that is being sent. If we have 50% duty cycle in a 5v
 * system, 2.5 will be sent out.*/
void changeDutyCycle(double num){
    /* If the passed in voltage is between 2.00 and 3.00,
     * we will make both motors go at full speed.
     */
    if (num>2.00 && num<3.00){
        OCR3A = 1023;
        OCR4A = 1023;
    }
    else{
    /*percent is the voltage/5 . 
     * OCR3A is then set to (percentage * 1023)
     * OCR4A is then set to (1 - percentage) * 1023 
     * */
    float percent;
    percent = num / 5;
    OCR3A = percent * 1023;
    OCR4A = (1 - percent) * 1023;
    }
}

/*Turns off both motors*/
void turnOff(){
    OCR3A = 0;
    OCR4A = 0;
}

void initPWMTimer3(){
    DDRE |= (1 << DDE3);/*Assigning to pin 5 */
    /*Set Fast PWM to 10-bit mode for timer 3*/
    TCCR3A |= (1 << WGM30) | (1 << WGM31) | (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);
    /*CS30 sets the prescaler bits to 1*/
    TCCR3B |= (1 << WGM32) | (1 << CS30);
    OCR3A = 1023;/*Our output compare register is 1023*/
}

void initPWMTimer4(){
    DDRH |= (1 << DDH3);/*Assigning to pin 6 */
    /*Set Fast PWM to 10-bit mode for timer 4*/
    TCCR4A |= (1 << WGM40) | (1 << WGM41) | (1 << COM4A1);
    TCCR4A &= ~(1 << COM4A0);
    /*CS40 sets the prescaler bits to 1*/
    TCCR4B |= (1 << WGM42) | (1 << CS40);
    OCR4A = 1023;/*Our output compare register is 1023*/
}