#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TTP229.h>

#define pinSCL 2 // Hubungkan pin SCL TTP229 ke pin 2 Arduino
#define pinSDO 3 // Hubungkan pin SDO TTP229 ke pin 3 Arduino

LiquidCrystal_I2C lcd(0x27, 16, 2);
TTP229 sensorTouch(pinSCL, pinSDO); // Instansiasi objek sensor
int old  = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinSCL, OUTPUT);
  pinMode(pinSDO, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Angka :");
}

void loop() {
  int Key = getkey();
  if (Key != 0 & Key != old)
  {
    Serial.print("TEKAN ---> ");
    Serial.println(Key);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Tombol Angka: " + String(Key));
  }
  old = Key;
}

byte getkey(void)
{
  byte cnt;
  byte num = 0;
  for (cnt = 1; cnt < 17; cnt++)
  {
    digitalWrite(pinSCL, LOW);
    if (digitalRead(pinSDO) == 0)
      num = cnt;
    digitalWrite(pinSCL, HIGH);
  }
  return num;
}

