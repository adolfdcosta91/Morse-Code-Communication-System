/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/

#ifndef CONTACT_H
#define CONTACT_H

class Contact{
  public:
    Contact();
    Contact(unsigned char* givenUUID, char const* givenName);
    Contact(unsigned char* givenUUID, char givenName);
    void setUUID(unsigned char* givenUUID);
    void setName(char const* givenName);
    void setName(char givenName);
    unsigned char* getUUID();
     char* getName();
    // Add as you see fit

  private:
     unsigned char* _givenUUID;
     char const* _givenName;
};

#endif
