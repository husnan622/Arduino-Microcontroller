#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define RX_Arduino 8
#define TX_Arduino 9
// GPS     ---  Arduino
// pin TX  -->  pin 8 (RX_Arduino)
// pin RX  <--  pin 9 (TX_Arduino)
SoftwareSerial UART_GPS(RX_Arduino, TX_Arduino);
TinyGPSPlus gps;

// Set alamat LCD ke 0x27 untuk ukuran tampilan 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  UART_GPS.begin(9600); //inisialisasi GPS

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PROJEK GPS");
  lcd.setCursor(0, 1);
  lcd.print("KOORDINAT BUMI");
  //delay(3000); // Tunda 3 detik
  //lcd.clear(); // Bersihkan layar
}

double lat_lama = 0;
double long_lama = 0;

void loop() {
  while (UART_GPS.available() > 0) {
    gps.encode(UART_GPS.read());
    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      // Tampilkan koordinat pada layar LCD saat terjadi perubahan koordinat saja.
      // Perbedaan koordinat diambil sampai pada 4 digit di belakang koma agar tidak terlalu flicker pada LCD
      if (String(lat_lama, 4) != String(latitude, 4) || String(long_lama, 4) != String(longitude, 4)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LINT.: " + String(latitude, 6));
        lcd.setCursor(0, 1);
        lcd.print("BUJUR: " + String(longitude, 6));

        // Menampilkan koordinat pada google map. Copy paste ke browser
        String link = "http://www.google.com/maps/place/" + String(latitude, 6) + "," + String(longitude, 6) ;
        Serial.print("Link Google Maps : ");
        Serial.println(link);

        lat_lama = latitude;
        long_lama = longitude;
      }

      // Serial monitor tetap ditampilkan sampai 6 digit dibelakang koma sehingga terus berubah karena lebih presisi
      Serial.print("Jumlah Satellite : ");
      Serial.println(gps.satellites.value());

      Serial.print("Lintang : ");
      Serial.println(latitude, 6);

      Serial.print("Bujur : ");
      Serial.println(longitude, 6);

      Serial.print("Kecepatan MPH : ");
      Serial.println(gps.speed.mph());

      Serial.print("Ketinggian : ");
      Serial.println(gps.altitude.feet());

      Serial.println("");
    }
  }
}
