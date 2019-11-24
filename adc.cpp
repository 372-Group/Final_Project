// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/03/19     
// Assignment: Lab 4
// Description: This is the execution file for the Analog to Digital Converter
//----------------------------------------------------------------------//

#include "adc.h"
#include <avr/io.h>

//a 8-level ADC has a bit-depth of 3. 
//Arduino has a bit-depth of 10.

/* steps to set up the adc
1. configure ADCSRA
- Choose input channel, mode (single-ended or differential), and gain (if applicable) using ADMUX bits 3-0.
- Choose VREF(AREF,AVCC, or internal 2.56 Vref) using ADMUX bits 7-6
- Choose left or right alignment of conversion result in ADC Data Register using ADMUX bit 5
- Choose to enable or disable ADC auto-trigger using ADCSRA bit 5. If enabled, you then need to set bits 7-5 in SFIOR to 
select the auto-trigger source
- Choose to enable or disable ADC interrupt using ADCSRA bit 3. 
    If enabled, you will alos need to enable Global interrupt in order for the ADC Interrupt to be acted upon
    (SREG |= (1 << SREG_l);). You will also need an ISR to service the interrupt <=""="">
- Choose the clock prescaler using ADCSRA bits 2-0
- Turn on the ADC using ADCSRA bit 7:
    1 to turn on; 0 to turn off.
2. start a Conversion: 
    write a 1 to bit-6 of ADCSRA to start a conversion
3. COnversion Complete Check
- Either by ADC Interrupt or by checking bit 6 of ADCSRA (conversion is complete when this bit is 0)
or by checking bit 4 of ADCSRA (conversion is complete when this bit is 1)
*/

// initSwitch returns void and takes no parameters
void initADC(){
    // set voltage references to be AVCC. datasheet page 281
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // ADLAR = 0 (RIGHT JUSTIFIED)
    ADMUX &= ~(1 << ADLAR);

   // Set ADC0 as single-ended input with MUX[5:0] = 0b000000
   //datasheet page 282, table 26-4
   ADMUX &= ~(1 << MUX2) | (1 << MUX1) | (1 << MUX0);
   ADMUX &=  ~(1 << MUX4);
   ADMUX &=  ~(1 << MUX3);
   ADCSRB &= ~(1 << MUX5);

   // set Auto Trigger Source Selection. datasheet page 287
   // set to free-running mode ADTS[2:0] = 0b000
   ADCSRB &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);

   // enable auto-triggering and turn-on ADC, datasheet page 285
   ADCSRA |= (1 << ADATE) | (1 << ADEN);

   // set the pre-scaler to 128, datasheet page 285
   // ADC clock frequency is 16 Mhz divided by pre-scaler = 125KHz
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

   // disable ADC0 pin digital input - pin A0 on board
   //DIDR0 |= (1 << ADC7D);
   DIDR0 |= (1 << ADC0D);
   

   // start the first conversion
   ADCSRA |= (1 << ADSC);
}
