/*
  Project: Smart Arduino Line Follower Robot
  Version: 2.0
  Author: Rahul (AR Rider Chronicles)
  Description: 
  Improved line follower robot code with smooth turns, serial debugging, 
  auto-calibration, and flexible speed control.
*/

#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5

// Base Speeds
int M1_Speed = 120;
int M2_Speed = 120;
int LeftRotationSpeed = 180;
int RightRotationSpeed = 180;

// Calibration threshold (auto-adjusted)
int threshold = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(A0, INPUT); // Left sensor
  pinMode(A1, INPUT); // Right sensor

  Serial.println("Calibrating sensors...");
  delay(1000);
  calibrateSensors();
  Serial.println("Calibration complete!");
}

void loop() {
  int LEFT_SENSOR = analogRead(A0);
  int RIGHT_SENSOR = analogRead(A1);

  Serial.print("Left: ");
  Serial.print(LEFT_SENSOR);
  Serial.print(" | Right: ");
  Serial.println(RIGHT_SENSOR);

  if (RIGHT_SENSOR < threshold && LEFT_SENSOR < threshold) {
    forward();
  } 
  else if (RIGHT_SENSOR < threshold && LEFT_SENSOR > threshold) {
    right();
  } 
  else if (RIGHT_SENSOR > threshold && LEFT_SENSOR < threshold) {
    left();
  } 
  else {
    Stop();
  }
}

// --- Movement Functions ---
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, LeftRotationSpeed / 2);
  analogWrite(enB, RightRotationSpeed);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed / 2);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

// --- Sensor Calibration ---
void calibrateSensors() {
  int leftTotal = 0, rightTotal = 0;
  for (int i = 0; i < 50; i++) {
    leftTotal += analogRead(A0);
    rightTotal += analogRead(A1);
    delay(20);
  }
  threshold = (leftTotal / 50 + rightTotal / 50) / 2;
  Serial.print("Threshold set to: ");
  Serial.println(threshold);
}
