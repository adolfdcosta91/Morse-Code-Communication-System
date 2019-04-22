/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include"Arduino.h"
class Message {
  public:
    Message();
    Message(unsigned char* from, unsigned char* to, unsigned short payload, unsigned char length);
    Message(unsigned char* from, unsigned char* to, char const* message);
    void setLength(unsigned char length);
    void setTo(unsigned char* to);
    void setFrom(unsigned char* from);
    void setPayload(unsigned short payload);
    unsigned char getLength();
    unsigned char* getTo();
    unsigned char* getFrom();
    unsigned short getPayload();
    char* getPayloadString();

  protected:
    unsigned short stringToPayload(char const* message);
    char* payloadToString(unsigned short payload, unsigned char length);

  private:
    unsigned char* _from;
    unsigned char* _to;
    unsigned short _payload;
    unsigned char _length;
    char const* _message;
};
#endif
