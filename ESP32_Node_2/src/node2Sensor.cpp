#include <Arduino.h>
#include "node2Sensor.hpp"

uint32_t getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;

}

DistanceState classifyDistance(uint32_t distance) {
    if (distance <= 50) {
        return DistanceState::CLOSE;
    } else if (distance <= 100) {
        return DistanceState::MEDIUM;
    } else {
        return DistanceState::FAR;
    }
}

DistanceState getDistanceClassification()
{
    return classifyDistance(getDistance());
}
