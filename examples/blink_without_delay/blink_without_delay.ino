// Arduino RBD Light Library v1.0.0 Example - Blink the Arduino LED in real-time with no delay.
// https://github.com/alextaujenis/RBD_Light
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Light.h> // https://github.com/alextaujenis/RBD_Light

RBD::Light light(13);

void setup() {
  light.blink(250,250);
}

void loop() {
  light.update();
}