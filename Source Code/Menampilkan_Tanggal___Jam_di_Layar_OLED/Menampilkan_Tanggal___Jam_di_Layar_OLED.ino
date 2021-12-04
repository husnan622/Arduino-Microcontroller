#include <SPI.h>
#include <Wire.h>
#include <DS3231.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TFTLCD.h>
#include <Fonts/FreeSansBold18pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
DS3231 rtc(SDA, SCL);
//DS3231 rtc();

void setup() {
  rtc.begin();
  // Setting tanggal dilakukan hanya satu kali, disesuaikan dengan tanggal komputer
  // selanjutnya beri tanda remark "//" agar tidak diset ulang
  // Bila RTC DS3231 di isi battery maka tidak perlu set tanggal lagi
  // ------------------------
  // rtc.setDOW(MONDAY);     // Set Day-of-Week to SUNDAY
  // rtc.setTime(10, 17, 0);     // Set the time to 12:00:00 (24hr format)
  // rtc.setDate(17, 9, 2018);   // Set the date to June 6th, 2017
  //-------------------------
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inisialisasi OLED 128x64 atau 0.96"

  display.clearDisplay(); // Bersihkan layar OLED
  display.setTextColor(WHITE); // Atur warna tulisan putih
  display.setFont(&FreeSansBold18pt7b); // Ubah jenis foont, cek di folder C:\Program Files (x86)\Arduino\libraries\Adafruit-GFX-Library-master
  display.setCursor(0, 27); // Posisi koordinat tulisan (x,y)
  display.print("DS"); // Cetak tulisan 'DS'

  display.setFont(); // Kembalikan jenis font menjadi normal
  display.setCursor(75, 7); // Posisi koordinat tulisan (x,y)
  display.println("Hore"); // Cetak tulisan
  display.setCursor(56, 16); // Posisi koordinat tulisan (x,y)
  display.println("Aku Bisa !!");
  display.fillRect(53, 2, 73, 2, WHITE);
  display.fillRect(53, 26, 73, 2, WHITE);
  display.display(); // Terapkan konfigurasi OLED
  delay(4000);

  display.clearDisplay(); // Bersihkan layar OLED
  display.setFont(); // Kembalikan jenis font menjadi normal
  display.setTextColor(WHITE);
  display.setCursor(22, 14);
  display.println("PROJEK OLED");
  display.display();
  delay(5000);

  display.clearDisplay();
}

void loop() {
  tampilHari();
}

void tampilHari() {
  String jam, menit, detik;
  Time waktu = rtc.getTime();

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  if (waktu.hour < 10) {
    jam = "0" + String(waktu.hour);
  } else {
    jam = String(waktu.hour);
  }

  if (waktu.min < 10) {
    menit = "0" + String(waktu.min);
  } else {
    menit = String(waktu.min);
  }

  if (waktu.sec < 10) {
    detik = "0" + String(waktu.sec);
  } else {
    detik = String(waktu.sec);
  }

  display.print(jam + ":" + menit);
  display.setTextSize(1);
  display.setFont(&FreeSansBold18pt7b);
  display.setCursor(76, 28);
  display.print(detik);
  display.setFont();
  display.drawRect(70, 0, 51, 32, WHITE);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.print(rtc.getDOWStr());
  display.setCursor(0, 25);
  display.print(rtc.getDateStr());
  display.display();
}
