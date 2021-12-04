#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <LiquidCrystal_I2C.h>

#define pinAnalog A0 //pin ultrasonic
#define pinTrigger 9 // pin trigger HC-SR04
#define pinEcho 8 // pin echo HC-SR04

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
int distanceCm;

// Pembangkitan custom character, kunjungi https://maxpromer.github.io/LCD-Character-Creator/
byte kotak[] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  pinMode(pinAnalog, INPUT);
  
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("Menghitung Jarak");
  lcd.setCursor(0, 1);
  lcd.print("Dengan Ultrasonic ");
  
  pinMode(pinTrigger, OUTPUT); // set pin trigger sebagai output
  pinMode(pinEcho, INPUT); // set pin echo sebagai input

  Serial.println();
  Serial.println("Initializing DFPlayer ...");

  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1. Cek ulang koneksi!");
    Serial.println("2. Masukkan microSD!");
    while (true);
  }
  Serial.println("DFPlayer Mini aktif.");
}

void loop()
{
  //*******************
  // Menghitung jarak
  //*******************
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

  //*******************
  // Deteksi Gas
  //*******************
  unsigned int nilaiPembacaanSensor = analogRead(pinAnalog);

  //mapping 1023 (kering) ke 0 dan 0 (level kebasahan) ke 100 persen
  byte persen = map(nilaiPembacaanSensor, 0, 1023, 0, 100);

  //mapping 0-100% ke jumlah karakter 1-16
  byte progressBar = map(persen, 0, 100, 1, 16);

  //*******************
  // Play Audio
  //*******************
  //tampilkan jarak kurang dari 50cm
  if (distanceCm <= 50) {
    myDFPlayer.volume(20);  //Set volume antara 0 sampai 30
    myDFPlayer.play(1);  //Play file mp3 pertama
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Jarak: " + String(distanceCm) + " cm");
  } else if (persen >= 30) {
    myDFPlayer.volume(20);  //Set volume antara 0 sampai 30
    myDFPlayer.play(2);  //Play file mp3 pertama
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Polusi Level:" + String(persen) + "%");
    for (byte i = 0; i < progressBar - 1; i++)
    {
      //cetak custom character kotak
      lcd.setCursor(i, 1);
      lcd.write(0);
    }
  } else {
    // berhenti jika jarak lebih dari 50cm
    myDFPlayer.stop();
  }

  delay(1000);
}
