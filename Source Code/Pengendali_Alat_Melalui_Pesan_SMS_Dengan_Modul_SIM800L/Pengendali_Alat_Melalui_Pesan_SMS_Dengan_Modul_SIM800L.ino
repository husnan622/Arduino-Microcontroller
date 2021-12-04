//#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Sim800L.h>

#define pinLedMerah 8
#define pinLedOrange 7
#define pinLedKuning 6
#define pinLedHijau 5
#define RX 10 // pin 10 arduino
#define TX 11 // pin 11 arduino
#define RESET 9 // pin reset arduino

/*
  SIM800L  >>> ARDUINO UNO
  ------------------------
  GND      >>> GND
  TX       >>> RX pin 10
  RX (voltage divier) >>> TX pin 11
  RST      >>> pin 9
  ------------------------
  Alternatif
  Sim800L GSM; // Use default pinout
  Sim800L GSM(RX, TX, RESET);
  Sim800L GSM(RX, TX, RESET, LED);
*/
Sim800L GSM(RX, TX);

// Set alamat LCD ke 0x27 untuk ukuran tampilan 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

//String text;
//uint8_t index;

String textSms, numberSms;
uint8_t index;
bool error;

void setup() {
  pinMode(pinLedMerah, OUTPUT);
  pinMode(pinLedOrange, OUTPUT);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedHijau, OUTPUT);

  digitalWrite(pinLedMerah, LOW);
  digitalWrite(pinLedOrange, LOW);
  digitalWrite(pinLedKuning, LOW);
  digitalWrite(pinLedKuning, LOW);

  Serial.begin(9600);

  // Inisialisasi Modem GSM SIM800L
  GSM.begin(9600);
  //GSM.sendSms("085731311476", "Haloo testing kirim dari SIM800L");
  //index = 1;
  //GSM.reset();

  // Bersihkan memori dari sms
  //error = GSM.delAllSms();
  //GSM.sendSms("+6285731311476", "Haloo testing kirim dari SIM800L");
/*
  Serial.println("GET PRODUCT INFO: ");
  Serial.println(GSM.getProductInfo());

  Serial.println("GET OPERATORS LIST: ");
  Serial.println(GSM.getOperatorsList());

  Serial.println("GET OPERATOR: ");
  Serial.println(GSM.getOperator());

  Serial.println("NOMOR: ");
  Serial.println(GSM.getNumberSms(1));
*/
  lcd.init(); // Inisialisasi LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MODEM GSM SIM800");
  lcd.setCursor(0, 1);
  lcd.print("  KONTROL SMS   ");

  //lcd.clear(); // Bersihkan layar

  // Seting LCD, Tampilan Awal
  
  //delay(3000); // Tunda 3 detik
  error = GSM.sendSms("6285731311476", "test sms arduino");
}

void loop() {

  // Membaca SMS Terbaru

  textSms = GSM.readSms(index);
  if (textSms != "")  {
    Serial.println("SMS: " + textSms);    
/*
    Serial.println("GET PRODUCT INFO: ");
    Serial.println(GSM.getProductInfo());

    Serial.println("GET OPERATORS LIST: ");
    Serial.println(GSM.getOperatorsList());

    Serial.println("GET OPERATOR: ");
    Serial.println(GSM.getOperator());
*/
    Serial.println("NOMOR: " + GSM.getNumberSms(1));    
    
  }

  // Memastikan bahwa isi pesan SMS adalah bertujuan untuk program
  // Dimana penandanya adalah string "PRG"
  /*
    if (textSms.indexOf("PRG") != -1)
    {
    // Nomor pengirim
    numberSms = GSM.getNumberSms(1);
    Serial.println(numberSms);

    // pesan SMS dibuat huruf besar semua untuk mencegah kesalahan pembacaan
    textSms.toUpperCase();

    if (textSms.indexOf("LEDMERAH") != -1 && textSms.indexOf("ON") != -1) {
      Serial.println("LED MERAH MENYALA");
      digitalWrite(pinLedMerah, HIGH);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Merah Hidup");
    } else if (textSms.indexOf("LEDMERAH") != -1 && textSms.indexOf("OFF") != -1) {
      Serial.println("LED MERAH MATI");
      digitalWrite(pinLedMerah, LOW);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Merah Mati");
    } if (textSms.indexOf("LEDORANGE") != -1 && textSms.indexOf("ON") != -1) {
      Serial.println("LED ORANGE MENYALA");
      digitalWrite(pinLedOrange, HIGH);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Orange Hidup");
    } if (textSms.indexOf("LEDORANGE") != -1 && textSms.indexOf("OFF") != -1) {
      Serial.println("LED ORANGE MATI");
      digitalWrite(pinLedOrange, LOW);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Orange Mati");
    } if (textSms.indexOf("LEDKUNING") != -1 && textSms.indexOf("ON") != -1) {
      Serial.println("LED KUNING MENYALA");
      digitalWrite(pinLedKuning, HIGH);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Kuning Hidup");
    } if (textSms.indexOf("LEDKUNING") != -1 && textSms.indexOf("OFF") != -1) {
      Serial.println("LED KUNING MATI");
      digitalWrite(pinLedKuning, LOW);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Kuning Mati");
    } if (textSms.indexOf("LEDHIJAU") != -1 && textSms.indexOf("ON") != -1) {
      Serial.println("LED HIJAU MENYALA");
      digitalWrite(pinLedHijau, HIGH);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Hijau Hidup");
    } if (textSms.indexOf("LEDHIJAU") != -1 && textSms.indexOf("OFF") != -1) {
      Serial.println("LED HIJAU MATI");
      digitalWrite(pinLedHijau, LOW);
      TampilLCD("NO. SIM : ", numberSms);
      delay(2000);
      TampilLCD(textSms, "LED Hijau Mati");
    }
    } else {
    TampilLCD("NO. SIM : ", numberSms);
    delay(2000);
    TampilLCD(textSms, "Bukan SMS Kontrol");
    Serial.print("Bukan SMS Kontrol");
    }

    // Hapus semua SMS, sehingga yang terbaca selalu sms urutan pertama
    GSM.delAllSms();
  */
}

void TampilLCD(String Baris1, String Baris2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMS:" + Baris1);
  lcd.setCursor(0, 1);
  lcd.print(Baris2);
}
