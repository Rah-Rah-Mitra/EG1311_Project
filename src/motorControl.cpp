#include "Arduino.h"
#include "MotorControl.h"

MotorControl::MotorControl(int ENABLE_1, int MOTOR_1_A, int MOTOR_1_B, int ENABLE_2, int MOTOR_2_A, int MOTOR_2_B) {
  pinMode(ENABLE_1, OUTPUT);
  pinMode(MOTOR_1_A, OUTPUT);
  pinMode(MOTOR_1_B, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);
  pinMode(MOTOR_2_A, OUTPUT);
  pinMode(MOTOR_2_B, OUTPUT);
  _ENABLE_1 = ENABLE_1;
  _MOTOR_1_A = MOTOR_1_A;
  _MOTOR_1_B = MOTOR_1_B;
  _ENABLE_2 = ENABLE_2;
  _MOTOR_2_A = MOTOR_2_A;
  _MOTOR_2_B = MOTOR_2_B;
}

void MotorControl::forward_motor_1() {
  digitalWrite(_MOTOR_1_A, HIGH);
  digitalWrite(_MOTOR_1_B, LOW);
  digitalWrite(_ENABLE_1, HIGH);
  Serial.println("Motor_1 Forward Direction");
}

void MotorControl::forward_motor_2() {
  digitalWrite(_MOTOR_2_A, HIGH);
  digitalWrite(_MOTOR_2_B, LOW);
  digitalWrite(_ENABLE_2, HIGH);
  Serial.println("Motor_2 Forward Direction");
}

void MotorControl::accelerate_motor_1() {
  for (int i = 0; i < 256; i++) {
    analogWrite(_ENABLE_1, i);
  }
  Serial.println("Motor_1 acceleration");
}

void MotorControl::accelerate_motor_2() {
  for (int i = 0; i < 256; i++) {
    analogWrite(_ENABLE_2, i);
  }
  Serial.println("Motor_2 acceleration");
}

void MotorControl::decelerate_motor_1() {
  for (int i = 255; i > 1; i--) {
    analogWrite(_ENABLE_1, i);
    delay(5);
  }
  Serial.println("Motor_1 deceleration");
}

void MotorControl::decelerate_motor_2() {
  for (int i = 255; i > 1; i--) {
    analogWrite(_ENABLE_2, i);
    delay(5);
  }
  Serial.println("Motor_2 deceleration");
}

void MotorControl::backward_motor_1() {
  digitalWrite(_MOTOR_1_A, LOW);
  digitalWrite(_MOTOR_1_B, HIGH);
  digitalWrite(_ENABLE_1, HIGH);
  Serial.println("Motor_1 Backward Direction");
}

void MotorControl::backward_motor_2() {
  digitalWrite(_MOTOR_2_A, LOW);
  digitalWrite(_MOTOR_2_B, HIGH);
  digitalWrite(_ENABLE_2, HIGH);
  Serial.println("Motor_2 Backward Direction");
}

void MotorControl::stop_motor_1() {
  digitalWrite(_MOTOR_1_A, LOW);
  digitalWrite(_MOTOR_1_B, LOW);
  analogWrite(_ENABLE_1, 0);
  Serial.println("Stop Motor_1");
}

void MotorControl::stop_motor_2() {
  digitalWrite(_MOTOR_2_A, LOW);
  digitalWrite(_MOTOR_2_B, LOW);
  analogWrite(_ENABLE_2, 0);
  Serial.println("Stop Motor_2");
}

void MotorControl::turn_left() {
  forward_motor_1();
  backward_motor_2();
  digitalWrite(_ENABLE_1, HIGH);
  digitalWrite(_ENABLE_2, HIGH);
  Serial.println("Turn Left");
}

void MotorControl::turn_right() {
  backward_motor_1();
  forward_motor_2();
  digitalWrite(_ENABLE_1, HIGH);
  digitalWrite(_ENABLE_2, HIGH);
  Serial.println("Turn Right");
}

void MotorControl::forward_both_motors() {
  digitalWrite(_MOTOR_1_A, HIGH);
  digitalWrite(_MOTOR_1_B, LOW);
  digitalWrite(_MOTOR_2_A, HIGH);
  digitalWrite(_MOTOR_2_B, LOW);
  digitalWrite(_ENABLE_1, HIGH); // Add this line
  digitalWrite(_ENABLE_2, HIGH); // Add this line
  //Serial.println("Motor_1 and Motor_2 Forward Direction");
}

void MotorControl::backward_both_motors() {
  digitalWrite(_MOTOR_1_A, LOW);
  digitalWrite(_MOTOR_1_B, HIGH);
  digitalWrite(_MOTOR_2_A, LOW);
  digitalWrite(_MOTOR_2_B, HIGH);
  digitalWrite(_ENABLE_1, HIGH);
  digitalWrite(_ENABLE_2, HIGH);
  Serial.println("Motor_1 and Motor_2 Backward Direction");
}

void MotorControl::accelerate_both_motors(int accelerationTime) {
  digitalWrite(_MOTOR_1_A, HIGH);
  digitalWrite(_MOTOR_1_B, LOW);
  digitalWrite(_MOTOR_2_A, HIGH);
  digitalWrite(_MOTOR_2_B, LOW);

  int increment = 255 / (accelerationTime / 10); // Calculate the increment value

  for (int i = 0; i <= 255; i += increment) {
    analogWrite(_ENABLE_1, i);
    analogWrite(_ENABLE_2, i);
    delay(10);
  }
  Serial.println("Motor_1 and Motor_2 acceleration");
  delay(accelerationTime);
}

void MotorControl::decelerate_both_motors(int decelerationTime) {
  digitalWrite(_MOTOR_1_A, HIGH);
  digitalWrite(_MOTOR_1_B, LOW);
  digitalWrite(_MOTOR_2_A, HIGH);
  digitalWrite(_MOTOR_2_B, LOW);

  int decrement = 255 / (decelerationTime / 10); // Calculate the decrement value

  for (int i = 255; i >= 0; i -= decrement) {
    analogWrite(_ENABLE_1, i);
    analogWrite(_ENABLE_2, i);
    delay(10);
  }
  Serial.println("Motor_1 and Motor_2 deceleration");
  delay(decelerationTime);
}

void MotorControl::stop_both_motors() {
  digitalWrite(_MOTOR_1_A, LOW);
  digitalWrite(_MOTOR_1_B, LOW);
  digitalWrite(_MOTOR_2_A, LOW);
  digitalWrite(_MOTOR_2_B, LOW);
  analogWrite(_ENABLE_1, 0);
  analogWrite(_ENABLE_2, 0);
  Serial.println("Motor_1 and Motor_2 Stop");
}

