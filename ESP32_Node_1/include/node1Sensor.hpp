#ifndef NODE1_SENSOR_HPP
#define NODE1_SENSOR_HPP

#include <Arduino.h>

constexpr uint8_t SENSOR_PIN {34}; // Pino do conversor Analógigo-Digital
constexpr uint16_t READ_INTERVAL {15000}; // 15 segundos
constexpr uint16_t MAX_LUMINOSITY {4095}; // Máxima luminosidade que o sensor pode captar
constexpr uint16_t MIN_LUMINOSITY {0}; // Mínima luminosidade que o sensor pode captar

// Enum das classificacoes de luminosidade
enum class LuminosityState {
    DARK,
    DIM,
    BRIGHT
};

uint16_t readSensor();
LuminosityState classifyLuminosity(uint16_t luminosity);

#endif // NODE1_SENSOR_HPP