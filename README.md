# A MIDI Controller for a Kiwi-106 build using a Teensy 3.2

This repository contains the code and build instructions for a MIDI controller that controlls a Kiwi-106. The purpose of this controller is to have all critical Kiwi-106 controls available on a hardware interface. This can control most of the MIDI-only controls for a Kiwi-106 (all the ones I decided were necessary for performance), along with the general controls for LFO2 and ENV2. This way, the user rarely needs to enter different pages, reducing the need for menu diving. 

## Parts List

- 1 Project Enclosure
- Teensy 3.2
- 15x Linear 10kohm pots 
- 1x Linear 10kohm deteneted pot
- 4 Toggle switches
- 13 LEDs

## Knob, Switch, and LED Description

### Pots

    - Pot 01: Channel 105: Detune Amount  
    - Pot 02: Channel 11:  PWM Source Select
        * LEDs 0, 5, 6, 7, 8, 9
    - Pot 03: Channel 15: DCO ENV Source Select
        * LEDs 10, 11
    - Pot 04: Channel 14: DCO ENV Amount
    - Pot 05: Channel 48: VCF ENV Source Select
        * LED 24, 25
    - Pot 06: Channel 59: VCA LFO Amount
    - Pot 07: Channel 61:  VCA ENV Mode
        * LEDs 27, 28
    - Pot 08: Channel 72: Int Clock
    - Pot 09: SysEx: Arp Subdivide and Seq Subdivide // Set CC to 0, which flips it to SysEx mode
    - Pot 10: Channel 22: LFO 2 Rate
    - Pot 11: Channel 23: LFO 2 Delay
        * Note: for some reason these CC values are backwards, so wrired up knob. in reverse
    - Pot 12: Channel 65: ENV 2 Attack
    - Pot 13: Channel 66: ENV 2 Decay
    - Pot 14: Channel 67: ENV 2 Sustain
    - Pot 15: Channel 68: ENV 2 Release 
    - Pot 16: MIDI Channel Select
        * Note: Muist use 11 point detented pot
        
### Toggles

    - Toggle 01: Channel 106: Detune Mode
        * Up = Mono/Unison/Poly
        * Down = Mono/Unison
    - Toggle 02: Channel 13: DCO LFO Source
        * Up = LFO 2
        * Down = LFO 1
    - Toggle 02: Channel 46: VCF LFO Source
        * Up = LFO 2
        * Down = LFO 1
    - Toggle 02: Channel 60: VCA LFO Source
        * Up = LFO 2
        * Down = LFO 1


### LEDs
Note: LED Numbers refer to the Teensy's Digital Pins

     - PWM Source Select
        * LED 0: Manual
        * LED 5: Inverted
        * LED 6: LFO 1
        * LED 7: LFO 2
        * LED 8: ENV 1
        * LED 9: ENV 2
        * LED 6: LFO 1
        * LED 7: LFO 2
        
    - DCO ENV Source Select
        * LED 10: Off = ENV 1, On = ENV 2 
        * LED 11: Off = Normal, On = Inverted
       
    - DCO ENV Source Select
        * LED 24: Off = ENV 1, On = ENV 2 
        * LED 25: Off = Normal, On = Inverted
      
    - VCA ENV Mode
        * LED 27: Off + LED 28: Off = Gate
        * LED 27: On + LED 28: Off = ENV 1
        * LED 27: Off + LED 28: On = ENV 2

