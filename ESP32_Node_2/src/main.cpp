#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/messages.pb.h"

DeviceState device_state = DeviceState_init_zero;

void setupDevice() {
    device_state.device_id = "ESP32_DISTANCE_1";
    device_state.type = DeviceType_DISTANCE_SENSOR;
}

void updateState() {
    uint32_t distance = getDistance();
    DistanceState state = classifyDistance(distance);
    
    device_state.has_distance = true;
    device_state.distance.distance_cm = distance;
    device_state.distance.state = (state == DistanceState::CLOSE) ? 
        DistanceData_State_CLOSE : 
        (state == DistanceState::MEDIUM) ? 
        DistanceData_State_MEDIUM : 
        DistanceData_State_FAR;
}

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}