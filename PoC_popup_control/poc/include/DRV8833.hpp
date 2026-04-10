#include <Arduino.h>
#include <GPIOGuard.hpp>
class DRV8833 : public GPIOGuard {
private:
  const gpio_num_t _mot1Pin1;
  const gpio_num_t _mot1Pin2;

public:
  DRV8833(gpio_num_t inputPin1, gpio_num_t inputPin2);
  ~DRV8833();
  void goForward(bool debug = false);
  void goReverse(bool debug = false);
  void stop(bool debug = false);
};

DRV8833::DRV8833(gpio_num_t inputPin1, gpio_num_t inputPin2)
    : GPIOGuard(inputPin1, inputPin2), _mot1Pin1(inputPin1),
      _mot1Pin2(inputPin2) {
  pinMode(_mot1Pin1, OUTPUT);
  pinMode(_mot1Pin2, OUTPUT);

  this->stop();
}

DRV8833::~DRV8833() {
  digitalWrite(_mot1Pin1, LOW);
  digitalWrite(_mot1Pin2, LOW);
}

void DRV8833::goForward(bool debug) {
  digitalWrite(_mot1Pin1, LOW);
  digitalWrite(_mot1Pin2, HIGH);
  if (debug) {
    Serial.printf("Motor forward\n");
  }
}

void DRV8833::goReverse(bool debug) {
  digitalWrite(_mot1Pin1, HIGH);
  digitalWrite(_mot1Pin2, LOW);
  if (debug) {
    Serial.printf("Motor reverse\n");
  }
}

void DRV8833::stop(bool debug) {
  digitalWrite(_mot1Pin1, LOW);
  digitalWrite(_mot1Pin2, LOW);
  if (debug) {
    Serial.printf("Motor stop\n");
  }
}
