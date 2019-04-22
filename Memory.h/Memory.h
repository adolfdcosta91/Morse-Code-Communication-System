/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/

#ifndef Memory_h
#define Memory_h

#include "Arduino.h"
#include <EEPROM.h>

class Memory
{
  public:
  Memory();
  void write_EEPROMMessage(int MessageNumber, char const* Message);
  String read_EEPROMMessage(int MessageNumber);
  void write_EEPROMContact(char addContact,unsigned char* UUIDdata, const char* Namedata);
  String read_EEPROMName(int NameNumber);
  String read_EEPROMUUID(int UUIDNumber);
  void Erase();

  char addContact;
  unsigned char* UUIDdata;
  const char* Namedata;
  int shiftUUIDToAdd;
  int _sizeName;
  int j;
  int addressLocationC;
  int addressoffsetC;
  int addressCounterC;

  int intialNameAddress;
  int NameOffset;
  char addName;
  char nameData;
  int namelen;

  int intialUUIDAddress;
  int UUIDOffset;
  char addUUID;
  int UUIDlen;

  int intialMessageAddress;
  int MessageOffset;
  char addMessage;
  char MessageData;
  int Messagelen;
  unsigned char k;

  int addressLocationM;
  int addressoffsetM;
  int addressCounterM;
  char add;
  int _size;
  int i;
  int addtest;
  int countertest;
};
#endif
