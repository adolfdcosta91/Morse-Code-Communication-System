/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/

#include "Arduino.h"
#include "Contact.h"


    Contact::Contact() {}
    Contact::Contact(unsigned char* givenUUID, char const* givenName)
    {
      _givenUUID = givenUUID;
      _givenName =  givenName;
    }
    Contact::Contact(unsigned char* givenUUID, char givenName)
    {
      _givenUUID = givenUUID;
      _givenName =  &givenName;
    }
    void Contact::setUUID(unsigned char* givenUUID)
    {
      _givenUUID = givenUUID;
    }
    void Contact::setName(char const* givenName)
    {
      String mymy;
      if (sizeof(*givenName) > 11)
      mymy = *givenName;
      mymy.remove(10);
      _givenName = mymy.c_str();

        }
    void Contact::setName(char givenName)
    {
      _givenName = &givenName;
    }
    unsigned char* Contact::getUUID()
    {
      return _givenUUID;
    }
     char* Contact::getName()
    {
      char* __givenName;
      __givenName = (char*) _givenName;
      return __givenName;
    }
