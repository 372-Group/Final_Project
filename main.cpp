// Author: Jessmer Palanca , Ariel Villasenor, Lu Yu
// Net ID: jjpalanca, arielv, lyu18    
// Date: 11/21/19     
// Assignment: Lab 5
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "i2c.h"
#include "timer.h"
#define DELAY 1000

typedef enum coordinates {x0 = 0x32, x1 = 0x33, y0=0x34, y1=0x35, z0=0x36, z1=0x37};

int main(){
  int Address = 0x53; // This is the slave address
  int x=0;
  int y=0;
  int z=0;

  Serial.begin(9600);
  Serial.flush();
  sei();
  initTimer1();
  initI2C();

  /* begin transmission by passing in our slave address 0x53*/
  beginTransmission(Address);
  write(0x2D); //Writing using our power control bit
  write(0x00);
  /* end the transmission*/
  endTransmission();

  /* begin transmission by passing in our slave address 0x53*/
  beginTransmission(Address);
  write(0x2D); //Writing using our power control bit
  write(0x08);
  /* end the transmission*/
  endTransmission();

	Serial.flush();

    while(1){
      /* begin transmission by passing in our slave address 0x53*/
      beginTransmission(Address);
      requestFrom(x1, Address); // Requesting for DATAX1 (0X33)
      x = (read() << 8); // set z to read()'s return value, shifted 8 bits to the left 
      /* end the transmission*/
      endTransmission();
      
      /* begin transmission by passing in our slave address*/
      beginTransmission(Address);
      requestFrom(x0, Address);// Requesting for DATAX0 (0X32)
      x |= read();// OR'ing the bits returned from read() with the value currently in x
      /* end the transmission*/
      endTransmission();
      
      /* begin transmission by passing in our slave address*/
      beginTransmission(Address);
      requestFrom(y1, Address);// Requesting for DATAY1 (0X34)
      y = (read() << 8);// set y to read()'s return value, shifted 8 bits to the left 
      /* end the transmission*/
      endTransmission();
      
      /* begin transmission by passing in our slave address*/
      beginTransmission(Address); 
      requestFrom(y0, Address);// Requesting for DATAY0 (0X33)
      y |= read(); // OR'ing the bits returned from read() with the value currently in y
      /* end the transmission*/
      endTransmission();

      /* begin transmission by passing in our slave address*/
      beginTransmission(Address);
      requestFrom(z1, Address);// Requesting for DATAZ1 (0X36)
      z = (read() << 8); // set z to read()'s return value, shifted 8 bits to the left 
      /* end the transmission*/
      endTransmission();
      
      /* begin transmission by passing in our slave address*/
      beginTransmission(Address);
      requestFrom(z0, Address);// Requesting for DATAZ0 (0X35)
      z |= read(); // OR'ing the bits returned from read() with the value currently in z
      /* end the transmission*/
      endTransmission();

      /*Print the X coordinate*/
      Serial.print("X = ");
      Serial.print(x);
      Serial.print("\t");

      /*Print the Y coordinate*/
      Serial.print("Y = ");
      Serial.print(y);
      Serial.print("\t");

      /*Print the Z coordinate*/
      Serial.print("Z = ");
      Serial.println(z);
      delayMs(1000);

    }
    return 0;
}

