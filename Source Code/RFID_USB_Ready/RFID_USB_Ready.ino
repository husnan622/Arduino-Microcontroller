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

String str = "";

void setup() {
  pinMode(pinLEDMerah, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);

  Serial.begin(9600);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.init(); // inisialisasi LCD
  lcd.backlight(); // aktifkan backlight dan siap tampilkan pesan
  lcd.setCursor(0, 0);
  lcd.print("Projek RFID");
  lcd.setCursor(0, 1);
  lcd.print("MIFARE");
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

  if (content != "" && str != content)
  {
    String hexrev = "";
    char pesanhex[8];
    String uid_send = "";
    char rfid[10];

    hexrev = content.substring(6, 8) + content.substring(4, 6) + content.substring(2, 4) + content.substring(0, 2);
    hexrev.toCharArray(pesanhex, hexrev.length() + 1);
    uid_send = String(hex2int(pesanhex));
    Serial.println("UID HEX ASLI : " + content);
    Serial.println("UID HEX REV : " + hexrev);
    Serial.println("UID DECIMAL : " + uid_send);
    Serial.println();
    uid_send.toCharArray(rfid, uid_send.length() + 1);
    str = content;
  }
}

uint32_t hex2int(char *hex)
{
  uint32_t val = 0;
  while (*hex) {
    char byte = *hex++;
    if (byte >= '0' && byte <= '9') byte = byte - '0';
    else if (byte >= 'a' && byte <= 'f') byte = byte - 'a' + 10;
    else if (byte >= 'A' && byte <= 'F') byte = byte - 'A' + 10;
    val = (val << 4) | (byte & 0xF);
  }
  return val;
}
