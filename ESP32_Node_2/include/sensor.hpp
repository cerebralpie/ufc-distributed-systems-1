#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Arduino.h>

constexpr uint8_t TRIG_PIN {19};
constexpr uint8_t ECHO_PIN {18};

enum class DistanceState {
    CLOSE,
    MEDIUM,
    FAR
};

uint32_t getDistance();
DistanceState classifyDistance(uint32_t distance);

#endif // SENSOR_HPP
