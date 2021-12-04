#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pinHujanAnalog = A0;
int pinHujanDigital = 2;
boolean apakahHujan = false;

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
  B11111 };

void setup() {
  pinMode(pinHujanAnalog, INPUT);
  pinMode(pinHujanDigital, INPUT);

  lcd.init(); // Inisialisasi LCD
  lcd.createChar(0, kotak);
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print("Deteksi Hujan &");
  lcd.setCursor(0, 1);
  lcd.print("Level Hujan");
  delay(1000);
}

void loop() {
  //membaca input signal analog
  unsigned int nilaiPembacaanSensor = analogRead(pinHujanAnalog); 
  
  //membaca input signal digital, status HIGH atau LOW
  apakahHujan = !(digitalRead(pinHujanDigital)); 
  
  //mapping 1023 (kering) ke 0 dan 0 (level kebasahan) ke 100 persen
  byte persen = map(nilaiPembacaanSensor, 1023, 0, 0, 100); 

  //mapping 0-100% ke jumlah karakter 1-16
  byte progressBar = map(persen, 0, 100, 1, 16);  

  lcd.clear();
  lcd.setCursor(0, 0);
  if (apakahHujan) {    
    //sensor terkena air
    //prosentase kebasahan
    lcd.print("Hujan Level:" + String(persen) + "%"); 
    for (byte i = 0; i < progressBar - 1; i++)
    {
      //cetak custom character kotak
      lcd.setCursor(i, 1);
      lcd.write(0);      
    }
  } else {
    //sensor tidak terkena air
    lcd.print("Tidak Hujan");
  }
  delay(1000);
}
