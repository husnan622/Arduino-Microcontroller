#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinProximity 2 // Pin Sensor
#define pinLED 3 // Pin LED
#define pinBuzzer 4 // Pin Buzzer

int isObstacle;
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2 karakter

void setup() {
  Serial.begin(9600);

  pinMode(pinLED, OUTPUT);      // pin LED arduiono sebagai output
  pinMode(pinBuzzer, OUTPUT);   // pin Speaker arduino sebagai output
  pinMode(pinProximity, INPUT); // pin Sensor arduino sebagai input

  // inisialisasi data
  digitalWrite(pinLED, LOW);
  digitalWrite(pinBuzzer, LOW);
  digitalWrite(pinProximity, HIGH);

  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
}

void loop() {
  // Pembacaan data sensor proximity
  isObstacle = digitalRead(pinProximity);

  if (isObstacle == HIGH) {
    // tidak ada halangan
    digitalWrite(pinLED, LOW);    // LED mati
    digitalWrite(pinBuzzer, LOW); // Buzzer diam
    
    // Cetak ke Serial Monitor
    Serial.println("Sensor tidak mendeteksi adanya benda penghalang");
    
    // Cetak ke LCD I2C    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pantau ...");
    
    lcd.setCursor(0, 1);    
    lcd.print("Aman clear");
  }
  else if (isObstacle == LOW) 
  {
    // ditemui halangan
    digitalWrite(pinLED, HIGH);    // LED hidup
    digitalWrite(pinBuzzer, HIGH); // Buzzer hidup
    
    // Cetak ke Serial Monitor
    Serial.println("Sensor mendeteksi adanya benda penghalang");    

    // Cetak ke LCD I2C    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pantau ...");
    
    lcd.setCursor(0, 1);    
    lcd.print("Awas terhalang");
  }
  delay(500);
}
