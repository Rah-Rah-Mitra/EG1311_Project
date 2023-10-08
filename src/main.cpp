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
bool FIRED = false;

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
  
  // Check if duration is 0
  if (duration == 0) {
    Serial.println("Error: Ultrasonic sensor not initialized or no obstacle within range");
    return -1;  // Return -1 to indicate an error
  }
  
  float distance = (duration * 0.0343) / 2;
  Serial.println("Distance(cm): " + String(distance));
  return distance;
}


void moveServo(int _fire_angle, int _buffer) {
  if (!FIRED) {
    myservo.attach(SERVO_PIN); // initialise servo only when moveServo is first called
    FIRED = true;
  }

  int pos = _fire_angle;
  for (pos = _fire_angle; pos <= _fire_angle + _buffer; pos += 1) {   // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(500);                            // waits 500ms at top
  }
  for (pos = _fire_angle + _buffer; pos >= 0; pos -= 2) {   // goes from 180 degrees to 0 degrees
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    delay(15);                            // waits 15ms for the servo to reach the position
  }
}

void setup() {
  delay(2000); // Wait for 2 seconds for all components to power up
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN,LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int state = 0;
  float distance;

  while((distance = get_distance(TRIG_PIN,ECHO_PIN)) >= 0) // loop as long as the ultrasonic sensor is initiated
  {
    switch(state) {
      case 0: // Case 0: Moving forward until distance is 5
        if(distance >= 5) {
          motorControl.forward_both_motors();
        } else {
          state = 1; // Switch to case 1
        }
        break;

      case 1: // Case 1: Initiate the servo and delay for 1 second
        motorControl.stop_both_motors();
        moveServo(120,2); //  (Launch Angle, Rotation Buffer)
        delay(1000);
        state = 2; // Switch to case 2
        break;

      case 2: // Case 2: Move backwards for the rest of the duration
        motorControl.backward_both_motors();
        break;
    }
  }
}
