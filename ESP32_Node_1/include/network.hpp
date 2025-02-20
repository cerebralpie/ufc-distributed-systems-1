#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Arduino.h>
#include <WiFi.h>

// Parametros de configuracao de rede
constexpr char WIFI_SSID[] {"Distributed_Systems"};
constexpr char WIFI_PASS[] {"12345678"}; 

// Configuracao IP
constexpr uint8_t IP_ADDRESS[] {192, 168, 1, 10};
constexpr uint8_t IP_GATEWAY[] {192, 168, 1, 1};
constexpr uint8_t IP_SUBNET[] {255, 255, 255, 0};

// Parametros da conexao
constexpr uint8_t MAX_CONNECTION_ATTEMPTS {10};
constexpr uint16_t CONNECTION_ATTEMPT_DELAY {500};
constexpr uint32_t SERIAL_BAUD_RATE {115200};
constexpr int16_t MINIMUM_WIFI_RSSI {-80};

// Enum dos estados da conexao
enum class ConnectionState {
  CONNECTED,
  DISCONNECTED,
  ERROR
};

void handleWiFiError(wl_status_t status);
bool configureStaticIP();
void printNetworkInfo();
ConnectionState connectToWiFi();

#endif // NETWORK_HPP