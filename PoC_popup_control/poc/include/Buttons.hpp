#include "Arduino.h"
#include <GPIOGuard.hpp>

class Button : public GPIOGuard {
private:
  const gpio_num_t _pin;
  bool _lastState;

public:
  Button(gpio_num_t pin);
  ~Button();
  bool isPressed(bool debug = false);
  void *onPress(void *(*callback)(void *), void *data = nullptr);
  void *onChange(void *(*callback)(void *), void *data = nullptr);
};

Button::~Button(){}

Button::Button(gpio_num_t pin) : GPIOGuard(pin), _pin(pin) {
  pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed(bool debug) {
  if (debug) {
    bool pressed = !(bool)digitalRead(_pin);
    Serial.printf("B[%d]:(%s)\n", _pin, pressed ? "pressed" : "not pressed");
    return pressed;
  }
  return !(bool)digitalRead(_pin);
}

void *Button::onPress(void *(*callback)(void *), void *data) {
  if (this->isPressed()) {
    return callback(data);
  }
  return nullptr;
}

void *Button::onChange(void *(*callback)(void *), void *data) {
  bool currentState = this->isPressed();
  if (currentState != _lastState) {
    void *result = callback(data);
    _lastState = currentState;
    return result;
  }
  return nullptr;
}
