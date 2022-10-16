#ifndef AZBUKA_AZMAGNET_H
#define AZBUKA_AZMAGNET_H
#include <ESP32Servo.h>

#define mgPin 19

Servo servo;

void initMagnet() {
  servo.attach(mgPin);
}

void mg(char mode) {
  Serial.println("MG!");
  if(mode) {
    servo.write(85);
  }
  else {
    servo.write(0);
  }
  delay(700);
}

#endif