#ifndef AsyncStepper_h
#define AsyncStepper_h

class AsyncStepper {
  public:
    AsyncStepper(unsigned int step_delay, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void move(int steps);
    void run();
    void startLoop();

  private:
    void applyNextStepPhase();
    void applyStepPhase(unsigned char phase);
    void release();

    int steps_left;
    char step_direction_increment;
    unsigned long last_step_time;
    unsigned int step_delay;
    unsigned char current_step_phase;
    bool is_movement_done;

    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
};

#endif
