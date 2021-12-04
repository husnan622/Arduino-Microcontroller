#include <UIPEthernet.h>
#include <LiquidCrystal_I2C.h>

#define LEDMerah 9 
#define LEDHijau 8
#define LEDKuning 7
#define port 16375 // port server
#define buff 50   // jumlah karakter yang diterima oleh ENC28J60

// ENC28J60       Arduino
// ----------------------
// VCC 3,3V       VCC 3,3V
// GND            GND
// SCK            13 divider
// SO/MISO        12
// ST/SI/MOSI     11 divider
// CS/SS          10 divider
// ----------------------
byte ip[4] = {192, 168, 4, 1}; // Sesuaikan dengan IP pada Komputer, misalnya 192.168.4.2
byte mac[6] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31}; // MAC address random
uint8_t myMASK[4] = {255, 255, 255, 0}; // IP Netmask
uint8_t myDNS[4] = {192, 168, 4, 1};    // IP DNS (jika perlu)
uint8_t myGW[4] = {192, 168, 4, 1};     // IP Gateway (jika perlu)
char pesan[buff];
EthernetServer server = EthernetServer(port);

// Atur alamat LCD pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(LEDMerah, OUTPUT);
  pinMode(LEDHijau, OUTPUT);
  pinMode(LEDKuning, OUTPUT);

  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
  lcd.setCursor(0, 0);
  lcd.print(" Komunikasi TCP");
  lcd.setCursor(0, 1);
  lcd.print("  LAN Ethernet");

  Ethernet.begin(mac, ip, myDNS, myGW, myMASK);
  server.begin();
}

void loop()
{
  size_t size;
  if (EthernetClient client = server.available())
  {
    if ((size = client.available()) > 0)
    {
      uint8_t* msg = (uint8_t*)malloc(size + 1);
      memset(msg, 0, size + 1);
      size = client.read(msg, size);
      for (uint8_t i = 0; i < sizeof(pesan); ++i)
      {
        pesan[i] = (char)0;
      }

      for (uint8_t i = 0; i < size; i++)
      {
        pesan[i] = (char)msg[i];
      }

      free(msg);

      String str(pesan);
      str.toUpperCase();
      if (str.indexOf("MERAHON") > -1) {
        // string "MERAHON" = led merah menyala
        digitalWrite(LEDMerah, HIGH);        
        TampilLCD("Data: " + str, "LED MERAH");
      } else if (str.indexOf("HIJAUON") > -1) {
        // string "HIJAUON" = led hijau menyala
        digitalWrite(LEDHijau, HIGH);
        TampilLCD("Data: " + str, "LED HIJAU");
      } else if (str.indexOf("KUNINGON") > -1) {
        // string "KUNINGON" = led kuning menyala
        digitalWrite(LEDKuning, HIGH);
        TampilLCD("Data: " + str, "LED KUNING");
      } else if (str.indexOf("MERAHOFF") > -1) {
        // string "MERAHOFF" = led merah mati
        digitalWrite(LEDMerah, LOW);
        lcd.clear();
      } else if (str.indexOf("HIJAUOFF") > -1) {
        // string "HIJAUOFF" = led hijau mati
        digitalWrite(LEDHijau, LOW);
        lcd.clear();
      } else if (str.indexOf("KUNINGOFF") > -1) {
        // string "KUNINGOFF" = led kuning mati
        digitalWrite(LEDKuning, LOW);
        lcd.clear();
      }

      // Koneksi TCP dengan Komputer diputus
      client.stop(); 
    }
  }
}

void TampilLCD(String Baris1, String Baris2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Baris1);
  lcd.setCursor(0, 1);
  lcd.print(Baris2);
}
