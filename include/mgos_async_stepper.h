#ifndef CS_MOS_LIBS_ASYNC_STEPPER_H_
#define CS_MOS_LIBS_ASYNC_STEPPER_H_

#include "AsyncStepper.h"

#ifdef __cplusplus
extern "C" {
#endif

AsyncStepper *mgos_AsyncStepper_create(unsigned int step_delay, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

void mgos_AsyncStepper_move(AsyncStepper *stepper, int steps);
void mgos_AsyncStepper_run(AsyncStepper *stepper);
void mgos_AsyncStepper_startLoop(AsyncStepper *stepper);

#ifdef __cplusplus
}
#endif

#endif /* CS_MOS_LIBS_ASYNC_STEPPER_H_ */