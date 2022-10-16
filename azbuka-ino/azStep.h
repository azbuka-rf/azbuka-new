#ifndef AZBUKA_AZSTEP_H
#define AZBUKA_AZSTEP_H

// ====================

#define xStp 2
#define xDir 3

#define yStp 5
#define yDir 6

#define xEnd 4
#define yEnd 7

#define Delay 150

// ====================

int X, Y;

// ====================

void movePerX(int mm) {
  int steps = mm * 200 * 16 / 2 / 20;
  if(steps < 0) {
    steps = -steps;
    digitalWrite(yDir, HIGH);
    digitalWrite(xDir, LOW);
  } else {
    digitalWrite(yDir, LOW);
    digitalWrite(xDir, HIGH);
  }
  while(steps--) {
    digitalWrite(yStp, HIGH);
    digitalWrite(xStp, HIGH);
    digitalWrite(yStp, LOW);
    digitalWrite(xStp, LOW);
    delayMicroseconds(Delay);
  }
  X += mm;
}

void movePerY(int mm) {
  int steps = mm * 200 * 16 / 2 / 20;
  if(steps < 0) {
    steps = -steps;
    digitalWrite(yDir, LOW);
    digitalWrite(xDir, LOW);
  } else {
    digitalWrite(yDir, HIGH);
    digitalWrite(xDir, HIGH);
    
  }
  while(steps--) {
    digitalWrite(yStp, HIGH);
    digitalWrite(xStp, HIGH);
    digitalWrite(yStp, LOW);
    digitalWrite(xStp, LOW);
    delayMicroseconds(Delay);
  }
  Y += mm; 
}

void goTo(int x, int y) {
  movePerX(x-X);
  movePerY(y-Y);
}

void goHome() {
  ;;;
}

void initStep() {
  X = 0; Y = 0;
  
  pinMode(xStp, OUTPUT);
  pinMode(xDir, OUTPUT);
  pinMode(xEnd, INPUT_PULLUP);

  pinMode(yStp, OUTPUT);
  pinMode(yDir, OUTPUT);
  pinMode(yEnd, INPUT_PULLUP);

  goHome();
  
}

#endif