#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinAnalog A0
#define pinLED 3
#define pinBuzzer 4

// Inisialisasi library
// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pembangkitan custom character, kunjungi https://maxpromer.github.io/LCD-Character-Creator/
byte kotak[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};


void setup() {
  pinMode(pinAnalog, INPUT);  
  pinMode(pinLED, OUTPUT);  

  lcd.init(); // Inisialisasi LCD
  lcd.createChar(0, kotak);
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("     Deteksi    ");
  lcd.setCursor(0, 1);
  lcd.print("Asap LPG Alkohol");
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  //membaca input signal analog
  unsigned int nilaiPembacaanSensor = analogRead(pinAnalog);

  //mapping 1023 (kering) ke 0 dan 0 (level kebasahan) ke 100 persen
  byte persen = map(nilaiPembacaanSensor, 0, 1023, 0, 100);

  //mapping 0-100% ke jumlah karakter 1-16
  byte progressBar = map(persen, 0, 100, 1, 16);

  Serial.println("Baca Analog: " + String(nilaiPembacaanSensor) + ", " + String(persen) + "%");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Polusi Level:" + String(persen) + "%");
  for (byte i = 0; i < progressBar - 1; i++)
  {
    //cetak custom character kotak
    lcd.setCursor(i, 1);
    lcd.write(0);
  }

  if (persen >= 30) {
    //jika kadar gas, asap, CO, LPG, Hidrogen lebih dari sama dengan 30%
    //maka indikator LED menyala dan terdengar speaker Buzzer
    digitalWrite(pinLED, HIGH);
    tone(pinBuzzer, 200, 200);
  } else {
    //jika kadar gas, asap, CO, LPG, Hidrogen kurang dari 30%
    //maka LED indikator mati dan speaker buzzer diam
    digitalWrite(pinLED, LOW);    
    noTone(pinBuzzer);
  }
  delay(2500);
}
