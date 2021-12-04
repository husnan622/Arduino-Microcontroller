#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Ultrasonic
#define pinTrigger 8 // pin trigger HC-SR04
#define pinEcho 9 // pin echo HC-SR04
#define pinPotensiometer A0 // pin potensiometer

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
#define pinServo 10 // pin Signal Servo
Servo myservo; // Membuat objek untuk mengendalikan servo
int val;

void setup() {
  Serial.begin(9600);
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
  delay(2000);
}

void loop() {
  // Membersihkan pin pinTrigger selama 2 microdetik
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  // Set pinTrigger menjadi HIGH selama 10 microdetik
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Membaca pinEcho, mengembalikan waktu perjalanan gelombang suara dalam mikrodetik
  long duration = pulseIn(pinEcho, HIGH);
  int distanceCm = duration * 0.034 / 2;  // Jarak satuan sentimeter

  // Membaca nilai pin potensiometer
  val = analogRead(pinPotensiometer);

  // Pemetaan skala nilai analog (0-1023) menjadi derajat (0-180)
  val = map(val, 0, 1023, 0, 180);

  // Atur posisi servo sesuai derajat yang ditentukan oleh potensiometer
  myservo.write(val);

  // Tampilkan derajat putaran
  lcd.setCursor(0, 0);
  lcd.print("Posisi: " + String(val));
  lcd.write(0);

  // Tampilkan jarak rintangan
  lcd.setCursor(0, 1);
  lcd.print("Jarak: " + String(distanceCm) + " cm");
  delay(10);
  lcd.clear();
}
