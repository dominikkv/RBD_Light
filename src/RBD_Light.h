// Arduino RBD Light Library v2.1.7 - Control many lights.
// https://github.com/alextaujenis/RBD_Light
// Copyright 2016 Alex Taujenis
// MIT License

#ifndef RBD_LIGHT_H
#define RBD_LIGHT_H

#include <Arduino.h>
#include <RBD_Timer.h>

namespace RBD {
  class SimpleLight {
    public:
      SimpleLight(int pin, bool isSink = false);
      void on(bool _stop_everything = true);  // turn on the light, stop everything is for internal use only
      void off(bool _stop_everything = true); // turn off the light, stop everything is for internal use only
      void setState(bool state, bool _stop_everything = true); // turn off the light, stop everything is for internal use only
      void toggle();
      bool isOn();                            // returns true when the light is at 100% brightness
      bool isOff();                           // returns true when the ligh is at 0% brightness
      void setBrightness(int value, bool _stop_everything = true);        // 0 - 255
      void setBrightnessPercent(int value, bool _stop_everything = true); // 0 - 100
      int getBrightness();        // 0 - 255
      int getBrightnessPercent(); // 0 - 100
    protected:
      virtual void _stopEverything();
    private:
      // global
      bool _isSink;
      int _pin;
      int _pwm_value = 0;
  };
  
  class Light: public SimpleLight {
    public:
      Light(int pin, bool isSink = false);
      void update();                          // process real-time methods
      void blink(unsigned long on_time, unsigned long off_time, int times);
      void fade(unsigned long up_time, unsigned long on_time, unsigned long down_time, unsigned long off_time, int times);
      // overloaded blink & fade for unlimited times
      void blink(unsigned long on_time, unsigned long off_time);
      void fade(unsigned long up_time, unsigned long on_time, unsigned long down_time, unsigned long off_time);
    protected:
      void _stopEverything();
    private:
      // global
      int _times;
      bool _forever  = false;
      // blinking
      bool _blinking;
      void _blink();
      bool _shouldBlinkOff();
      bool _shouldBlinkOn();
      void _startBlinking();
      void _stopBlinking();
      void _blinkOff();
      void _blinkOn();
      // fading
      bool _fading;
      enum {_RISING, _MAX, _FALLING, _MIN} _state;  // internal state
      void _fade();
      void _rising();
      void _max();
      void _falling();
      void _min();
      void _startFading();
      void _stopFading();
      bool _shouldBeRising();
      bool _shouldBeMax();
      bool _shouldBeFalling();
      bool _shouldBeMin();
      int _risingValue();
      int _fallingValue();
      Timer _up_timer;
      Timer _on_timer;
      Timer _down_timer;
      Timer _off_timer;
  };
}
#endif