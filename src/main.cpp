#include "motorControl.h"
#include "Arduino.h"
#include "Servo.h"

//Motor_1 Connection
int ENABLE_1 = 13;
int MOTOR_1_A = 12;
int MOTOR_1_B = 11;

//Motor_2 Connection
int ENABLE_2 = 5;
int MOTOR_2_A = 4;
int MOTOR_2_B = 3;

//Ultrasonic Sensor
int TRIG_PIN = 6;
int ECHO_PIN = 7;

//Servo Motor
int SERVO_PIN = 10;

//Constants
float SPEED_OF_SOUND = 0.0345;

MotorControl motorControl(ENABLE_1 ,MOTOR_1_A ,MOTOR_1_B ,ENABLE_2 ,MOTOR_2_A ,MOTOR_2_B);
Servo myservo; 


float get_distance(int TRIG_PIN , int ECHO_PIN){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;
  Serial.println("Distance(cm): " + String(distance));
  return distance;
}


void moveServo(int _delay) {
  int pos = 0;
  for (pos = 0; pos <= 180; pos += 1) {   // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(_delay);                        // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) {   // goes from 180 degrees to 0 degrees
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(_delay);                        // waits 15ms for the servo to reach the position
  }
}

void setup() {
  myservo.attach(SERVO_PIN); // initialise servo
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN,LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  motorControl.accelerate_both_motors(2000);
  motorControl.forward_both_motors();
  delay(2000);
  motorControl.decelerate_both_motors(2000); // ms
  motorControl.backward_both_motors();
  delay(5000);
  get_distance(TRIG_PIN,ECHO_PIN); // cm
  moveServo(2); // Duration of 1 rotation cycle [ 1 <= int <= 15 ]
}
