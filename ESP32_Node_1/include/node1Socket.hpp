#ifndef NODE1_SOCKET_HPP
#define NODE1_SOCKET_HPP

#include <Arduino.h>
#include <WiFi.h>
#include "node1Network.hpp"


WiFiServer wifiServer(80);

void socketInitialize();

#endif // NODE1_SOCKET_HPP