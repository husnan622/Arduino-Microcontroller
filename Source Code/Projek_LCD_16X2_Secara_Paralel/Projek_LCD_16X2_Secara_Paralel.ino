#include <LiquidCrystal.h>

// Membuat objek LCD. Parameter: (rs, enable, d4, d5, d6, d7)
const int rs = 12, enable = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);

void setup() {
  // Inisialisasi interface ke layar LC dan menentukan dimensi
  // lebar dan tinggi dari layar
  lcd.begin(16, 2);
}

void loop() {
  lcd.print("Arduino"); // Cetak "Arduino" pada LCD
  delay(3000);          // Tunda 3 detik
  lcd.setCursor(2,1);   // Atur lokasi teks dimulai dari kolom 2 baris 1
  lcd.print("LCD Tutorial"); // Cetak "LCD Tutorial" pada LCD
  delay(3000);          // Tunda 3 detik
  lcd.clear();          // Membersihkan layar
  lcd.blink();          // Kedip kursor LCD
  delay(4000);          // Tunda 4 detik
  lcd.setCursor(7,1);   // Atur lokasi teks dimulai dari kolom 4 baris 1
  delay(3000);          // Tunda 3 detik
  lcd.noBlink();        // Mematikan kedip kursor LCD
  lcd.cursor();         // Menampilkan underscore/garis bawah pada posisi karakter berikutnya
  delay(4000);          // Delay 4 detik
  lcd.noCursor();       // Menyembunyikan kursor LCD
  lcd.clear();          // Membersihkan layar LCD
}
