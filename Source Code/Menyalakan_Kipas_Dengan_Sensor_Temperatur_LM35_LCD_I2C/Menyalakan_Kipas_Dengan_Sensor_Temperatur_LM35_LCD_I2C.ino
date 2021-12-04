#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pinRelay = 8; // Pin S Relay ke Pin 8 Arduino
int pinLED = 9;   // Pin LED Resistor ke Pin 9 Arduino
int pinLM35 = A0;  // pin LM35 ke Pin A0 Arduino (analog)

// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("INDIKATOR SUHU"); // tampilkan di LCD
  delay(4000); // tunda 4 detik
  lcd.clear();

  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLM35, INPUT);
}

void loop() {
  int suhucelcius = getTemperatureCel(pinLM35);
  int suhufarenheit = celsius_to_fahrenheit(suhucelcius);

  // Tampilkan suhu ke LCD
  lcd.clear(); // Bersihkan layar LCD
  lcd.setCursor(0,0);
  lcd.print("Celcius: " + String(suhucelcius));
  lcd.setCursor(0,1);
  lcd.print("Farenheit: " + String(suhufarenheit));
  
  // Menampilkan nilai sensor LM35
  Serial.println("Temperatur Celcius: " + String(suhucelcius) + " - " + "Farenheit: " + String(suhufarenheit));
  delay(1000);

  if (suhucelcius >= 34) {
    // Mengaktifkan relay ON dan menghidupkan kipas angin
    // jika temperatur lebih dari sama dengan 34 derajat celcius
    digitalWrite(pinLED, HIGH);
    digitalWrite(pinRelay, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
    digitalWrite(pinRelay, LOW);
  }
}

int getTemperatureCel(int pin) {
  int val = analogRead(pin);
  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;
  return (cel);
}

int celsius_to_fahrenheit(float cel) {
  float farh = (cel * 9) / 5 + 32;
  return (farh);
}
