#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>

SoftwareSerial Bluetooth(7, 6); // RX, TX

#define pinServo 10
Servo myservo;

#define TRIGGER_PIN 8
#define ECHO_PIN 9
#define MAX_DISTANCE 500
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define MotorKiri_IN1 2
#define MotorKiri_IN2 3
#define MotorKanan_IN1 4
#define MotorKanan_IN2 5

#define MotorKiri_EN 12
#define MotorKanan_EN 13
#define OB_range 30

unsigned int i = 0, pos = 0, current_distance = 0;
unsigned int range0 = 0, range30 = 0, range60 = 0, range85 = 0, range90 = 0, range95 = 0, range120 = 0, range150 = 0, range180 = 0 ;
unsigned long previous_millis = 0;
char serialData;

void setup()
{
  Serial.begin(9600);
  // Software Serial
  Bluetooth.begin(9600);
  myservo.attach(pinServo);

  pinMode(MotorKiri_IN2, OUTPUT);
  pinMode(MotorKiri_IN1, OUTPUT);
  pinMode(MotorKanan_IN2, OUTPUT);
  pinMode(MotorKanan_IN1, OUTPUT);
  pinMode(MotorKiri_EN, OUTPUT);
  pinMode(MotorKanan_EN, OUTPUT);

  analogWrite(MotorKiri_EN, 150);
  analogWrite(MotorKanan_EN, 150);
}

void brake()
{
  //berhenti
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, LOW);
}

void forward()
{
  //bergerak maju
  digitalWrite(MotorKiri_IN1, HIGH);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, HIGH);
  digitalWrite(MotorKanan_IN2, LOW);
}

void forward_left()
{
  //belok kiri dan bergerak maju
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, HIGH);
  digitalWrite(MotorKanan_IN2, LOW);
}

void forward_right()
{
  //belok kanan dan bergerak maju
  digitalWrite(MotorKiri_IN1, HIGH);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, LOW);
}

void backward()
{
  //bergerak mundur
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, HIGH);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, HIGH);
}

void backward_right()
{
  //belok kanan dan bergerak mundur
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, HIGH);
}

void backward_left()
{
  //belok kiri dan bergerak mundur
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, HIGH);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, LOW);
}

void left()
{
  //belok kiri
  digitalWrite(MotorKiri_IN1, LOW);
  digitalWrite(MotorKiri_IN2, HIGH);
  digitalWrite(MotorKanan_IN1, HIGH);
  digitalWrite(MotorKanan_IN2, LOW);
}

void right()
{
  //belok kanan
  digitalWrite(MotorKiri_IN1, HIGH);
  digitalWrite(MotorKiri_IN2, LOW);
  digitalWrite(MotorKanan_IN1, LOW);
  digitalWrite(MotorKanan_IN2, HIGH);
}

int range(int pos)
{
  myservo.write(pos);
  delay(300);
  //current_distance = sonar.ping_cm(); //hitung jarak saat ini
  current_distance = sonar.ping() / US_ROUNDTRIP_CM; //hitung jarak saat ini

  if (current_distance == 0) current_distance = 100; //jika jarak=0 maka jarak dijadikan 100
  Serial.println(current_distance);

  // jika jarak berada diantara 0 s / d 15 maka lakukan perintah di bawah
  if (current_distance > 0 && current_distance < 15) {
    Bluetooth.print("B"); // berhenti

    if (pos == 90) {
      // jika servo menghadap ke depan (90 derajat) mundur
      backward();
      delay(500);
    }

    if (pos < 90) {
      // jika servo menghadap ke kiri (0-90 dereajat)
      // maka robot akan belok ke kanan sambil mundur
      backward_right();
      delay(500);
    }

    if (pos > 90) {
      // jika servo menghadap ke kiri (90-180 dereajat)
      // maka robot akan belok ke kiri sambil mundur
      backward_left();
      delay(500);
    }
    return current_distance;
  }
}


// Perintah bluetooth
// 'A' = SET BERGERAK OTOMATIS  | 'M' = SET BERGERAK MANUAL DENGAN REMOTE
// 'F' = ROBOT BERGERAK MAJU    | 'B' = ROBOT BERGERAK MUNDUR
// 'R' = ROBOT BELOK KANAN      | 'L' = ROBOT BELOK KIRI
// 'S' = ROBOT BERHENTI

void loop() {
Automatic:
  brake();
  delay(300);
  while (1) {
    if (Bluetooth.available() > 0) serialData = Bluetooth.read();
    if (serialData == 'M') goto Manual;

above:
    range90 = 0;
    range90 = range(90);
    delay(10);
    while (range90 >= OB_range ) {
      if (millis() - previous_millis > 2000) {
        previous_millis = millis();
        range(180);
        delay(50);
        range(0);
        delay(50);
      }
      range90 = range(90);
      analogWrite(MotorKiri_EN, 150);
      analogWrite(MotorKanan_EN, 150);
      forward();
      Bluetooth.print("F");
      if (Bluetooth.available() > 0) serialData = Bluetooth.read();
      if (serialData == 'M') goto Manual;
    }
    brake();

    if (range90 < OB_range)
    {
      analogWrite(MotorKiri_EN, 100);
      analogWrite(MotorKanan_EN, 100);
      brake();
      range60 = 0;
      range60 = range(60);
      delay(200);
      range120 = 0;
      range120 = range(120);
      delay(200);
      if (Bluetooth.available() > 0) serialData = Bluetooth.read();
      if (serialData == 'M') goto Manual;
      if (range60 > OB_range || range120 > OB_range )
      {
        if (range60 >= range120) {
          forward_right();
          Bluetooth.print("R");
          delay(50);
          goto above;
        } else if (range60 < range120) {
          forward_left();
          Bluetooth.print("L");
          delay(50);
          goto above;
        }
      }

      if (range60 < OB_range && range120 < OB_range)
      {
above1:
        range30 = 0;
        range30 = range(30);
        delay(200);
        range150 = 0;
        range150 = range(150);
        delay(200);
        if (Bluetooth.available() > 0) serialData = Bluetooth.read();
        if (serialData == 'M') goto Manual;
        if (range30 > OB_range || range150 > OB_range )
        {
          if (range30 >= range150) {
            right();
            Bluetooth.print("R");
            delay(100);
            goto above;
          } else if (range30 < range150) {
            left();
            Bluetooth.print("L");
            delay(100);
            goto above;
          }
        }

        if (range30 < OB_range && range150 < OB_range)
        {
          range0 = 0;
          range0 = range(0);
          delay(200);
          range180 = 0;
          range180 = range(180);
          delay(200);
          if (Bluetooth.available() > 0) serialData = Bluetooth.read();
          if (serialData == 'M') goto Manual;
          if (range0 > OB_range || range180 > OB_range )
          {
            if (range0 >= range180) {
              backward_right();
              Bluetooth.print("R");
              delay(200);
              goto above;
            }
            else if (range0 < range180) {
              backward_left();
              Bluetooth.print("L");
              delay(200);
              goto above;
            }
          }
          if (range0 < OB_range && range180 < OB_range)
          {
            backward();
            Bluetooth.print("B");
            delay(200);
            goto above1;
          }
        }
      }
    }
  }

Manual:
  brake();
  delay(300);

  while (1) {
    if (Bluetooth.available() > 0) serialData = Bluetooth.read();
    if (serialData == 'A') goto Automatic;
    if (serialData == 'F') forward();
    if (serialData == 'B') backward();
    if (serialData == 'S') brake();
    if (serialData == 'L') left();
    if (serialData == 'R') right();
  }
}
