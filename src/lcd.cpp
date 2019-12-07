// Author: Ariel Villasenor
// Net ID: arielv
// Date: 10/14/19
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>
#include <stdio.h>
//#include <iostream>


/*
 * Initialize PA0, PA1, PA2, and PA3 to outputs
 * Initializing B4 for and B6 for
*/
void initLCDPins(){
  DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
  DDRB |= (1 << DDB4) | (1 << DDB6);
  DDRG |= (1 << DDG0) | (1 << DDG1);
}

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay){
  PORTA = (data & 0x0F);                  // 1. Sending the bottom 4 bits of data
  PORTB &= ~(1 << PORTB6);                // 2. Set RS pin to low 
  PORTB |= (1 << PORTB4);                 // 3.1 Set EN pin to high
  delayUs(1);                             // 3.2 Set 1 microsecond delay
  PORTB &= ~(1 << PORTB4);                // 3.3 Set EN pin to low
  delayUs(delay);                         //4.
}

/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  PORTA = ((command & 0xF0) >> 4);        // 1. Sending the top 4 bits of "command" first. 
  PORTB &= ~(1 << PORTB6);                // 2. Set RS pin to low
  PORTB |= (1 << PORTB4);                 // 3.1 Set EN pin to high
  delayUs(1);                             // 3.2 Set 1 microsecond delay
  PORTB &= ~(1 << PORTB4);                // 3.3 Set EN pin to low

  PORTA = (command & 0x0F);               // 1. Sending the bottom 4 bits of "command".
  PORTB &= ~(1 << PORTB6);                // 2. Set RS pin to low
  PORTB |= (1 << PORTB4);                 // 3.1 Set EN pin to high
  delayUs(1);                             // 3.2 Set 1 microsecond delay
  PORTB &= ~(1 << PORTB4);                // 3.3 Set EN pin to low
  delayUs(delay);            
}

/* Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high                          [X]
 * 3. Assert high on enable pin, delay, and asset low on enable pin               [X]
 * 4. Now set the lower four bits of character to appropriate bits in PORTA     
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void writeCharacter(unsigned char character){
  PORTA = (character >> 4);               // sending the top 4 bits of "character" first.
  PORTB |= (1 << PORTB4);                 //3. Assert high on enable pin
  PORTB |= (1 << PORTB6);                 //2. This is a "data" signal, meaning RS will be high
  delayUs(1);                             //3. delay for microsecond
  PORTB &= ~(1 << PORTB4);                //3. Assert low on enable pin
  
  PORTA = character;                      // sending the bottom 4 bits of "character" next
  PORTB |= (1 << PORTB4);                 //3. Assert high on enable pin
  delayUs(1);                             //3. delay for microsecond
  PORTB &= ~(1 << PORTB4);                //3. Assert low on enable pin
  delayUs(46);                            // delay for 46 microseconds
}

/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void writeString(const char *string){
  while (*string != '\0'){
        writeCharacter(*string);  // passing the character to the writeCharacter function
        string++;                 // increment through the array of characters
    }
}

/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void moveCursor(unsigned char x, unsigned char y){
  unsigned char DDRAM = y | x;
  //unsigned char DDRAM = 0x80 | x<<6;
	eightBitCommandWithDelay(0x80 + DDRAM, 46); //Attempts to turn on LCD Display
}


/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  // Delay 15 milliseconds
  delayUs(15000); //delays the clock 15 ms

  // Write 0b0011 to DB[7:4] and delay 4100 microseconds
  fourBitCommandWithDelay(0b0011, 4100);

  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0b0011, 100);

  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  
  // write 0b0011 to DB[7:4] and 100us delay
  fourBitCommandWithDelay(0b0011, 100);
  
  // write 0b0010 to DB[7:4] and 100us delay.
  fourBitCommandWithDelay(0b0010, 100);

  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0b00101100, 53); // Does function set from the data sheet

  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0b00001010, 53); // Supposed to turn off the display

  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0b00000001, 1640); // Supposed to clear the display

  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0b00000110, 53); // Set Increment to 1, set Display shift to 0

  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  eightBitCommandWithDelay(0b00001101, 53 ); 
}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();  // Initializes needed pins.
  turnOnLCD();
  initLCDProcedure();
}

void turnOffLCD(){
  PORTG |= (1<<PORTG0);
  PORTG &= ~(1<<PORTG1);
}

void turnOnLCD(){
  PORTG &= ~(1 << PORTG0);
  PORTG |= (1 << PORTG1);
}
  
