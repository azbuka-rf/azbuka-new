#ifndef AZBUKA_AZBOARD_H
#define AZBUKA_AZBOARD_H
#include <Adafruit_PCF8574.h>

#include "azWiFi.h"

Adafruit_PCF8574 pcfX, pcfY;
char board[8][8];

void initBoard() {
  if(!pcfX.begin(0x23, &Wire)) {
    Serial.println("Couldn't find pcfX");
    while(1);
  }
  if(!pcfY.begin(0x27, &Wire)) {
    Serial.println("Couldn't find pcfY");
    while(1);
  }
  for(int i = 0; i < 8; ++i) {
    pcfX.pinMode(i, OUTPUT);
    pcfX.digitalWrite(i,HIGH);
  }
  for(int i = 0; i < 8; ++i) {
    pcfY.pinMode(i, INPUT_PULLUP);
  }
  for(int i = 0; i < 8; ++i) {
    pcfX.digitalWrite(i,LOW);
    for(int j = 0; j < 8; ++j) {
      board[i][j]=pcfY.digitalRead(j);
    }
    pcfX.digitalWrite(i,HIGH);
  }
}

void boardUpdate() {
  char x;
  for(int i = 0; i < 8; ++i) {
    pcfX.digitalWrite(i,LOW);
    for(int j = 0; j < 8; ++j) {
      x = pcfY.digitalRead(j);
      if(x != board[i][j]) {
        tcp << String("M ") + i + " " + j + " " + " " + x;
      }
      board[i][j] = x;
    }
    pcfX.digitalWrite(i,HIGH);
  }
}

#endif