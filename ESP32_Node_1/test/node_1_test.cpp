#include "proto/messages.pb.h"
#include <pb_encode.h>
#include "sensor.hpp"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    // Initialize sensor pin
    pinMode(SENSOR_PIN, INPUT);
}

void loop() {
    // Create buffer for serialized data
    uint8_t buffer[128];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    // Create and populate message
    DeviceState state = DeviceState_init_zero;
    strcpy(state.device_id, "ESP32_LUM_1");
    state.type = DeviceType_LUMINOSITY_SENSOR;
    
    // Read and classify sensor data
    uint16_t raw_value = readSensor();
    LuminosityState lum_state = classifyLuminosity(raw_value);
    
    state.has_luminosity = true;
    state.luminosity.raw_value = raw_value;
    state.luminosity.state = (LuminosityData_State) lum_state;
    
    // Serialize and print debug info
    bool status = pb_encode(&stream, DeviceState_fields, &state);
    
    Serial.println("\n=== Sensor Test ===");
    Serial.print("Raw Value: ");
    Serial.println(raw_value);
    Serial.print("State: ");
    Serial.println((int)lum_state);
    Serial.print("Serialization: ");
    Serial.println(status ? "SUCCESS" : "FAILED");
    Serial.print("Message size: ");
    Serial.println(stream.bytes_written);
    
    delay(2000);
}
