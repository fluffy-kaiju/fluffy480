#include "Arduino.h"
#include <Potentiometer10K.hpp>
#include <Buttons.hpp>
#include <DRV8833.hpp>

Buttons buttonForward = Buttons(GPIO_NUM_25);
Buttons buttonReverse = Buttons(GPIO_NUM_26);

DRV8833 motor = DRV8833(GPIO_NUM_18, GPIO_NUM_19);

Potentiometer10K whitePot = Potentiometer10K(GPIO_NUM_34);
Potentiometer10K motPot = Potentiometer10K(GPIO_NUM_35);

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  // Todo: add a member to the class to run lamda only when the value changes.
  //       Constructor should have a treshold parameter to determine how much the value should change before triggering the callback.
  const int whitePotValue = whitePot.getValuePercent(true);
  const int motPotValue = motPot.getValuePercent(true);

  buttonForward.onChange([](void *data) -> void *
                         {
                            DRV8833 *motor = (DRV8833 *)data;
                            bool isPressed = buttonForward.isPressed();
                            if (isPressed)
                            {
                            motor->goForward(true);
                            }
                            else
                            {
                              motor->stop(true);
                            }
                            return nullptr; }, &motor);

  buttonReverse.onChange([](void *data) -> void *
                         {
                            DRV8833 *motor = (DRV8833 *)data;
                            bool isPressed = buttonReverse.isPressed();
                            if (isPressed)
                            {
                              motor->goReverse(true);
                            }
                            else
                            {
                              motor->stop(true);
                              Serial.printf("Motor stop\n");
                            }
                            return nullptr; }, &motor);
  delay(100);
}
