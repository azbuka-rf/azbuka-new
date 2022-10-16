#include <chernozem.h>

#include "azStep.h"
#include "azBoard.h"
#include "azWiFi.h"
#include "azMg.h"

#define hf 17

chernozem ser(&Serial);

void setup() {
  Serial.begin(115200);
  initTCP();
  ser << "TCP!\n";
  initStep();
  ser << "STEP!";
  initBoard();
  ser << "BOARD!";
  initMagnet();
  ser << "MAGNET!";
}

void loop() {
  if(WiFi.status() != WL_CONNECTED || !_tcp.connected()) {
    setup();
  }
  Serial.println("LOOp!");
  while(tcp.available()) {
    String cmd; tcp >> cmd;
    Serial.println("CMD!");

    if(cmd == "move") {
      int sx, sy, ex, ey; tcp >> sx >> sy >> ex >> ey;
      goTo(sx,sy);
      mg(1);

      if(ex < sx)
        movePerX(-hf);
      else if(sx < ex)
        movePerX(hf);

      if(ey > sy)
        goTo(X, ey-hf);
      else if(ey < sy)
        goTo(X, ey+hf);

      goTo(ex, Y);
      goTo(X, ey);
      
      mg(0);
    } else if(cmd == "up") {
      Serial.println("UP!");
      mg(1);
    }
    else if(cmd == "down")
      mg(0);
  } delay(2000);
  
  boardUpdate();
}

// void loop() {
//   if(WiFi.status() != WL_CONNECTED || !_tcp.connected()) {
//     setup();
//   }

//   while(tcp.available()) {
//     String cmd; tcp >> cmd;
//     ser << "TCP Command: " << cmd;
//     if(cmd == "move") {
//       cord s,e; tcp >> s.x >> s.y >> e.x >> e.y;
//       goTo(s.x,s.y);
//       mg(1);

//       if(e.x < s.x) {
//         movePerX(-hf);
//       } else if(s.x < e.x) {
//         movePerX(hf);
//       }

//       if(e.y > s.y) {
//         goTo(X,e.y-hf);
//       } else if(e.y < s.y) {
//         goTo(X, e.y+hf);
//       }

//       goTo(e.x,Y);
//       goTo(X, e.y);
      
//       mg(0);
//     } else if(cmd == "up") {
//       mg(1);
//     } else if(cmd== "down") {
//       mg(0);
//     }
//   }
  
//   if(ser.available()) {
//     String cmd; ser >> cmd;
//     ser << "TCP Command: " << cmd;
//     if(cmd == "send") {
//       int t, x, y; ser >> t >> x >> y;
//       tcp << String("M ") + t + " " + x + " " + y + "\n";
//     }
//   }
// }
