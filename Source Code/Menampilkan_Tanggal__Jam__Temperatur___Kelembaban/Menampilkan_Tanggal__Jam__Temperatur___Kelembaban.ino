#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ds3231.h>

#define pinDHT 3
#define jenisDHT DHT11

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

DHT dht(pinDHT, jenisDHT);

void setup() {
  Serial.begin(9600);
  
  // Inisialisasi dengan alamat I2C 0x3D (resolusi 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  
  display.clearDisplay();
  
  dht.begin();
  
}

void loop() {
  delay(2000);

  // Pembacaan temperatur atau kelembaban membutuhkan waktu kurang lebih 250 mili detik
  // Sensor membaca mungkin bisa sampai 2 detik (sensor yang lambat)
  float h = dht.readHumidity();
  
  // Membaca temperatur dalam Celcius (default)
  float t = dht.readTemperature();
  
  // Membaca temperatur dalam Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Cek jika pembacaan gagal dan keluar seketika (untuk mencoba lagi)
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Pembacaan sensor DHT telah gagal!");
    return;
  }
  
  // Hitung index panas dalam Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  
  // Hitung index panas dalam Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Kelembaban: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatur: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
