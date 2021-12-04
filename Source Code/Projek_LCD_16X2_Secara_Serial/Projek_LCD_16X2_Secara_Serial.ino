#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// String yang dicetak ke LCD
char array1[] = " Horeee aku bisa Arduino Sekarang    ";
char array2[] = " Hello, World!                       ";
int tunda = 500; // waktu tunda

// Inisialisasi library
// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Inisialisasi LCD
  lcd.init();  

  // Menghidupkan backlight
  lcd.backlight();
}

void loop()
{
  lcd.setCursor(15, 0); // set kursor kolom 15, baris 0
  for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
  {
    lcd.scrollDisplayLeft(); //Scroll konten dari layar ke kiri.
    lcd.print(array1[positionCounter1]); // Cetak pesan ke LCD.
    delay(tunda); //tunda 500 microseconds
  }
  lcd.clear(); // Bersihkan layar LCD dan memposisikan kursor di kiri atas pojok.

  lcd.setCursor(15, 1); // set kursor di kolom 15, baris 1
  for (int positionCounter = 0; positionCounter < 26; positionCounter++)
  {
    lcd.scrollDisplayLeft(); //Scroll konten layar satu spasi ke kiri.
    lcd.print(array2[positionCounter]); // Cetak pesan ke LCD.
    delay(tunda); // Tunda 500 microseconds
  }
  lcd.clear(); // Bersihkan layar LCD dan memposisikan kursor di kiri atas pojok.
}
