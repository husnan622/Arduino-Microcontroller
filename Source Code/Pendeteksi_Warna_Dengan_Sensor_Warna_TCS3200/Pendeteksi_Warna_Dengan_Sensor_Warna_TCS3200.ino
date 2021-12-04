#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Inisialisasi library
// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned int merahFreq = 0, hijauFreq = 0, biruFreq = 0;
unsigned int warnaMerah = 0, warnaHijau = 0, warnaBiru = 0;

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Pensklaan frekwensi menjadi 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // Pengaturan photodiode filter warna merah
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Membaca frekwensi output
  merahFreq = pulseIn(sensorOut, LOW, 25000) / 2;
  // lakukan kalibrasi warna merah
  // nilai map pasti berbeda
  warnaMerah = map(merahFreq, 74, 250, 255,0);


  // Pengaturan photodiode filter warna hijau
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Membaca frekwensi output
  hijauFreq = pulseIn(sensorOut, LOW, 25000) / 2;
  // lakukan kalibrasi warna hijau
  // nilai map pasti berbeda
  warnaHijau = map(hijauFreq, 102, 245, 255, 0);

  // Pengaturan photodiode filter warna biru
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Membaca frekwensi output
  biruFreq = pulseIn(sensorOut, LOW, 25000) / 2;
  // lakukan kalibrasi warna biru
  // nilai map pasti berbeda
  warnaBiru = map(biruFreq, 127, 254, 255, 0);

  // Printing the value on the serial monitor
  Serial.println("R=" + String(warnaMerah) + " G=" + String(warnaHijau) + " B=" + String(warnaBiru));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Komposisi Warna");
  lcd.setCursor(0, 1);
  lcd.print("M" + String(warnaMerah) + " H" + String(warnaHijau) + " B" + String(warnaBiru));
  delay(1000); 
}
