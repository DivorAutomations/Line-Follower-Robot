#define S1 22
#define S2 24
#define S3 26
#define S4 28
#define S5 30
#define CLP 32
#define Near 34

#define MotorLE 2
#define MotorL1 3
#define MotorL2 4
#define MotorRE 7
#define MotorR1 6
#define MotorR2 5

const int sensorArr[7] = { S1, S2, S3, S4, S5, CLP, Near };
int sensorData[7];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(sensorArr[i], INPUT);
  }

  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }

  //set motor speed
  analogWrite(MotorRE, 55);
  analogWrite(MotorLE, 55);
  //  analogWrite(MotorLE, 0);
  //  analogWrite(MotorRE, 0);

  Serial.println("Initialized");
}

void loop() {
  for (int i = 0; i < 7; i++) {
    sensorData[i] = digitalRead(sensorArr[i]);
  }

  //debugging print
  // for (int i = 0; i < 7; i++) {
  //   Serial.print("Sensor " + String(i) + ": " + String(sensorData[i]) + " | ");
  // }
  // Serial.println();

  /*
    sensorArr[0] -> leftmost sensor
    sensorArr[1] -> left mid sensor
    sensorArr[2] -> center sensor
    sensorArr[3] -> right mid sensor
    sensorArr[4] -> rightmost sensor
    sensorArr[5] -> CLP sensor
    sensorArr[6] -> Near sensor
  */

  if (!sensorData[2]) {
    analogWrite(MotorRE, 55);
    analogWrite(MotorLE, 55);
    forward();
  } else if (!sensorData[2] && !sensorData[1]) {
    analogWrite(MotorRE, 55);
    analogWrite(MotorLE, 35);
    forward();
  } else if (!sensorData[2] && !sensorData[3]) {
    analogWrite(MotorRE, 35);
    analogWrite(MotorLE, 55);
    forward();
  } else if (!sensorData[1] || !sensorData[0]) {
    analogWrite(MotorLE, 60);
    left();
  } else if (!sensorData[3] || !sensorData[4]) {
    analogWrite(MotorRE, 60);
    right();
  } else {
    _stop();
  }
}

void forward() {
  //Left motor
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  //right motor
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
}

void left() {
  //Left motor
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  //right motor
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
}

void right() {
  //Left motor
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
  //right motor
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
}

void _stop() {
  //Left motor
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
  //right motor
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
}
