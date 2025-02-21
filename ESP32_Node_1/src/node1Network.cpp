#include "node1Network.hpp"

void handleWiFiError(wl_status_t status)
{
    Serial.print("Erro no WiFi: ");
    switch (status)
    {
        case WL_NO_SHIELD:
            Serial.println("Nenhum módulo WiFi presente");
            break;
        case WL_IDLE_STATUS:
            Serial.println("WiFi está ocioso");
            break;
        case WL_NO_SSID_AVAIL:
            Serial.println("SSID não disponível");
            break;
        case WL_SCAN_COMPLETED:
            Serial.println("Varredura concluída");
            break;
        case WL_CONNECT_FAILED:
            Serial.println("Falha na conexão");
            break;
        case WL_CONNECTION_LOST:
            Serial.println("Conexão perdida");
            break;
        case WL_DISCONNECTED:
            Serial.println("Desconectado");
            break;
        default:
            Serial.println("Erro desconhecido");
            break;
    }
}

bool configureStaticIP()
{
    IPAddress local_IP(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2],
                       IP_ADDRESS[3]);
    IPAddress gateway(IP_GATEWAY[0], IP_GATEWAY[1], IP_GATEWAY[2],
                      IP_GATEWAY[3]);
    IPAddress subnet(IP_SUBNET[0], IP_SUBNET[1], IP_SUBNET[2],
                     IP_SUBNET[3]);
    
    if (!WiFi.config(local_IP, gateway, subnet))
    {
        Serial.println("Falha na configuração de IP estático");
        return false;
    }
    
    return true;
}

void printNetworkInfo() 
{
    Serial.println("\n=== Informações da Rede ===");
    Serial.print("IP Local: ");
    Serial.println(WiFi.localIP());
    Serial.print("Máscara de Sub-rede: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("IP do Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Força do sinal (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("=========================\n");
}

ConnectionState connectToWiFi()
{
    // Configura o WiFi no modo estação e desconecta de redes anteriores
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    delay(100);  // Pequeno atraso para estabilidade

    // Configura o IP estático
    if (!configureStaticIP())
    {
        return ConnectionState::ERROR;
    }

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Conectando ao Wi-Fi...");

    uint8_t attempts {0};
    
    while (attempts < MAX_CONNECTION_ATTEMPTS)
    {
        wl_status_t status {WiFi.status()};
        
        if (status == WL_CONNECTED)
        {
            // Verifica a força do sinal
            if (WiFi.RSSI() < MINIMUM_WIFI_RSSI)
            {
                Serial.println("\nSinal Wi-Fi fraco detectado!");
            }
            
            // Habilita economia de energia
            // WiFi.setSleep(true);
            return ConnectionState::CONNECTED;
        }
        else if (status != WL_DISCONNECTED)
        {
            handleWiFiError(status);
        }
        
        delay(CONNECTION_ATTEMPT_DELAY);
        Serial.print('.');
        ++attempts;
    }

    return ConnectionState::DISCONNECTED;
}