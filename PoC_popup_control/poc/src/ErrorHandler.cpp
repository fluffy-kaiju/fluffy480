#include <ErrorHandler.hpp>

#define ERROR_LED GPIO_NUM_2

void panic(const char* message) {
    Serial.printf("\n!!! FATAL ERROR: %s !!!\n", message);
    pinMode(ERROR_LED, OUTPUT);
    while (true) {
        digitalWrite(ERROR_LED, !digitalRead(ERROR_LED)); // Toggle LED
        delay(500);
        yield(); // Keeps the ESP32 Watchdog happy
    }
}
