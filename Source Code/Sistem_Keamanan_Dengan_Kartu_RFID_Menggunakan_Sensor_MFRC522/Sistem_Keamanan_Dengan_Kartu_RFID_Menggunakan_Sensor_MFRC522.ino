#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLEDMerah 2
#define pinLEDHijau 3
#define pinBuzzer 4
#define pinReset 9   // Reset rfid
#define pinSS 10   // SS/SDA rfid

// Set alamat LCD ke 0x27 untuk ukuran tampilan 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(pinSS, pinReset);
String PasswordBenar[] = {"84206dcf", "Password2", "Password3"};

void setup() {
  pinMode(pinLEDMerah, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);

  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.init(); // inisialisasi LCD
  lcd.backlight(); // aktifkan backlight dan siap tampilkan pesan
  lcd.setCursor(0, 0);
  lcd.print("    Masukkan    ");
  lcd.setCursor(0, 1);
  lcd.print("    Password    ");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() )
  {
    delay(50);
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  if (content != "")
  {
    //cek pembacaan TAG ID di serial monitor
    //kemudian catat sebagai password
    Serial.println("TAG ID : " + content);

    boolean statusPassword = false;
    // Cek keabsahan password
    for (int i = 0; i < sizeof(PasswordBenar) - 1; i++) {
      if (PasswordBenar[i] == content)
      {
        //jika kartu RFID benar TAG 84206dcf
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("    Selamat     ");
        lcd.setCursor(0, 1);
        lcd.print(" Password Benar ");
        digitalWrite(pinLEDHijau, HIGH);
        digitalWrite(pinLEDMerah, LOW);

        //ganti status password menjadi true
        statusPassword = true;
        // jika password ditemukan maka hentikan perulangan
        // tidak perlu meneruskan pencarian password
        break;
      } else
      {
        statusPassword = false;
      }
    }

    // beri pesan kesalahan sekali saja
    // sehingga harus dikeluarkan dari loop
    if (statusPassword == false) {
      //jika kartu RFID selain TAG 84206dcf
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Password Anda ");
      lcd.setCursor(0, 1);
      lcd.print("   SALAH !!!");
      digitalWrite(pinLEDHijau, LOW);
      digitalWrite(pinLEDMerah, HIGH);
      tone(pinBuzzer, 200, 300);
    }

    //tunda 4 detik
    delay(4000);

    //beri pesan baru
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempelkan Kartu");
    lcd.setCursor(0, 1);
    lcd.print("   RFID Anda   ");

    //matikan semua LED
    digitalWrite(pinLEDMerah, LOW);
    digitalWrite(pinLEDHijau, LOW);
  }
}
