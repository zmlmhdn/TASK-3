// Motor driver pins - ADJUST TO YOUR WIRING
#define LEFT_MOTOR_DIR1 5
#define LEFT_MOTOR_DIR2 12
#define LEFT_MOTOR_PWM 10

#define RIGHT_MOTOR_DIR1 6
#define RIGHT_MOTOR_DIR2 13
#define RIGHT_MOTOR_PWM 11

// Robot parameters
#define WHEEL_BASE 0.25  // Distance between wheels in meters
#define MAX_SPEED 255

#define START_BYTE 0xFF
#define END_BYTE 0xFE

void setup() {
  Serial.begin(57600);
  
  // Setup motor pins
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(LEFT_MOTOR_DIR1, OUTPUT);
  pinMode(LEFT_MOTOR_DIR2, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR1, OUTPUT);
  pinMode(RIGHT_MOTOR_DIR2, OUTPUT);
  
  stopMotors();
}

void loop() {
  if (Serial.available() >= 10) {  // 1 + 4 + 4 + 1 bytes
    byte start = Serial.read();
    
    if (start == START_BYTE) {
      // Read linear and angular velocities
      float linear_x, angular_z;
      Serial.readBytes((char*)&linear_x, 4);
      Serial.readBytes((char*)&angular_z, 4);
      byte end = Serial.read();
      
      if (end == END_BYTE) {
        // Calculate wheel speeds
        float left_speed = linear_x - (angular_z * WHEEL_BASE / 2.0);
        float right_speed = linear_x + (angular_z * WHEEL_BASE / 2.0);
        
        // Convert to PWM
        int left_pwm = constrain(left_speed * 100, -MAX_SPEED, MAX_SPEED);
        int right_pwm = constrain(right_speed * 100, -MAX_SPEED, MAX_SPEED);
        
        setMotorSpeed(left_pwm, right_pwm);
      }
    }
  }
}

void setMotorSpeed(int left, int right) {
  // Left motor
  if (left > 0) {
    digitalWrite(LEFT_MOTOR_DIR1, HIGH);
    digitalWrite(LEFT_MOTOR_DIR2, LOW);
    analogWrite(LEFT_MOTOR_PWM, abs(left));
  } else if (left < 0) {
    digitalWrite(LEFT_MOTOR_DIR1, LOW);
    digitalWrite(LEFT_MOTOR_DIR2, HIGH);
    analogWrite(LEFT_MOTOR_PWM, abs(left));
  } else {
    digitalWrite(LEFT_MOTOR_DIR1, LOW);
    digitalWrite(LEFT_MOTOR_DIR2, LOW);
    analogWrite(LEFT_MOTOR_PWM, 0);
  }
  
  // Right motor
  if (right > 0) {
    digitalWrite(RIGHT_MOTOR_DIR1, HIGH);
    digitalWrite(RIGHT_MOTOR_DIR2, LOW);
    analogWrite(RIGHT_MOTOR_PWM, abs(right));
  } else if (right < 0) {
    digitalWrite(RIGHT_MOTOR_DIR1, LOW);
    digitalWrite(RIGHT_MOTOR_DIR2, HIGH);
    analogWrite(RIGHT_MOTOR_PWM, abs(right));
  } else {
    digitalWrite(RIGHT_MOTOR_DIR1, LOW);
    digitalWrite(RIGHT_MOTOR_DIR2, LOW);
    analogWrite(RIGHT_MOTOR_PWM, 0);
  }
}

void stopMotors() {
  setMotorSpeed(0, 0);
}