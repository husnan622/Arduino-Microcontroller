#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define pinLedMerah 8
#define pinLedOrange 7
#define pinLedKuning 6
#define pinLedHijau 5
#define RX 10 // pin 10 arduino
#define TX 11 // pin 11 arduino

//  SIM800L  >>> ARDUINO UNO
//  ------------------------
//  GND      >>> GND
//  TX       >>> RX pin 10
//  RX (voltage divier) >>> TX pin 11
//  RST      >>> pin 9
//  ------------------------
SoftwareSerial GSMSerial(RX, TX);

// Set alamat LCD ke 0x27 untuk ukuran tampilan 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

char incomingByte;
String incomingData;
bool atCommand = true;

int index = 0;
String number = "";
String message = "";

void setup()
{
  Serial.begin(9600);
  GSMSerial.begin(9600);

  lcd.init(); // Inisialisasi LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MODEM GSM SIM800");
  lcd.setCursor(0, 1);
  lcd.print("  KONTROL SMS   ");
  
  pinMode(pinLedMerah, OUTPUT);
  pinMode(pinLedOrange, OUTPUT);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedHijau, OUTPUT);

  //Cek apakah jaringan GSM telah terhubung dengan SIM800L
  while (!GSMSerial.available()) {
    GSMSerial.println("AT");
    delay(1000);
    Serial.println("Connecting....");
  }

  Serial.println("Connected..");
  //Set SMS Text Mode
  GSMSerial.println("AT+CMGF=1");
  delay(1000);

  //Prosedur bagaimana menerima pesan dari jaringan
  GSMSerial.println("AT+CNMI=1,2,0,0,0");
  delay(1000);

  //Baca pesan yang belum terbaca
  GSMSerial.println("AT+CMGL=\"REC UNREAD\"");
  Serial.println("Ready to received Commands..");
}

void loop()
{
  if (GSMSerial.available()) {
    delay(100);

    // Serial buffer
    while (GSMSerial.available()) {
      incomingByte = GSMSerial.read();
      incomingData += incomingByte;
    }

    delay(10);
    if (atCommand == false) {
      receivedMessage(incomingData);
    } else {
      atCommand = false;
    }

    //Hapus pesan untuk menghemat memori
    if (incomingData.indexOf("OK") == -1) {
      GSMSerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      atCommand = true;
    }

    incomingData = "";
  }
}

void receivedMessage(String inputString) {

  //Mendapatkan nomer pengirim pesan
  index = inputString.indexOf('"') + 1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0, index);
  Serial.println("Number: " + number);

  //Mendapatkan pesan yang diterima
  index = inputString.indexOf("\n") + 1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);

  // Menjadikan uppercase pesan yang diterima
  message.toUpperCase();

  //Menjadikan LED ON atau OFF
  if (message.indexOf("MON") > -1) {
    //Jika ditemui pesan string = MON, LED merah ON
    digitalWrite(pinLedMerah, HIGH);
    TampilLCD("Perintah:", "LED Merah Hidup");
    Serial.println("Command: LED Merah Hidup.");
  } else if (message.indexOf("OON") > -1) {
    //Jika ditemui pesan string = OON, LED orange ON
    digitalWrite(pinLedOrange, HIGH);
    TampilLCD("Perintah:", "LED Orange Hidup");
    Serial.println("Command: LED Orange Hidup.");
  } else if (message.indexOf("KON") > -1) {
    //Jika ditemui pesan string = KON, LED kuning ON
    digitalWrite(pinLedKuning, HIGH);
    TampilLCD("Perintah:", "LED Kuning Hidup");
    Serial.println("Command: LED Kuning Hidup.");
  } else if (message.indexOf("HON") > -1) {
    //Jika ditemui pesan string = HON, LED hijau ON
    digitalWrite(pinLedHijau, HIGH);
    TampilLCD("Perintah:", "LED Hijau Hidup");
    Serial.println("Command: LED Hijau Hidup.");
  } if (message.indexOf("MOFF") > -1) {
    //Jika ditemui pesan string = MOFF, LED merah OFF
    digitalWrite(pinLedMerah, LOW);
    TampilLCD("Perintah:", "LED Merah Mati");
    Serial.println("Command: LED Merah Mati.");
  } else if (message.indexOf("OOFF") > -1) {
    //Jika ditemui pesan string = OOFF, LED orange OFF
    digitalWrite(pinLedOrange, LOW);
    TampilLCD("Perintah:", "LED Orange Mati");
    Serial.println("Command: LED Orange Mati.");
  } else if (message.indexOf("KOFF") > -1) {
    //Jika ditemui pesan string = KOFF, LED kuning OFF
    digitalWrite(pinLedKuning, LOW);
    TampilLCD("Perintah:", "LED Kuning Mati");
    Serial.println("Command: LED Kuning Mati.");
  } else if (message.indexOf("HOFF") > -1) {
    //Jika ditemui pesan string = HOFF, LED hijau OFF
    digitalWrite(pinLedHijau, LOW);
    TampilLCD("Perintah:", "LED Hijau Mati");
    Serial.println("Command: LED Hijau Mati.");
  }
  delay(50);
}

void TampilLCD(String Baris1, String Baris2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMS:" + Baris1);
  lcd.setCursor(0, 1);
  lcd.print(Baris2);
}
