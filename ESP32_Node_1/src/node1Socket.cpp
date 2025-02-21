#include "node1Sensor.hpp"
#include "node1Socket.hpp"
#include <Arduino.h>

void socketInitialize() {
    // Inicializa o servidor socket
    wifiServer.begin();
}