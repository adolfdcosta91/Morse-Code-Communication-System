/* 
Developed and Created by 
Name: Adolf A D'costa & Ahmed Alhazmi 
Project: Morse Beeper 
Hardware: Arduino Uno, LDC with buttons and nRF24L01+(2.4Ghz-2.5Ghz Tx/Rx)
Date: 10th March 2019
Project Goal: Arduino has the ability to store Messages and Contacts with UUID and send Morse code using nRF24L01+, Also has an LCD screen with button to display and scroll 
			  Most libraries were developed and modified for the project. 
*/

#include<Arduino.h>
#include"Contact.h"
#include"Message.h"
#include"Memory.h"
#include"ExtendedLcd.h"
#include"EEPROM.h"
#include<RF24.h>
#include<Entropy.h>



  ExtendedLcd _lcd;
    int CursorPos = 0;
  //Button _button = NONE;
  int States = 0; //0: Setup, 1: Menu , 2: Contacts, 3: Messages, 4: New Contact, 5: About me
                  // 6: Composing a message, 7: result of sending the message"success/failure + result of adding a contact
                  //8: Display Stored Messages, 9: result of adding a contact,, 10: Interrupt for message reception
  int testDown = 5;
  Button _button = NONE;



unsigned char * UUID1 = (unsigned char*) "0";
unsigned char * UUID2;
unsigned char * UUID3; // for new contact

  int Char = 'a';
  String Main_Options [] {"Contacts ","Messages ","N.Contact", "About Me "};
  String Contacts [] {"Ahmed", "Adolf", "Sunny", "Noor "};
  String readEeprom [] = "";
  String MessageOutcome [] {"Messge Sent  !", "Message Failed !"};
  bool messageOutcome =true; // true: sent, false:failed
  String MessageSentFrom [] {"Sent: ", "From: "};
  String  HexLetters []   {"1","2","3","4","5","6","7","8","9","A","B","C","D","E","F", "0"};
  //char  HexLetters =   {"123456789ABCDEF0"};
  int OwnerName [] = {1,2,3,4,5,6,7,8,9,9};
  int ContactName [] = {1,2,3,4,5,6,7,8,9,9};
  int Ncount =0, NNcount=0; // for skipping through the name's positions of the owner, NN: for new contact
  int MorseCode_0 = '.';
  int MorseCode_1 = '-';
  int MorseCode_2 = ' ';
  int Options =0, OptionsCon =0;
  int tempOptionsCon;
  int tempOptions =0;
  int Ctr; //might be deleted?
  unsigned short max_Contact = 10;
  int  newUUID =0; // newUUID =1 => switch to new UUID screen
  int Hex =0;
  char  newCName [] = {};
 // newCName [11];
  Memory Eeprom;
  String SendUUId;
 String conUUID;
 int countUUID;
 //unsigned char _UUID [6];
 char test0,test1,test2,test3,test4,test5,test6,test7,test8,test9;
 int increment = 0;
 int eepromread = 0;
 
 
 
RF24 radio(A4,A5);
char messagerecivied[100] = "";
char morseMessage [14] = "";
int morseCount =0;
bool PipeNum = true; // pipes 
bool tx, rx, rx_ready;
byte addresses[][6] = {"0003E","000DD"}; //UUID address will be added here

  

//following is for time-out
unsigned long count = 0;
unsigned long time;
boolean pressingButton = false, Owner = true;



void setup() {
  Serial.begin(9600);
  Entropy.initialize();
  EEPROM.begin();
  _lcd.begin(16,2);
  //UUID2 = GeneratedUUID();
  _lcd.setCursor(0,0);
  _lcd.print("Enter your name");
  _lcd.setCursor(0,1);
  _lcd.write(Char);
  radio.begin();
  radio.maskIRQ(1,1,0);

  radio.setPALevel(RF24_PA_LOW);
  
  
  if(PipeNum == true){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  radio.startListening(); // will be stopped when we want to transmit
 attachInterrupt(0,Int_Servc_Rut,FALLING);
}

void loop() {


  if (States == 0) //Setup
  {

if (CursorPos == 9) CursorPos =0;
_lcd.setCursor(CursorPos,1);
  

 typingName();

  

 if (_button == SELECT){
        // expirment for writing to memory

        //char const* hello = {"hi there ahmed"};
    
        //Eeprom.write_EEPROMMessage(0,"hi there");
        //Eeprom.write_EEPROMMessage(1,"this is");
        //Eeprom.write_EEPROMMessage(0,"quik testing");
        //Eeprom.write_EEPROMMessage(3,"messages");
        Eeprom.write_EEPROMMessage(0,"quik testing");
        
        OwnerName[Ncount] = Char;
       // else if (!Owner) 
       Owner = false;
        changingState(1);
        UUID1 = GeneratedUUID();
       }
}

if (States ==1) //Menu
{
   // String t;
  //t = String(Eeprom.read_EEPROMMessage(0));

          //Eeprom.write_EEPROMMessage(0,"messages");


  //for (int i =0; i< sizeof(t); i++) 
//  Serial.println(t);

  
  
  pressingButton =false;
    //Setting up the menu screen
  _lcd.setCursor(0,0);
  _lcd.print("Main Menu");
  _lcd.setCursor(0,1);
  _lcd.print("<-");
  _lcd.setCursor(14,1);
 _lcd.print("->");

    _button = _lcd.getButtonPress();

if (_button == RIGHT){
    //test
    //_lcd.clear();
        _lcd.setCursor(3,1);
        _lcd.print(Main_Options[Options]);
        tempOptions = Options;
        Options++;
       _button = _lcd.getButtonPress();
       //_lcd.clear();
        if (Options >3 || Options <0) Options =0;
       }
 if (_button == LEFT){
  //_lcd.clear();
       _lcd.setCursor(3,1);
        _lcd.print(Main_Options[Options]);
         tempOptions = Options;
         Options--;
  if (Options <0) Options =3;
 _button = _lcd.getButtonPress();
 //_lcd.clear();
 }


 if (_button == SELECT){ //0:contacts, 1:messages, 2:n.contact, 3:about me
        //States = States + (tempOptions + 1);
     
        changingState(tempOptions+2);
       if(States ==4) CursorPos = 5;

       
       }
  }

if (States ==2) //Contacts
{
    //Setting up the Contact screen
  _lcd.setCursor(0,0);
  _lcd.print("Contact:");
  _lcd.setCursor(0,1);
  _lcd.print("<-");
  _lcd.setCursor(14,1);
 _lcd.print("->");

 
    _button = _lcd.getButtonPress();
    int CurPos2 = 0; //moving the cursor in the "composing a message" part

  
if (_button == RIGHT){
    _lcd.clear();
        _lcd.setCursor(5,1);
      //  _lcd.print(Contacts[OptionsCon]);
      _lcd.print(Eeprom.read_EEPROMName(OptionsCon));
        tempOptionsCon = OptionsCon;
        OptionsCon++;
       _button = _lcd.getButtonPress();
       // if (OptionsCon >3 || OptionsCon <0) OptionsCon =0;
          if (OptionsCon >9 || OptionsCon <0) OptionsCon =0;
       }
       
 if (_button == LEFT){
      _lcd.clear();
       _lcd.setCursor(5,1);
       // _lcd.print(Contacts[OptionsCon]);
       _lcd.print(Eeprom.read_EEPROMName(OptionsCon));
                tempOptionsCon = OptionsCon;
                OptionsCon--;
  //if (OptionsCon <0) OptionsCon =3;
  if (OptionsCon <0) OptionsCon =9;

 _button = _lcd.getButtonPress();
 }

 if (_button == UP)
 {
      changingState(1);
  }

 if (_button == SELECT) // Composing a message
 {
 
      changingState(6); // composing a message state
 }
}

 if (States ==6) // composing a message
 {
      _lcd.setCursor(0,0);
      _lcd.print("To: ");
      _lcd.print(Eeprom.read_EEPROMName(OptionsCon));
      _lcd.setCursor(0,1);

    _button = _lcd.getButtonPress();

      if (_button == RIGHT)
      {_lcd.setCursor(CursorPos,1);
        _lcd.write(MorseCode_0);
        morseMessage[morseCount] = MorseCode_0;
        morseCount++;
        CursorPos++;
         _button = _lcd.getButtonPress();
        }
      else if (_button == LEFT)
      {_lcd.setCursor(CursorPos,1);
        _lcd.write(MorseCode_1);
        morseMessage[morseCount] = MorseCode_1;
        morseCount++;
        CursorPos++;
       _button = _lcd.getButtonPress();
        }
       else if (_button == UP)
      {
         changingState(2);
        } 
        else if (analogRead(0) > 250 && analogRead(0) < 450) //DOWN
        {
          CursorPos--;
          morseCount--;
          _lcd.setCursor(CursorPos,1);
        _lcd.write(MorseCode_2);
        morseMessage[morseCount] = MorseCode_2;
            _button = _lcd.getButtonPress();
          }
        else if (_button == SELECT)
        {
            radio.stopListening();  
             
          
          radio.write(&morseMessage,sizeof(morseMessage));  
           radio.startListening();
           morseCount=0;
           //morseMessage = "";
                    changingState(7); //composing a message state

          } 
      }

      if (States ==7) // outcomes of sending a message
 {
      _lcd.setCursor(0,0);
      if (messageOutcome == true) 
      _lcd.print(MessageOutcome[0]);
      else if(messageOutcome == false)
      _lcd.print(MessageOutcome[1]);
      _lcd.setCursor(0,1);

      _button = _lcd.getButtonPress(); 

    timeOut(2000);

  }

      if (States ==3) //messages
 {
    _lcd.setCursor(0,0);
    _lcd.print("Messages: ");
    _lcd.setCursor(14,0);
    _lcd.print("(S");     //its logic need changes based on how data is stored and retireved

  
    _button = _lcd.getButtonPress();

     if (_button == RIGHT)
      {  
        _lcd.setCursor(0,1);
        Ctr++;
        _lcd.print(Ctr);
        if(Ctr == 20) Ctr =0; // limit of stroed messages is 20 
                              //(this implementation might not be needed)
        _lcd.print(".");
        _lcd.setCursor(3,1);
        _lcd.print(Contacts[OptionsCon]);
        OptionsCon++;
       _button = _lcd.getButtonPress();
        if (OptionsCon >3 || OptionsCon <0) OptionsCon =0;
        } 

  if (_button == LEFT)
      {  
        _lcd.setCursor(0,1);
        Ctr++;
        if(Ctr == 20) Ctr =0; // limit of stroed messages is 20 
                              //(this implementation might not be needed)
        _lcd.print(Ctr);
        _lcd.print(".");
        _lcd.setCursor(3,1);
        _lcd.print(Contacts[OptionsCon]);
        tempOptionsCon = OptionsCon;
        OptionsCon--;
        if (OptionsCon <0) OptionsCon =3;
        _button = _lcd.getButtonPress();
        }
      if (_button == UP)
      {
        _lcd.clear();
          States =1;
         CursorPos =0;
        }
        
        if (_button == SELECT)
      {
        _lcd.clear();
          States =8;
         CursorPos =0;
        }
  }

      if (States ==8) //Display Content of Stored Messages
      {
        _lcd.setCursor(0,0);
        _lcd.print(MessageSentFrom[0]);
        _lcd.print(Contacts[OptionsCon-1]);
        _lcd.setCursor(0,1);

       /* String _random [] {".","_"}; // for creating arbitray vlues - will be deleted
        
          for(int i=0;i<5; i++) //this loop is just for showin arbitary values 
                               // will be replaced with code to show the stored content of messages
        { int x =0;
        if (CursorPos == 5) break;
          x = random(0,2);
          if (x == 0) _lcd.print(_random[0]);
          else _lcd.print(_random[1]);
          CursorPos++;
          }*/

          //String(Eeprom.read_EEPROMMessage(eepromread));
          _lcd.print(Eeprom.read_EEPROMMessage(eepromread));
          

        _button = _lcd.getButtonPress();
        
      if (_button == UP)
      {
                eepromread++;
                if (eepromread >4 ) eepromread =0;

        changingState(3);
        }

        }

        if (States == 4) //N.contact
        {
          if(max_Contact <=10 && newUUID ==0)
          {
            _lcd.setCursor(0,0);
            _lcd.print("New Contact");
            _lcd.setCursor(14,0);
            _lcd.print("(1");    
            _lcd.setCursor(0,1);
            _lcd.print("Name:");
      

   if (CursorPos == 15) CursorPos =5;
  _lcd.setCursor(CursorPos,1);
  
  typingName();

 if (_button == SELECT){
  
        ContactName[NNcount] = Char;
        test9 = Char;
        test8 = Char-1;

      //  memset(&newCName[0], 0, sizeof(newCName));
         
                   test0 = '\0';
                   test1= '\0';
                  test2= '\0';
                test3= '\0';
                  test4= '\0';
                  test5= '\0';
                   test6= '\0';
                   test7= '\0';
                  test8= '\0';
                  test9= '\0';
      
        
         for (int i=0; i <= NNcount; i++)
              { if(i ==0) test0 = ContactName[i];
                if(i==1) test1 = ContactName[i];
                if(i==2) test2 = ContactName[i];
                if(i==3) test3 = ContactName[i];
                if(i ==4) test4 = ContactName[i];
                if(i==5) test5 = ContactName[i];
                if(i==6) test6 = ContactName[i];
                if(i==7) test7 = ContactName[i];
                //if(i==8) test8 = ContactName[i];
                //if(i==9) test9 = ContactName[i];
                newCName[i] = ContactName[i];
                  }
                  
               newCName[0] = test0;
                  newCName[1] = test1;
                  newCName[2] = test2;
                  newCName[3] = test3;
                  newCName[4] = test4;
                  newCName[5] = test5;
                  newCName[6] = test6;
                  newCName[7] = test7;
                  newCName[8] = test8;
                  newCName[9] = test9;           
                 
                  NNcount =0;

                  
                  
        newUUID =1;
        CursorPos =5;
      _lcd.clear();
          
       }  
            }
    else if(max_Contact <=10 && newUUID ==1)
    {
      
      _lcd.setCursor(0,0);
            _lcd.print("New Contact");
            _lcd.setCursor(14,0);
            _lcd.print("(2");    
            _lcd.setCursor(0,1);
            _lcd.print("UUID:");

            

            if (CursorPos > 15) CursorPos =5;
  _lcd.setCursor(CursorPos,1);
  
  if (HexLetters[Hex] == "0")
  { 
    Hex = 0;
    _lcd.print(HexLetters[Hex]);
  }

   _button = _lcd.getButtonPress();


 if (_button == UP)
 {    _lcd.setCursor(CursorPos,1);
      Hex++;
      _lcd.print(HexLetters[Hex]);
       _button = _lcd.getButtonPress();
       }
  
 
  if(analogRead(0) > 250 && analogRead(0) < 450){
      _lcd.setCursor(CursorPos,1);
      Hex--;
      if (Hex < 0) Hex = 14;
      _lcd.print(HexLetters[Hex]);
      _button = _lcd.getButtonPress();}

     if (_button == RIGHT){
 
      
      //conUUID+= HexLetters[Hex];
      conUUID.concat(HexLetters[Hex]);
      
      countUUID++;
      CursorPos++;
      _lcd.setCursor(CursorPos,1);
      Hex = 0;
      _lcd.print(HexLetters[Hex]);
       _button = _lcd.getButtonPress();
       }
 if (_button == LEFT){
       _lcd.print(' ');
        Hex =0;
     // _lcd.rightToLeft();
      conUUID.remove(Hex);
        CursorPos--;
        countUUID--;
        
       _lcd.setCursor(CursorPos,1);
 _button = _lcd.getButtonPress();
 }

 if (_button == SELECT){
  conUUID.concat(HexLetters[Hex]);
   // UUIDConvert(conUUID);

  

            // Serial.print(newCName[0]);
             //Serial.print(newCName[1]);
            //Serial.print(newCName[2]);
             //Serial.print(newCName[3]);
             //Serial.print(newCName[4]);
               // Serial.print(newCName[5]);


             /* Serial.print(UUID3[0]);
               Serial.print(UUID3[2]);
               Serial.print(UUID3[4]);
               Serial.print(UUID3[6]);
               Serial.print(UUID3[8]);*/
               // unsigned char* UUID4;
                
          
               
               
                 Eeprom.write_EEPROMContact(0,UUID1,newCName);
                 if (increment == 9) 
                 {
                  increment =0;
                  }
                 increment++;
                 
                  //String test = reinterpret_cast< char*> (UUID2);
                  //Eeprom.write_EEPROMContact(0,test,newCName);

            String x;
            String xx;
            xx = Eeprom.read_EEPROMUUID(2);
             Serial.print(xx);
             

        newUUID =0;    
        conUUID = "";
        _lcd.clear();
      States =9;
        CursorPos =6;
       }            
      }

      else if(max_Contact >10)
    {    
       _lcd.setCursor(0,0);
       _lcd.print("Contact List");    
       _lcd.setCursor(0,1);
       _lcd.print("is Full!");

       _button = _lcd.getButtonPress();   

        timeOut(2000);
    }
                }

          if (States == 9)
          {
             
            _lcd.setCursor(0,0);
            _lcd.print("Contact Added!");    

           _button = _lcd.getButtonPress();

            timeOut(2000);
           
        }
            if (States == 5) //About me
            {


              _lcd.setCursor(0,0);
              _lcd.print("Name: "); 
                for (int i=0; i <= Ncount; i++) _lcd.write(OwnerName[i]); 
                    
             
              
             _lcd.setCursor(0,1);
            _lcd.print("UUID: "); 
             HexConvert(UUID1);
           

              _button = _lcd.getButtonPress();

              timeOut(2000);
              
              }

          if(States == 10)
          {
            _lcd.setCursor(0,0);
              _lcd.print("New Message: ");
              _lcd.setCursor(0,1);

              while(radio.available ()) 
                    {radio.read(&messagerecivied, sizeof(messagerecivied)); 
                    //Serial.println(messagerecivied);
                      _lcd.print(messagerecivied);
                      rx_ready =false;
                    }
             Eeprom.write_EEPROMMessage(1,messagerecivied);

              
                    timeOut(4000);
                    
                  _button = _lcd.getButtonPress();
                  if (_button == UP)
                  {
                    changingState(1);
                    
                    }
            
            }


              
               
}

void changingState(int stateNum)
{
  States =stateNum;
        CursorPos =0;
      _lcd.clear();
  }

void typingName()
{
  if (Char > 'z')
  { 
    Char = 'a';
    _lcd.write(Char);
  }

   _button = _lcd.getButtonPress();


 if (_button == UP)
 {    _lcd.setCursor(CursorPos,1);
      Char++;
      _lcd.write(Char);
       _button = _lcd.getButtonPress();
       }
  
 
  if(analogRead(0) > 250 && analogRead(0) < 450){
      _lcd.setCursor(CursorPos,1);
      Char--;
      if (Char < 'a') Char = 'z';
      _lcd.write(Char);
      _button = _lcd.getButtonPress();}
       

 if (_button == RIGHT){

  if(Owner){
      OwnerName[Ncount] =  Char;
      Ncount++;
      if (Ncount > 9) Ncount =0;}
      
   else if(!Owner){  
        ContactName[NNcount] = Char;
        //test for newCName
       // if(NNcount == 0) test1 = Char;
   // if(NNcount == 1) test2 = Char;
    NNcount++; 
      
    
   if (NNcount > 9) NNcount =0;}
      
      CursorPos++;
      _lcd.setCursor(CursorPos,1);
      Char = 'a';
      _lcd.write(Char);
       _button = _lcd.getButtonPress();
       }
 if (_button == LEFT){
       Char = ' ';
       _lcd.write(Char);
        Char = 'a';
     // _lcd.rightToLeft();
        CursorPos--;
        Ncount--;
        NNcount--;
       _lcd.setCursor(CursorPos,1);
 _button = _lcd.getButtonPress();
  
  } }

  void timeOut(const long timeOutPeriod)
  {
       
      time = mymillisec();
    
      while ((mymillisec() - time < timeOutPeriod) && pressingButton ==false)
      {
            _button = _lcd.getButtonPress();
            if (_button == UP) pressingButton =true;
            
            }          
              changingState(1);  
    }

    

  unsigned long mymillisec()
{
  noInterrupts();          
TCCR1A = 0;     
TCCR1B = 0;     

OCR1A = 1999; 


TCCR1B |= (1 << WGM12);

TCCR1B |= (1 << CS11); 


TIMSK1 |= (1 << OCIE1A);

interrupts();
return count;

}

ISR(TIMER1_COMPA_vect)
{
  count++;
}

unsigned char* GeneratedUUID()
{              
  unsigned char * x = (unsigned char*)"12345";
x[5] = '\0';
for(int i=0; x[i] != '\0';i++)
x[i] = Entropy.random(WDT_RETURN_BYTE);


  return x;
  }


  void HexConvert(unsigned char *UUID)
   {

    for(int i=0; UUID[i] != '\0';i++)
    {

     unsigned char rightSideBits, leftSideBits;
      unsigned char valueForDigits = 0x30; // 0:0x30 => 9 :0x39   
       
       leftSideBits = UUID[i]  & 0xF0;     
       leftSideBits = leftSideBits >> 4; 

      if(leftSideBits >= 0 && leftSideBits <=9)
         leftSideBits = leftSideBits + valueForDigits;     
       else if(leftSideBits >9) 
       {            
          if (leftSideBits == 10)  leftSideBits = 0x41;  
          else if (leftSideBits == 11)  leftSideBits = 0x42;
          else if (leftSideBits == 12)  leftSideBits = 0x43;  
          else if (leftSideBits == 13)  leftSideBits = 0x44;
          else if (leftSideBits == 14)  leftSideBits = 0x45;
          else if (leftSideBits == 15)  leftSideBits = 0x46;
   }
                           
               
       rightSideBits = UUID[i]  & 0x0F; 
       if(rightSideBits >= 0 && rightSideBits <=9)
          rightSideBits = rightSideBits + valueForDigits;    

       if(rightSideBits >9) 
          {        
            if (rightSideBits == 10)  rightSideBits = 0x41;  
          else if (rightSideBits == 11)  rightSideBits = 0x42;
          else if (rightSideBits == 12)  rightSideBits = 0x43;  
          else if (rightSideBits == 13)  rightSideBits = 0x44;
          else if (rightSideBits == 14)  rightSideBits = 0x45;
          else if (rightSideBits == 15)  rightSideBits = 0x46;
          }
       
             
       _lcd.write(leftSideBits);           
       _lcd.write(rightSideBits); 

    }
     
   }

/*void UUIDConvert(String UUID)
   {
      char test [sizeof(UUID)+1];
      char test2[] = {};
     unsigned char* test1 ;
     
      int count =0;
      strcpy(test,UUID.c_str());
        unsigned char x=0;
           unsigned char rightSideBits, leftSideBits;

     
 
int ii =0;
    for(int i=0; i < 10;i+=2)
    { 

        x=0;
        leftSideBits = test[i];
        rightSideBits = test[i+1];

        
      
  if( leftSideBits >= '0' && leftSideBits <= '9' ) 
  x += leftSideBits-'0';
  
  else if(leftSideBits >= 'A' && leftSideBits <= 'F') 
  x += leftSideBits-'A'+0xA;
  
  x *= 0x10;
  
  if(rightSideBits >= '0' && rightSideBits <= '9')
  x += rightSideBits-'0';
  else if(rightSideBits >= 'A' &&rightSideBits <= 'F' )
  x += rightSideBits-'A'+0xA;

              // test1[i] = x;
        UUID3[i] = x;

   }
                 
   }*/

void Int_Servc_Rut()
{ 
                    radio.whatHappened(tx,rx,rx_ready);

                   if(rx_ready){

                    changingState(10);
                    
                   /* while(radio.available ()) 
                    {radio.read(&messagerecivied, sizeof(messagerecivied)); 
                    Serial.println(messagerecivied); }*/
                    
                    }

                    if(rx)
                    {
                       messageOutcome = false;
                       changingState(7);
                      }

                      if(tx)
                      {  messageOutcome = true;
                        changingState(7);
                      //Serial.print("message sent successfully");
                      }
  
  }
  
       
  


  
