#ifndef NODE2_SENSOR_HPP
#define NODE2_SENSOR_HPP

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
DistanceState getDistanceClassification();

#endif // NODE2_SENSOR_HPP
