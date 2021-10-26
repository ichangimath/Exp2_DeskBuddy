#include <Servo.h>

const int ledLeft = 8;
const int ledRight = 6;
const int ledmidLeft = 13;
const int ledmidRight = 12;
const int ledTop = 7;
const int ledWhite = 0;
const int ledGreen = 1;
const int ledRed = 2;
const int servoLegs = 9;
const int servoTongue = 11;
const int servoSun = 10;
const int LDR_Ball_pin = A5;
const int LDR_Sun_pin = A4;

int LDR_Ball;
int LDR_Sun;


Servo sLegs;
Servo sTongue;
Servo sSun;

unsigned long tStart = 0;

unsigned long tongueStart = 0;

int sunPos = 0;

int trigger = 0;
int trigger2 = 0;

int dogPos = 0;
int tonguePos = 0;

int dogSittingTime = 0;


void setup() {
  sLegs.attach(servoLegs);
  sTongue.attach(servoTongue);
  sSun.attach(servoSun);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledmidLeft, OUTPUT);
  pinMode(ledmidRight, OUTPUT);
  pinMode(ledTop, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(LDR_Ball, INPUT);
  pinMode(LDR_Sun, INPUT);
}
void dogSit() {
  for (int pos = 80; pos >= 10; pos -= 1) {
    sLegs.write(pos);
    delay(5);
  }
  dogPos = 0;
}
void dogStand() {
  for (int pos = 10; pos <= 80; pos += 1) {
    sLegs.write(pos);
    delay(5);
  }
  dogPos = 1;
}
void tongueOut(int x) {
  sTongue.write(constrain(x, 0, 90));
  tonguePos = 1;
}

void tongueIn() {
  for (int pos = 90; pos >= 0; pos -= 1) {
    sTongue.write(pos);
    delay(5);
  }
  tonguePos = 0;
}

void sunRise(int sunPos) {
  sSun.write(sunPos);
  if (sunPos < 80 || sunPos > 110)
    digitalWrite(ledRed, HIGH);
  if (sunPos > 75 && sunPos < 80)
    digitalWrite(ledGreen, HIGH);
  if (sunPos > 110 && sunPos < 115)
    digitalWrite(ledGreen, HIGH);
  digitalWrite(ledWhite, HIGH);
}
void sunSet() {
  for (sunPos = 70; sunPos <= 110; sunPos += 1) {
    sSun.write(sunPos);
    delay(5);
  }
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledWhite, LOW);
}
void leftLoop() {
  digitalWrite(ledmidLeft, HIGH);
  digitalWrite(ledLeft, HIGH);
  digitalWrite(ledTop, HIGH);
  digitalWrite(ledmidRight, LOW);
  digitalWrite(ledRight, LOW);
}
void rightLoop() {
  digitalWrite(ledmidLeft, LOW);
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledmidRight, HIGH);
  digitalWrite(ledRight, HIGH);
  digitalWrite(ledTop, HIGH);
}
void allLEDOff() {
  digitalWrite(ledmidLeft, LOW);
  digitalWrite(ledLeft, LOW);
  digitalWrite(ledmidRight, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledTop, LOW);
}
void loop() {
  LDR_Ball=analogRead(LDR_Ball_pin);
  LDR_Sun=analogRead(LDR_Sun_pin);

  if (LDR_Sun > 200)
  {
    if (trigger == 0)
      tStart = millis();
    trigger = 1;
    sunRise(int(constrain(map(((millis() - tStart) / 60000), 0, 720, 110, 70), 110, 70)));
  }
  if (LDR_Sun <200)
  {
    sunSet();
    trigger = 0;
  }
  if (LDR_Ball <150)
  {
    if (dogPos == 1)
      dogSit();
    if (trigger2 == 0)
      tongueStart = millis();
    trigger2 = 1;
    tongueOut(map(((millis() - tongueStart) / 1000), 0, 60, 0, 90));
    leftLoop();
    delay(3000);
    rightLoop();
    delay(3000);
    leftLoop();
    delay(3000);
    rightLoop();
    delay(3000);
    allLEDOff();
  }
  if (LDR_Ball >150)
  {
    if (dogPos == 0)
      dogStand();
    if (tonguePos == 1)
      tongueIn();
    allLEDOff();
    trigger2 = 0;
  }


}
