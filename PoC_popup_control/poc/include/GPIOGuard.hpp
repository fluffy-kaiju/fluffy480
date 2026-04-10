#pragma once
#include <Arduino.h>
#include <ErrorHandler.hpp>
#include <array>
#include <stdexcept>
#include <vector>

class GPIOGuard {
private:
  static std::array<bool, GPIO_NUM_MAX> usedPins;

protected:
  template <typename... Pins> GPIOGuard(Pins... pins);
  virtual ~GPIOGuard();
  std::vector<gpio_num_t> _pins;

public:
};

std::array<bool, GPIO_NUM_MAX> GPIOGuard::usedPins = {};

template <typename... Pins>
GPIOGuard::GPIOGuard(Pins... pins) : _pins({static_cast<gpio_num_t>(pins)...}) {
  for (gpio_num_t pin : this->_pins) {

    if (this->usedPins[pin] == true) {
      std::string error =
          "ERROR: duplicate use of pin " + std::to_string(pin) + "!";
      panic(error.c_str());
    }
    this->usedPins[pin] = true;
    Serial.printf("Register pin(%d)\n", pin);
  }
}

GPIOGuard::~GPIOGuard() {
  for (gpio_num_t pin : this->_pins) {
    this->usedPins[pin] = false;
    Serial.printf("Unregister pin(%d)\n", pin);
  }
}
