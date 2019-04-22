/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/


#ifndef ExtendedLcd_h
#define ExtendedLcd_h

#include"Arduino.h"
#include <LiquidCrystal.h>

typedef enum {LEFT, RIGHT, UP, DOWN, SELECT, NONE} Button;


class ExtendedLcd : public LiquidCrystal{
    public:
          ExtendedLcd();
          Button getButtonPress();
          int analogPinConnected;

};
#endif
