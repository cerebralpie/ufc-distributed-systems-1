#include "proto/messages.pb.h"
#include <pb_encode.h>
#include "sensor.hpp"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    uint8_t buffer[128];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    
    DeviceState state = DeviceState_init_zero;
    strcpy(state.device_id, "ESP32_DIST_1");
    state.type = DeviceType_DISTANCE_SENSOR;
    
    uint32_t distance = getDistance();
    DistanceState dist_state = classifyDistance(distance);
    
    state.has_distance = true;
    state.distance.distance_cm = distance;
    state.distance.state = (DistanceData_State) dist_state;
    
    bool status = pb_encode(&stream, DeviceState_fields, &state);
    
    Serial.println("\n=== Sensor Test ===");
    Serial.print("Distance (cm): ");
    Serial.println(distance);
    Serial.print("State: ");
    Serial.println((int)dist_state);
    Serial.print("Serialization: ");
    Serial.println(status ? "SUCCESS" : "FAILED");
    Serial.print("Message size: ");
    Serial.println(stream.bytes_written);
    
    delay(2000);
}
