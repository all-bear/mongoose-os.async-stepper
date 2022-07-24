#include "mgos_async_stepper.h"

AsyncStepper *mgos_AsyncStepper_create(unsigned int step_delay, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) {
    return new AsyncStepper(step_delay, motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4);
}

void mgos_AsyncStepper_move(AsyncStepper *stepper, int steps) {
    if (stepper == nullptr) return;

    stepper->move(steps);
}

void mgos_AsyncStepper_run(AsyncStepper *stepper) {
    if (stepper == nullptr) return;

    stepper->run();
}

void mgos_AsyncStepper_startLoop(AsyncStepper *stepper) {
    if (stepper == nullptr) return;

    stepper->startLoop();
}