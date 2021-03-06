// Copyright © 2018 Stanislav Hnatiuk. All rights reserved.

#ifndef REQUEST_H
#define REQUEST_H

#include <Ethernet.h>


 
//! Глобальный сервер.
EthernetServer server(80);



//! Ответить на запрос. Определение в файле IION-Monitor-Arduino.
extern void requestResponse(EthernetClient& client);



//! Проверить запрос.
void checkRequest() {
  for (uint8_t sock = 0; sock < MAX_SOCK_NUM; ++sock) {
    EthernetClient client = server.available_(sock);
    bool start = true;
    bool currentLineIsBlank = true;
    while (client.connected()) {
      char c = client.read();
      if (c == '\n' && currentLineIsBlank) {
        requestResponse(client);
        break;
      }

      if (c == '\n') {
        currentLineIsBlank = true;
      } else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
    client.stop();
  }
}



//! Настроить и запустить сервер.
void startServer() {
  Ethernet.begin((0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED),
                 IPAddress(172, 17, 24, 131), 
                 IPAddress(172, 17, 24, 1), 
                 IPAddress(255, 255, 255, 0));
  server.begin();
}

#endif // REQUEST_H
