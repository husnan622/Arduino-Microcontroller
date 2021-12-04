#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266.h>
#include <SoftwareSerial.h>

#define port 16375  // port server
#define buff 128    // jumlah karakter diterima oleh esp8266
#define OLED_RESET 7
#define pinBuzzer 4 // pin speaker buzzer
#define pinLED1 5   //pin LED 1
#define pinLED2 6   //pin LED 2

Adafruit_SSD1306 display(OLED_RESET);

//Arduiono         ESP8266
//Pin 2 (RX) ----> Pin TX
//Pin 3 (TX) ----> Pin RX (gunakan resistor divider)
SoftwareSerial SerialESP(2, 3); // RX, TX
ESP8266 wifi(SerialESP);

char pesan[buff]; // buffer string diterima
int8_t kounting = 0;

void setup()
{
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(23, 12);
  display.println("PROJEK ESP8266");
  display.display();
  delay(5000);
  display.clearDisplay();

  TCPServer(); // Membangun TCP Server
}

void loop()
{
  uint8_t buffer[buff] = {0};
  uint8_t mux_id;
  uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 10000);

  if (len > 0)
  {
    display.clearDisplay();
    kounting = 0;
    for (uint8_t i = 0; i < sizeof(pesan); ++i)
    {
      // kosongkan semua karakter yang pernah tersimpan
      pesan[i] = (char)0;
    }

    for (uint8_t i = 0; i < len; i++)
    {
      // pindahkan karakter yang diterima ke variable pesan
      pesan[i] = (char)buffer[i];
    }

    // konversi dari karakter ke string
    String str(pesan);

    // proses jika string diterima tidak kosong
    if (str != "") {
      if (str == "LED1 ON") {
        // nyalakan LED 1 jika string = LED1 ON
        digitalWrite(pinLED1, HIGH);
      } else if (str == "LED2 ON") {
        // nyalakan LED 2 jika string = LED2 ON
        digitalWrite(pinLED2, HIGH);
      } else if (str == "LED1 OFF") {
        // matikan LED 1 jika string = LED1 OFF
        digitalWrite(pinLED1, LOW);
      } else if (str == "LED2 OFF") {
        // matikan LED 2 jika string = LED2 OFF
        digitalWrite(pinLED2, LOW);
      }
    }

    // aktifkan speaker buzzer jika string diterima
    tone(pinBuzzer, 200, 200);
    
    // tampilkan string ke layar OLED
    cetak(str);

    // putuskan koneksi dengan client
    wifi.releaseTCP(mux_id);
  }
}

void cetak(String str)
{
  // function mencetak string ke OLED
  // maksimal 4 baris
  if (kounting > 3)
  {
    kounting = 0;
    display.clearDisplay();
  }
  display.setCursor(0, kounting * 8);
  display.println(str);
  display.display();
  kounting++;
}

void TCPServer()
{
  // pengujian dan setup ESP8266
  (wifi.setOprToSoftAP()) ? cetak("Access Point ..... OK") : cetak("Access Point .. ERROR");
  (wifi.enableMUX()) ? cetak("Connection ....... OK") : cetak("Connection .... ERROR");
  (wifi.startTCPServer(port)) ? cetak("Server Start ..... OK") : cetak("Server Start .. ERROR");
  (wifi.setTCPServerTimeout(10)) ? cetak("Timeout 10 sec ... OK") : cetak("Timeout ....... ERROR");
}
