#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pinPIRSensor = 2;
int pinRelay = 3;
int statusPanas = LOW;
int nilaiSensor = 0;

// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(pinPIRSensor, INPUT); // set pin sensor sebagai input
  pinMode(pinRelay, OUTPUT);    // set pin relay sebagai output

  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("Deteksi Obyek");
  lcd.setCursor(0, 1);
  lcd.print("Sensor PIR ");
  delay(3000);
}

void loop() {
  // Membaca nilai pin sensor
  nilaiSensor = digitalRead(pinPIRSensor);

  // Sensor mendeteksi panas
  if (nilaiSensor == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Obyek Terdeteksi");
    lcd.setCursor(0, 1);
    lcd.print("Lampu Hidup");

    digitalWrite(pinRelay, HIGH); // Relay aktif untuk menghidupkan lampu
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AUTO OFF");
    lcd.setCursor(0, 1);
    lcd.print("Lampu Mati");

    // Sensor tidak mendeteksi panas
    digitalWrite(pinRelay, LOW); // Relay tidak aktif dan lampu mati
  }
  delay(1000);
}
