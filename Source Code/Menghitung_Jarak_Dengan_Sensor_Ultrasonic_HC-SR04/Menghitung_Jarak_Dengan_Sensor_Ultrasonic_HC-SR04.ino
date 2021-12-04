#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int pinTrigger = 9; // pin trigger HC-SR04
const int pinEcho = 8; // pin echo HC-SR04
long duration;
int distanceCm, distanceInch;

// Atur alamat LCD pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{    
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("Menghitung Jarak");
  lcd.setCursor(0, 1);
  lcd.print("Dengan Ultrasonic ");
  pinMode(pinTrigger, OUTPUT); // set pin trigger sebagai output
  pinMode(pinEcho, INPUT); // set pin echo sebagai input
}

void loop()
{
  // Membersihkan pin pinTrigger selama 2 microdetik
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);

  // Set pinTrigger menjadi HIGH selama 10 microdetik
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);

  // Membaca pinEcho, mengembalikan waktu perjalanan gelombang suara dalam mikrodetik
  duration = pulseIn(pinEcho, HIGH);
  distanceCm = duration * 0.034 / 2;  // Jarak dalam CM
  distanceInch = duration * 0.0133 / 2; // Jarak dalam INCH
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(String(distanceCm));
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Jarak: ");
  lcd.print(String(distanceInch));
  lcd.print(" inch");

  delay(1000); //tunda 1 detik agar LCD tidak terlalu flicker
}
