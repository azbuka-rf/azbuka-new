#ifndef AZBUKA_AZWIFI_H
#define AZBUKA_AZWIFI_H
#include "chernozemTCP.h"
#include <WiFi.h>

WiFiClient _tcp;
chernozemTCP tcp(&_tcp);

const char* ssid = "vika";
const char* password = "korovin228";

const char* host = "192.168.43.185";
const uint16_t port = 1234;

void initTCP() {
  WiFi.hostname("Azbuka");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  while(!_tcp.connect(host, port)) {
    delay(100);
  }
}

#endif