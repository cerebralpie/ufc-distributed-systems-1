#include <Arduino.h>
#include "node1Sensor.hpp"

uint16_t readSensor() {
    return analogRead(SENSOR_PIN);

}

LuminosityState classifyLuminosity(uint16_t luminosity) {
    if (luminosity <= 1365) {
        return LuminosityState::DARK;
    } else if (luminosity <= 2730) {
        return LuminosityState::DIM;
    } else {
        return LuminosityState::BRIGHT;
    }
}
