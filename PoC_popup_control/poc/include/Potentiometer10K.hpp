#include "Arduino.h"

class Potentiometer10K
{
private:
    const gpio_num_t _pin;
    int _lastValueAnalog;
    int _lastValuePercent;

public:
    Potentiometer10K(gpio_num_t pin);
    ~Potentiometer10K();
    int getAnalogValue(bool debug = false);
    int getValuePercent(bool debug = false);
};

Potentiometer10K::Potentiometer10K(gpio_num_t pin)
    : _pin(pin)
{
    _lastValueAnalog = -1;
    _lastValuePercent = -1;
    pinMode(_pin, INPUT);
}

Potentiometer10K::~Potentiometer10K()
{
}

/**
 * @brief Get the raw analog value from the potentiometer (0-4095).
 * @param debug If true, will print the value to serial when it changes. Otherwise, just return the value.
 * @return The raw analog value from the potentiometer (0-4095).
 */
int Potentiometer10K::getAnalogValue(bool debug)
{
    if (debug)
    {
        const int val = analogRead(_pin);
        if (val != _lastValueAnalog)
        {
            Serial.printf("Pot[%d]: %d\n", _pin, val);
        }
        _lastValueAnalog = val;
        return val;
    }
    return analogRead(_pin);
}

/**
 * @brief Get the potentiometer value as a percentage (0-100%).
 * @param debug If true, will print the value to serial when it changes. Otherwise, just return the value.
 * @return The potentiometer value as a percentage (0-100%).
 */
int Potentiometer10K::getValuePercent(bool debug)
{

    if (debug)
    {
        const int val = map(this->getAnalogValue(false), 0, 4095, 0, 100);
        if (val != _lastValuePercent)
        {
            Serial.printf("Pot[%d]: %d%%\n", _pin, val);
        }
        _lastValuePercent = val;
        return val;
    }

    return map(this->getAnalogValue(false), 0, 4095, 0, 100);
}
