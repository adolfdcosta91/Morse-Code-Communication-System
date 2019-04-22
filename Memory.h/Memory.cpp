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
#include "Memory.h"
#include "EEPROM.h"

Memory::Memory(){}

void Memory :: write_EEPROMMessage(int MessageNumber, char const* Message)
{
    int addressLocationM=174;
    int addressoffsetM=13;
    int addressCounterM=0;
    char add;

    if(MessageNumber!=0)
     {
      add = ((MessageNumber*addressoffsetM)+addressLocationM);
     }

    if (MessageNumber==0)
    {
      addressCounterM = EEPROM.read(173);

      add = ((addressCounterM*addressoffsetM)+addressLocationM);
    }

    int _size = 12;
    int i;
    for(i=0;i<_size;i++)
    {
      EEPROM.write(add+i,Message[i]);

    }
      EEPROM.write(add+_size,'\0');
      addressCounterM++;
      if (addressCounterM > 20) addressCounterM =0; //restting the counter after it reaches the max value
      EEPROM.write(173,addressCounterM);
}


String Memory :: read_EEPROMMessage(int MessageNumber)
{

    int i;
    int intialMessageAddress=174;
    int MessageOffset=13;
    char addMessage;
    addMessage = (MessageOffset * MessageNumber) + intialMessageAddress ;
    char MessageData[100];// a change from 100 to 12
    char const* MessageData1 = MessageData;
    int Messagelen=0;
     char k;
    k=EEPROM.read(addMessage);
    while(k != '\0' && Messagelen<500)
    {
      k=EEPROM.read(addMessage+Messagelen);
      MessageData[Messagelen]=k;
      //MessageData1[Messagelen] = EEPROM.read(addMessage+Messagelen);
      Messagelen++;
    }
    //MessageData[Messagelen]='\0';
    //return MessageData1;
    return String(MessageData);
}



String Memory ::  read_EEPROMName(int NameNumber)
{
  int i;
  int intialNameAddress=27;
  int NameOffset=15;
  char addName;
  addName = (NameOffset * NameNumber) + intialNameAddress ;
  char nameData[100];
  int namelen=0;
  unsigned char k;
  k=EEPROM.read(addName);
  while(k != '\0' && namelen<500)
  {
    k=EEPROM.read(addName+namelen);
    nameData[namelen]=k;
    namelen++;
  }
  nameData[namelen]='\0';

  return String(nameData);
}


String Memory :: read_EEPROMUUID(int UUIDNumber)

{
  int i;
  int intialUUIDAddress=21;
  int UUIDOffset=15;
  char addUUID;
  addUUID = (UUIDOffset * UUIDNumber) + intialUUIDAddress ;
  char UUIDdata[100];
  int UUIDlen=0;
  unsigned char k;
  k=EEPROM.read(addUUID);
  while(k != '\0' && UUIDlen<500)
  {
    k=EEPROM.read(addUUID+UUIDlen);
    UUIDdata[UUIDlen]=k;
    UUIDlen++;
  }
  UUIDdata[UUIDlen]='\0';

  return String(UUIDdata);

}




void Memory :: write_EEPROMContact(char addContact,unsigned char* UUIDdata, const char* Namedata)
{
  int shiftUUIDToAdd=6;
  int addressLocationC=21;
  int addressoffsetC=15;
  int addressCounterC=0;
  char add;

  if (addContact==0)
    {
     addressCounterC = EEPROM.read(20);
     add = ((addressCounterC*addressoffsetC)+addressLocationC);
    }

  if (addContact!=0)
    {
     add = ((addContact*addressoffsetC)+addressLocationC);
    }

  int _size = 5; //data.length();
  int i;
  for(i=0;i<_size;i++)
  {
    EEPROM.write(add+i,UUIDdata[i*2]);
  }
  EEPROM.write(add+_size,'\0');



  int _sizeName = 8; //data.length();
  int j;
  add=add+shiftUUIDToAdd;
  for(j=0;j<_sizeName;j++)
  {
    EEPROM.write(add+j,Namedata[j]);
  }
  EEPROM.write(add+_sizeName,'\0');

  addressCounterC++;
  EEPROM.write(20,addressCounterC);

}

void Memory :: Erase()
{
 for (int i = 0; i < 1024; i++)
  {
    EEPROM.write(i, 0);
  }
}

/*
  write_EEPROMMessage(Message # , Message in Char );
  read_EEPROMMessage(Message #);
  write_EEPROMContact(Contact location ,UUID of Name , Name );
  read_EEPROMName(Name # to be retrived);
  read_EEPROMUUID(Conact UUID # to be retrived);
  Erase();  TO erase the EEPROM

  while using the write function if the location is left to zero note that the processor will store the data sequentially in next contact or message location else you can specify the
  location which you want to store as well.

  Note : EEPROM.begin();
         Serial.begin(9600);

  Above to commands are necessary to be placed in the voidsetup()

*/
