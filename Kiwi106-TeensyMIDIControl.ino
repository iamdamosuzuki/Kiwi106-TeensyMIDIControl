#include <MIDI.h>
#include "Controller.h"

/*************************************************************
  Kiwi-106 MIDI Controller Using Teensy 3.2
  
  bassed on:  MIDI CONTROLLER  by Notes and Volts  www.notesandvolts.com

  Morgan Notes
  7/17/23
  I believe this is all working. LEDs will need to be tested
  SysEx for Arp Speed is working. Individual pots and switches have been tested. 
  Comments have been put in for clarity
  Time to build and test!

 *************************************************************/

MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 0;
//---How many toggles are connected directly to pins?--
byte NUMBER_TOGGLES = 4;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 15;

//************************************************************

//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

Pot PO1(A0, 0, 105, 1);   //  Detune  
Pot PO2(A1, 0, 11, 1);    //  PWM Source Select     // LED 0, 5, 6, 7, 8, 9
Pot PO3(A2, 0, 15, 1);    //  DCO ENV Source Select // LED 10, 11
Pot PO4(A3, 0, 14, 1);    //  DCO ENV Amount
Pot PO5(A4, 0, 48, 1);    //  VCF ENV Source Select // LED 12, 13
Pot PO6(A5, 0, 59, 1);    //  VCA LFO Amount
Pot PO7(A6, 0, 61, 1);    //  VCA LFO Mode          // LED 24, 25
Pot PO8(A7, 0, 72, 1);    //  Int Clock
Pot PO9(A8, 0, 0, 1);     //  Arp Subdivide // Set CC to 0, which flips it to SysEx mode
Pot PO10(A9, 0, 0, 1);     //  LFO 2 Rate
Pot PO11(A10, 0, 0, 1);     //  LFO 2 Delay
Pot PO12(A11, 0, 0, 1);     //  ENV 2 Attack
Pot PO13(A12, 0, 0, 1);     //  ENV 2 Decay
Pot PO14(A13, 0, 0, 1);     //  ENV 2 Sustain
Pot PO15(A14, 0, 0, 1);     //  ENV 2 Release
//*******************************************************************
//Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
//Pot *POTS[] {&PO1};
Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6, &PO7, &PO8, &PO9, &PO10, &PO11, &PO12, &PO13, &PO14, &PO15};
//*******************************************************************

//***DEFINE DIRECTLY CONNECTED TOGGLES*******************************
//Toggle (Pin Number, Command, Channel, Debounce Time)

Toggle TG1(2, 106, 1, 5 );    //    Detune Mode
Toggle TG2(3, 13, 1, 5 );    //    DCO LFO Source
Toggle TG3(4, 46, 1, 5 );    //    VCF LFO Source
Toggle TG4(5, 60, 1, 5 );    //    VCA LFO Source

//*******************************************************************
//Add toggles used to array below like this->  Toggle *TGS[] {&TG1, &TG2, &TG3, &TG4, &TG5, &TG6, &TG7, &TG8};
Toggle *TOGGLES[] {&TG1, &TG2, &TG3, &TG4};
//Toggle *TOGGLES[] {&TG1};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

//Button BU1(9, 1, 60, 1, 5 );    
//Button BU2(3, 0, 61, 1, 5 );
//Button BU3(4, 0, 62, 1, 5 );
//Button BU4(5, 0, 63, 1, 5 );
//Button BU5(6, 0, 64, 1, 5 );
//Button BU6(7, 0, 65, 1, 5 );
//Button BU7(8, 1, 64, 1, 5 );
//Button BU8(9, 2, 64, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {NULL}; //No buttons, gotta declare this as NULL to keep the code happy
//Button *BUTTONS[] {&BU1};
//*******************************************************************

void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(0, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
}

void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_TOGGLES != 0) updateToggles();
}


//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}

//*****************************************************************
void updateToggles() {

  // Cycle through Toggle array
  for (int i = 0; i < NUMBER_TOGGLES; i = i + 1) {
    byte message = TOGGLES[i]->getValue();

    //  Toggle is Flipped Up
    if (message == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    MIDI.sendControlChange(TOGGLES[i]->Tcontrol, 127, TOGGLES[i]->Tchannel);
    }

    //  Toggles is flipped down
    if (message == 1) {
    digitalWrite(LED_BUILTIN, LOW);
    MIDI.sendControlChange(TOGGLES[i]->Tcontrol, 0, TOGGLES[i]->Tchannel); 
    }
  }
}
//***********************************************************************

void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255){             //if pot message changes 
      if (POTS[i]->Pcontrol == 0){      // CC value 0 trips it to perform SysEx Arp Speed Command
        processSysEx(potmessage);       // This funtion figures out the SysEx message to send to the arp speed command
      }
      else{
        MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, POTS[i]->Pchannel);
        updateLEDs(i, potmessage);      //This function handles LED feedback      
      }
    }
  }
}

void processSysEx(byte potmessage) {
  byte arp_byte = 0;
  if (potmessage <= 14){
    arp_byte = 0x00;
  }
  if (potmessage >= 15 && potmessage <= 28){
    arp_byte = 0x01;
  }
  if (potmessage >= 29 && potmessage <= 42){
    arp_byte = 0x02;
  }
  if (potmessage >= 43 && potmessage <= 56){
    arp_byte = 0x05;
  }
  if (potmessage >= 57 && potmessage <= 70){
    arp_byte = 0x06;
  }
  if (potmessage >= 71 && potmessage <= 84){
    arp_byte = 0x09;
  }
  if (potmessage >= 85 && potmessage <= 98){
    arp_byte = 0x10;
  }
  if (potmessage >= 99 && potmessage <= 112){
    arp_byte = 0x11;
  }
  if (potmessage >= 113 && potmessage <= 127){
    arp_byte = 0x12;
  }
  uint8_t sysex[] {0xF0, 0x00, 0x21, 0x16, 0x60, 0x03, 0x00, 0x0E, 0x63, 0x00, arp_byte, 0xF7};
  MIDI.sendSysEx(12, sysex, true);
}

void updateLEDs(int potNum, byte potmessage) {
  if (potNum == 2){         //Pot 2 PWM Source
    if (potmessage <= 15){  //Manual
      digitalWrite(0, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
    if (potmessage >= 16 && potmessage <= 31){  //LFO 1
      digitalWrite(0, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
    if (potmessage >= 32 && potmessage <= 47){  //LFO 2
      digitalWrite(0, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
    }
    if (potmessage >= 48 && potmessage <= 63){  //ENV 1 Normal
      digitalWrite(0, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
    }
    if (potmessage >= 64 && potmessage <= 79){  //ENV 1 Inverted
      digitalWrite(0, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
    }
    if (potmessage >= 80 && potmessage <= 95){  //ENV 2 Normal
      digitalWrite(0, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
    }
    if (potmessage >= 96 && potmessage <= 127){ //ENV 1 Invterted
      digitalWrite(0, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
    }
  }
  if (potNum == 3){         //Pot 3 DCO ENV Source
    if (potmessage <= 31){  //ENV 1 Normal
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    }
    if (potmessage >= 32 && potmessage <= 63){  //ENV 1 Inverted
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
    if (potmessage >= 64 && potmessage <= 95){  //ENV 2 Normal
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
    if (potmessage >= 96 && potmessage <= 127){  //ENV 2 Inverted
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    }
  }
  if (potNum == 5){ //Pot 5 VCF ENV Source
    if (potmessage <= 31){  //ENV 1 Normal
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
    if (potmessage >= 32 && potmessage <= 63){  //ENV 1 Inverted
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
    if (potmessage >= 64 && potmessage <= 95){  //ENV 2 Normal
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
    if (potmessage >= 96 && potmessage <= 127){  //ENV 2 Inverted
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
    }
  }
  if (potNum == 7){ //Pot 7 VCA ENV Source / Mode
    if (potmessage <= 31){  //Gate
      digitalWrite(25, LOW);
      digitalWrite(24, LOW);
    }
    if (potmessage >= 32 && potmessage <= 63){  //ENV 1
      digitalWrite(25, HIGH);
      digitalWrite(24, LOW);
    }
    if (potmessage >= 64 && potmessage <= 127){  //ENV 2 
      digitalWrite(25, LOW);
      digitalWrite(24, HIGH);
    }
  }
}



