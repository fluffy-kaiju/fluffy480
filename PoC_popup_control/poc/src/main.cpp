#include <Arduino.h>
#include <Buttons.hpp>
#include <DRV8833.hpp>
#include <Potentiometer10K.hpp>

Button *buttonForward = nullptr;
Button *buttonReverse = nullptr;

DRV8833 *motor = nullptr;

Potentiometer10K *whitePot = nullptr;
Potentiometer10K *motPot = nullptr;

void setup() {
  Serial.begin(115200);
  buttonForward = new Button(GPIO_NUM_25);
  buttonReverse = new Button(GPIO_NUM_26);

  motor = new DRV8833(GPIO_NUM_18, GPIO_NUM_19);
  motor = new DRV8833(GPIO_NUM_18, GPIO_NUM_19);

  whitePot = new Potentiometer10K(GPIO_NUM_34);
  motPot = new Potentiometer10K(GPIO_NUM_35);
}

void loop() {

  // Todo: add a member to the class to run lamda only when the value changes->
  //       Constructor should have a treshold parameter to determine how much
  //       the value should change before triggering the callback->
  const int whitePotValue = whitePot->getValuePercent(true);
  const int motPotValue = motPot->getValuePercent(true);

  // Skip if both buttons are pressed
  if (!(buttonForward->isPressed() && buttonReverse->isPressed())) {
    buttonForward->onChange(
        [](void *data) -> void * {
          DRV8833 *motor = (DRV8833 *)data;
          bool isPressed = buttonForward->isPressed();
          if (isPressed) {
            motor->goForward(true);
          } else {
            motor->stop(true);
          }
          return nullptr;
        },
        &motor);

    buttonReverse->onChange(
        [](void *data) -> void * {
          DRV8833 *motor = (DRV8833 *)data;
          bool isPressed = buttonReverse->isPressed();
          if (isPressed) {
            motor->goReverse(true);
          } else {
            motor->stop(true);
            Serial.printf("Motor stop\n");
          }
          return nullptr;
        },
        &motor);
  }

  delay(100);
}
