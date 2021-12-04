#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Ultrasonic
const int pinTrigger = 8; // pin trigger HC-SR04
const int pinEcho = 9; // pin echo HC-SR04

// Atur alamat LCD pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Karakter derajat
byte derajat[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000
};

// Servo
const int pinServo = 10; // pin Signal Servo
Servo myservo; // Membuat objek untuk mengendalikan servo

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.createChar(0, derajat);
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("HITUNG JARAK");
  lcd.setCursor(0, 1);
  lcd.print("& SERVO SWEEP");

  pinMode(pinTrigger, OUTPUT); // set pin trigger sebagai output
  pinMode(pinEcho, INPUT); // set pin echo sebagai input

  // attach pin servo pin
  myservo.attach(pinServo);
}

void loop() {  
  rotasi_dan_jarak(0);
  rotasi_dan_jarak(45);
  rotasi_dan_jarak(90);
  rotasi_dan_jarak(135);
  rotasi_dan_jarak(180);
  rotasi_dan_jarak(135);
  rotasi_dan_jarak(90);
  rotasi_dan_jarak(45);
}

void rotasi_dan_jarak(int deg) {
  myservo.write(deg);

  // Membersihkan pin pinTrigger selama 2 microdetik
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  // Set pinTrigger menjadi HIGH selama 10 microdetik
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Membaca pinEcho, mengembalikan waktu perjalanan gelombang suara dalam mikrodetik
  long duration = pulseIn(pinEcho, HIGH);
  int distanceCm = duration * 0.034 / 2;  // Jarak dalam CM

  lcd.setCursor(0, 0);
  lcd.print("Posisi: " + String(deg)); // Tampilkan derajat putaran
  lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.print("Jarak: " + String(distanceCm) + " cm"); // Tampilkan jarak rintangan
  delay(2000); // Tunda per 2 detik
  lcd.clear();
}
