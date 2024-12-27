#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Define the GPIO pin for the built-in LED
#define LED_PIN GPIO_NUM_2 // Usually GPIO 2 for ESP32 built-in LED

void app_main(void)
{
    // Reset the GPIO pin configuration to the default state
    gpio_reset_pin(LED_PIN);

    // Configure the LED pin as an output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        // Turn the LED on
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 ms

        // Turn the LED off
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 ms
    }
}