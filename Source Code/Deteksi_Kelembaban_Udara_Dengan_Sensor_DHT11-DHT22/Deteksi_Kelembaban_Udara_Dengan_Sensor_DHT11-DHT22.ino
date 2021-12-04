#include <SimpleDHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinDHT 2

// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);
SimpleDHT11 dht11(pinDHT);
// jika menggunakan sensor DHT22
// SimpleDHT22 dht22(pinDHT22); 

byte derajat[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000,
  B00000 };

void setup() {
  Serial.begin(9600);

  lcd.init(); // Inisialisasi LCD
  lcd.createChar(0, derajat);
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("    Deteksi    ");
  lcd.setCursor(0, 1);
  lcd.print("  Kelembaban   ");
  delay(1000);
}

void loop() {
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err); delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature);
  Serial.print(" *C, ");
  Serial.print((int)humidity);
  Serial.println(" H");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatur: " + String((int)temperature));
  lcd.write(0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Kelembaban: " + String((int)humidity) + "H");

  // DHT11 sampling rate 1HZ.
  delay(1500);
}
