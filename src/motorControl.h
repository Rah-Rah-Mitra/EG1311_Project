#ifndef MotorControl_h
#define MotorControl_h

#include "Arduino.h"

class MotorControl {
  public:
    MotorControl(int ENABLE_1, int MOTOR_1_A, int MOTOR_1_B, int ENABLE_2, int MOTOR_2_A, int MOTOR_2_B);
    void forward_motor_1();
    void forward_motor_2();
    void accelerate_motor_1();
    void accelerate_motor_2();
    void decelerate_motor_1();
    void decelerate_motor_2();
    void backward_motor_1();
    void backward_motor_2();
    void stop_motor_1();
    void stop_motor_2();
    void turn_left();
    void turn_right();
    void forward_both_motors();
    void backward_both_motors();
    void accelerate_both_motors(int accelerationTime);
    void decelerate_both_motors(int decelerationTime);
    void stop_both_motors();
  private:
    int _ENABLE_1;
    int _MOTOR_1_A;
    int _MOTOR_1_B;
    int _ENABLE_2;
    int _MOTOR_2_A;
    int _MOTOR_2_B;
};

#endif
