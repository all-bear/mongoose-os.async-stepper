let AsyncStepper = {
    _create_4_pins: ffi('void *mgos_AsyncStepper_create(int, int, int, int, int)'),
    _move: ffi('void mgos_AsyncStepper_move(void *, int)'),
    _run: ffi('void mgos_AsyncStepper_run(void *)'),
    _startLoop: ffi('void mgos_AsyncStepper_startLoop(void *)'),

    create: function(step_delay, motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4, motor_pin_5) {
        let obj = Object.create(AsyncStepper._proto);
        obj.stepper = AsyncStepper._create(step_delay, motor_pin_1, motor_pin_2, motor_pin_3, motor_pin_4);
        
        return obj;
    },

    _proto: {
        move: function(steps) {
          return AsyncStepper._move(this.stepper, steps);
        },

        run: function() {
            return AsyncStepper._run(this.stepper);
        },
        
        startLoop: function() {
            return AsyncStepper._startLoop(this.stepper);
        },
    },    
};