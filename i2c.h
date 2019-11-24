// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/21/19     
// Assignment: Lab 5
//----------------------------------------------------------------------//
#ifndef I2C_H
#define I2C_H

void initI2C();
void beginTransmission(int num);
void endTransmission();
char read();
void write(int num);
void requestFrom(int num1, int num2);

/* If the implementation of these functions 
 * overlap, this is fine.
 * */

#endif
