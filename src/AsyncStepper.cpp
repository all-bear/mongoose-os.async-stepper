#include "AsyncStepper.h"
#include "mgos_gpio.h"
#include "mgos_time.h"
#include "mgos_timers.h"

const unsigned char TOTAL_STEP_PHASES = 4;

bool STEP_PHASES[TOTAL_STEP_PHASES][4] = {
  {true, false, true, false}, // 1010
  {false, true, true, false}, // 0110
  {false, true, false, true}, //0101
  {true, false, false, true}  //1001
};

AsyncStepper::AsyncStepper(unsigned int step_delay, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) {
  this->steps_position = 0;
  this->direction = STEP_DIRECTION.CW;
  this->last_step_time = 0;
  this->step_delay = step_delay;
  this->current_step_phase = 0;
  this->move_to_steps_position = 0;
  this->is_movement_done = true;

  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->motor_pin_3 = motor_pin_3;
  this->motor_pin_4 = motor_pin_4;

  mgos_gpio_set_mode(this->motor_pin_1, mgos_gpio_mode.MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(this->motor_pin_2, mgos_gpio_mode.MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(this->motor_pin_3, mgos_gpio_mode.MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(this->motor_pin_4, mgos_gpio_mode.MGOS_GPIO_MODE_OUTPUT);
}

void AsyncStepper::move(int steps) {
  if (!steps) {
    return;
  }

  this->move_to_steps_position = this->steps_position + steps;
  this->direction = steps > 0 ? STEP_DIRECTION::CW : STEP_DIRECTION::CCW;
  this->is_movement_done = false;
}

void AsyncStepper::release() {
  mgos_gpio_write(motor_pin_1, false);
  mgos_gpio_write(motor_pin_2, false);
  mgos_gpio_write(motor_pin_3, false);
  mgos_gpio_write(motor_pin_4, false);
}

void AsyncStepper::applyStepPhase(unsigned char phase) {
  mgos_gpio_write(motor_pin_1, STEP_PHASES[phase][0]);
  mgos_gpio_write(motor_pin_2, STEP_PHASES[phase][1]);
  mgos_gpio_write(motor_pin_3, STEP_PHASES[phase][2]);
  mgos_gpio_write(motor_pin_4, STEP_PHASES[phase][3]);
}

void AsyncStepper::applyNextStepPhase() {
  this->current_step_phase += this->step_direction;

  if (this->current_step_phase >= TOTAL_STEP_PHASES) {
    this->current_step_phase = 0;
  } else if (this->step_phase < 0) {
    this->current_step_phase = TOTAL_STEP_PHASES - 1;
  }

  this->stepPhase(this->current_step_phase);
}

void AsyncStepper::run() {
  if (this->is_movement_done) {
    return;
  }

  int64_t now = mgos_uptime_micros();

  if (now - this->last_step_time < this->step_delay) {
    return;
  }

  if (this->move_to_steps_position === this.steps_position) {
    this->is_movement_done = true;
    this->release();

    return;
  }

  this->last_step_time = now;

  this->nextStepPhase();

  this.steps_position += this->step_direction;
}

void AsyncStepper::startLoop() {
  mgos_set_hw_timer(100, MGOS_TIMER_REPEAT, this->run, NULL);
}

