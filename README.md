# A MIDI Controller for a Kiwi-106 build using a Teensy 3.2

This repository contains the code and build instructions for a MIDI controller that controlls a Kiwi-106. The purpose of this controller is to have all critical Kiwi-106 controls available on a hardware interface. This can control most of the MIDI-only controls for a Kiwi-106 (all the ones I decided were necessary for performance), along with the general controls for LFO2 and ENV2. This way, the user rarely needs to enter different pages, reducing the need for menu diving.

This code is based on:  MIDI CONTROLLER  by Notes and Volts  www.notesandvolts.com. Big thanks to Notes and Volts!

It looks like the Teensy3.2 is pretty much out of production. You're better off using 4.x. The code should work the same, but the layout of the pins may be different.

## Getting Started

Follow these instructions to install the Teensy board info in the Arduino IDE: https://www.pjrc.com/teensy/td_download.html

## Build instructions

The basic instructions for building a MIDI controller with an Arduino can be found here: https://www.youtube.com/watch?v=DXhxdsGREsU

Connect the MIDI/DIN jack like so:
  - If the female end of the jack is facing you, the pins from left to right are 3, 5, 2, 4, 1
  - Leave pin 3 disconnected
  - Connect pin 5 to the TX pin, with a 47Ω resistor in between
  - Connect pin 2 (center) to the Ground pin
  - Connect pin 4 to the 5V pin, with a 47Ω resistor in between
  - Leave pin 3 disconnected

Connect each Pot like so:
  - With the pins facing you, they are organized like so: 1, 2, 3
  - Connect Pin 1 to the Ground pin
  - Connect Pin 2 to whichever Teensy Analog pin corresponds to the knob (see below)
  - Connect Pin 3 to 5V

Connect each Toggle like so:
  - Connect one (either) of the outer pins to whichever Teensy Analog pin corresponds to the Toggle (see below)
  - Connect the center pin to the Ground pin

Connect each LED like so:
  - Connect the Anode (Long Pin) to whichever Teensy Analog pin corresponds to the LED (see below)
  - Connect the Cathode (Short Pin) to the Ground pin

## Parts List

- 1x Project Enclosure
  * https://www.mouser.com/ProductDetail/546-515-0930
- 1x Teensy 3.2
  * https://www.sparkfun.com/products/13736
  * https://www.mouser.com/ProductDetail/474-PRT-13925
- 1x MIDI/DIN Jack
  * https://www.mouser.com/ProductDetail/16HR655
- 15x Linear 10kohm pots
  * https://www.taydaelectronics.com/10k-ohm-linear-taper-potentiometer-round-shaft-pcb-9mm.html
- 1x Linear 10kohm deteneted pot (11 detents is ideal)
  * not sure where I got this
- 4x Toggle switches
  * https://www.taydaelectronics.com/mini-toggle-switch-spdt-on-on.html
- 13x LEDs
  * https://www.taydaelectronics.com/led-3mm-red.html
  * https://www.taydaelectronics.com/3mm-bezel-led-panel-mounting-clip.html
- 1x Teensy power adapter
  * https://www.mouser.com/ProductDetail/485-4217

## Knob, Switch, and LED Description

For each Pot, the pot number corresponds to the Analog Pin Number (Pot 0 connects to Pin A0)

For each Toggle or LED the number corresponds to the Digital Pin number (LED 0 connects to Digital Pin 0, Toggle 1 connects to Digital Pin 1). Digital pins can be outputs or inputs, so they're mixed up a bit according to the best way to solder them.

### Pots

- Pot 0: Channel 105: Detune Amount  
- Pot 1: Channel 11:  PWM Source Select
    * LEDs 0, 5, 6, 7, 8, 9
- Pot 2: Channel 15: DCO ENV Source Select
    * LEDs 10, 11
- Pot 3: Channel 14: DCO ENV Amount
- Pot 4: Channel 48: VCF ENV Source Select
    * LED 24, 25
- Pot 5: Channel 59: VCA LFO Amount
- Pot 6: Channel 61:  VCA ENV Mode
    * LEDs 27, 28
- Pot 7: Channel 72: Int Clock
- Pot 8: SysEx: Arp Subdivide and Seq Subdivide // Set CC to 0, which flips it to SysEx mode
- Pot 9: Channel 22: LFO 2 Rate
- Pot 10: Channel 23: LFO 2 Delay
    * Note: for some reason these CC values are backwards, so wrired up knob. in reverse
- Pot 11: Channel 65: ENV 2 Attack
- Pot 12: Channel 66: ENV 2 Decay
- Pot 13: Channel 67: ENV 2 Sustain
- Pot 14: Channel 68: ENV 2 Release
- Pot 15: MIDI Channel Select
    * Note: Muist use 11 point detented pot

### Toggles

- Toggle 1: Channel 106: Detune Mode
    * Up = Mono/Unison/Poly
    * Down = Mono/Unison
- Toggle 2: Channel 13: DCO LFO Source
    * Up = LFO 2
    * Down = LFO 1
- Toggle 2: Channel 46: VCF LFO Source
    * Up = LFO 2
    * Down = LFO 1
- Toggle 2: Channel 60: VCA LFO Source
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


### Known Bugs

- LFO 2 Delay rate is backwards. Rather than adjusting the code I just flipped the polarity of the pot physically by switching the Ground and +5v pins.  
- DCO Envelope Select knob is broken. It only lets you choose between ENV 1 Normal, and ENV 2 Inverted. Not sure why, I think it's a KIWI issue.
