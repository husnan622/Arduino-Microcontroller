#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLED 4
#define pinKran 3
#define pinDigitalKelembabanD0 2 // sesuaikan dengan board komparator
#define pinAnalogKelembabanA0 A0 // sesuaikan dengan board komparator

// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);
boolean apakahLembab = false;

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
  pinMode(pinLED, OUTPUT);
  pinMode(pinKran, OUTPUT);
  pinMode(pinDigitalKelembabanD0, INPUT);
  pinMode(pinAnalogKelembabanA0, INPUT);

  lcd.init(); // Inisialisasi LCD
  lcd.createChar(0, kotak);
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print(" Smart Farming ");
  lcd.setCursor(0, 1);
  lcd.print("  Kelembaban");
  delay(3000);
}

void loop() {
  //membaca input signal analog
  unsigned int nilaiPembacaanSensor = analogRead(pinAnalogKelembabanA0);

  //membaca input signal digital, status HIGH atau LOW
  apakahLembab = !(digitalRead(pinAnalogKelembabanA0));

  //mapping 1023 (kering) ke 0 dan 0 (lembab) ke 100 persen
  byte persen = map(nilaiPembacaanSensor, 1023, 0, 0, 100);

  //mapping 0-100% ke jumlah karakter 1-16
  byte progressBar = map(persen, 0, 100, 1, 16);

  lcd.clear();
  lcd.setCursor(0, 0);
  if (apakahLembab) {
    //LED mati ketika tanah lembab
    digitalWrite(pinLED, LOW);

    //sensor terkena air
    //prosentase kelembaban
    lcd.print("Kelembaban:" + String(persen) + "%");
    for (byte i = 0; i < progressBar - 1; i++)
    {
      //cetak custom character kotak
      lcd.setCursor(i, 1);
      lcd.write(0);
    }

    //Tutup kran elektrik (valve solenoid)
    //Ketika tingkat kelembaban lebih dari sama dengan 60%
    if (persen >= 60) {
      digitalWrite(pinKran, LOW);
      delay(1000); //tunda 1 detik
    }
  } else {
    //LED hidup ketika tanah kering
    digitalWrite(pinLED, HIGH);

    //sensor tidak terkena air
    lcd.print("Tanah Kering");

    if (persen < 60) {
      //Buka kran elektrik (valve solenoid)
      //Ketika tingkat kelembaban kurang dari 60%
      digitalWrite(pinLED, HIGH);
      delay(1000); //tunda 1 detik
    }
  }
  delay(1000);
}
