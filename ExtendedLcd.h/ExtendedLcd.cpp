/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/


#include"Arduino.h"
#include "LiquidCrystal.h"
#include "ExtendedLcd.h"



ExtendedLcd::ExtendedLcd() : LiquidCrystal(8, 9, 4, 5, 6, 7) {}

Button ExtendedLcd::getButtonPress()

{
  int analogPinConnected = analogRead(0); //Reading the value at analog pin zero
if (analogPinConnected>1000);  // If no button is pressed 1 is returned
delay(35);
if (analogPinConnected>1000);
if (analogPinConnected<50);    //For "Right Button"
delay(35);
if (analogPinConnected<50) return RIGHT;
if (analogPinConnected<250);   //For "UP Button"
delay(35);
if (analogPinConnected<250) return UP;
if (analogPinConnected<450);   //For "Down Button"
delay(35);
if (analogPinConnected<450) return DOWN;
if (analogPinConnected<650);   //For "Left Button"
delay(35);
if (analogPinConnected<650) return LEFT;
if (analogPinConnected<850);   //For "Select Button"
delay(35);
if (analogPinConnected<850) return SELECT;
  }
