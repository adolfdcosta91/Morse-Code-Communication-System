/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/
#include"Message.h"
#include"Arduino.h"

Message::Message() {}
Message::Message(unsigned char* from, unsigned char* to, unsigned short payload, unsigned char length)
{
  _from = from;
  _to = to;
  _payload = payload;
  _length = length;
}
Message::Message(unsigned char* from, unsigned char* to, char const* message)
{
  _from = from;
  _to = to;
  _payload = stringToPayload(message);
  String myString = String(_payload);
  _length = myString.length();
}
void Message::setLength(unsigned char length)
{
  _length = length;
}
void Message::setTo(unsigned char* to)
{
  _to = to;
}
void Message::setFrom(unsigned char* from)
{
  _from = from;
}
void Message::setPayload(unsigned short payload)
{
  _payload = payload;
}
unsigned char Message::getLength()
{
  return _length;
}
unsigned char* Message::getTo()
{
  return _to;
}
unsigned char* Message::getFrom()
{
  return _from;
}
unsigned short Message::getPayload()
{
  return _payload;
}
char* Message::getPayloadString()
{
  return payloadToString(_payload, _length);
}

unsigned short Message::stringToPayload(char const* message)
{
  char *myString;
  strncpy(myString,message,2);
  _payload = (unsigned short) strtoul(myString, NULL, 0);
  return _payload;
}
char* Message::payloadToString(unsigned short payload, unsigned char length)
{
  String myString = String(payload);
char _myString [length+1];

  return strcpy(_myString,myString.c_str());
}
