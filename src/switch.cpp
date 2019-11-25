// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/03/19     
// Assignment: Lab 4
// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 * Pin 50
 */
void initSwitchPB3(){
    // Set switch 50 as pull-up enabled input
    PORTB |= (1 << PORTB3);
    DDRB &= ~(1 << DDB3);

    PCICR |= (1 << PCIE0); // enable PCINT 0 - 7
    PCMSK0 |= (1 << PCINT3); // enable PCIN
}
