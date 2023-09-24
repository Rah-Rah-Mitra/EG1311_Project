#include "motorControl.h"
#include "Arduino.h"
#include "Servo.h"

//Motor_1 Connection
int ENABLE_1 = 11;
int MOTOR_1_A = 10;
int MOTOR_1_B = 9;

//Motor_2 Connection
int ENABLE_2 = 5;
int MOTOR_2_A = 4;
int MOTOR_2_B = 3;

//Ultrasonic Sensor
int TRIG_PIN = 6;
int ECHO_PIN = 7;

//Servo Motor
int SERVO_PIN = 2;

//Constants
float SPEED_OF_SOUND = 0.0345;

MotorControl motorControl(ENABLE_1 ,MOTOR_1_A ,MOTOR_1_B ,ENABLE_2 ,MOTOR_2_A ,MOTOR_2_B);
Servo myservo; 


float get_distance(int TRIG_PIN , int ECHO_PIN){
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float Ultrasonic_Data = microsecs*SPEED_OF_SOUND/2;
  Serial.println("Distance Measured (cm): " + String(Ultrasonic_Data));
  return Ultrasonic_Data;
}

void moveServo() {
  myservo.write(90);  // tell servo to go to position in variable 'pos'
  delay(15);          // waits 15ms for the servo to reach the position
}

void setup() {
  myservo.attach(SERVO_PIN); // initialise servo
  Serial.begin(9600);
}

void loop() {
  motorControl.forward_motor_1();
  delay(1000);
  motorControl.stop_motor_1();
  delay(1000);
}