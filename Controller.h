#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

//************************************************************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte pin, byte command, byte value, byte channel, byte debounce);
    byte getValue();
    void newValue(byte command, byte value, byte channel);
    byte Bcommand;
    byte Bvalue;
    byte Bchannel;
    byte Btoggle;

  private:
    byte _previous;
    byte _current;
    unsigned long _time;
    int _debounce;
    byte _pin;
    byte _value;
    byte _command;
    bool _busy;
    byte _status;
    byte _last;
    byte _enablepin;
};
//************************************************************************
//Toggle (Pin Number, Control, Channel, Debounce Time)
class Toggle
{
  public:
    Toggle(byte pin, byte control, byte channel, byte debounce);
    byte getValue();
    void newValue(byte control, byte value, byte channel);
    byte Tcontrol;
    byte Tvalue;
    byte Tchannel;
    byte Ttoggle;

  private:
    byte _previous;
    byte _current;
    unsigned long _time;
    int _debounce;
    byte _pin;
    byte _control;
    bool _busy;
    byte _status;
    byte _last;
    byte _enablepin;
};
//*************************************************************************
class Pot
{
  public:
    Pot(byte pin, byte command, byte control, byte channel);
    void newValue(byte command, byte value, byte channel);
    byte getValue();
    byte Pcommand;
    byte Pcontrol;
    byte Pchannel;

  private:
    byte _pin;
    byte _control;
    int _value;
    int _oldValue;
    bool _changed;
    byte _enablepin;
};
//*************************************************************************
#endif
