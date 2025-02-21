#include "proto/messages.pb.h"
#include "node1Sensor.hpp"
#include "node1Socket.hpp"
#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <WiFi.h>



auto state {ConnectionState::DISCONNECTED};

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);  // Para permitir que o serial estabilize

  Serial.println("Inicializando processo de conexão ao WiFi...");

  state = {connectToWiFi()};

  if (state == ConnectionState::CONNECTED)
  {
    Serial.println("\nConexão ao WiFi realizado com sucesso!");
    printNetworkInfo();
  }
  else
  {
    Serial.println("\nFalha ao tentar conectar ao WiFi.");
    Serial.println("Por favor, cheque as credenciais e o status do roteador.");
  }

  socketInitialize();
}

void loop() {
  static uint32_t lastCheck {0};
  constexpr uint32_t CHECK_INTERVAL {10000};  // Checa a cada 10 segundos
    
  uint32_t currentMillis {millis()};
    
  // Checagem periódica da conexão
  if (currentMillis - lastCheck >= CHECK_INTERVAL) {
      lastCheck = currentMillis;
      
      if (WiFi.status() != WL_CONNECTED) {
          Serial.println("WiFi connection lost. Attempting to reconnect...");
          state = connectToWiFi();
      } else if (WiFi.RSSI() < MINIMUM_WIFI_RSSI) {
          Serial.println("Warning: Weak WiFi signal detected!");
          Serial.print("Current RSSI: ");
          Serial.print(WiFi.RSSI());
          Serial.println(" dBm");
      }
  }
    
    // Código de leitura da luminosidade, seguido de envio dos dados para 
    // o gateway


    delay(100);  // Previnir reinicialização do watchdog
}