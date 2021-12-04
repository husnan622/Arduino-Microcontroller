#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

// Set alamat LCD ke 0x27 untuk ukuran tampilan 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pinIR = 8; // Sensor Penerima IR - Pin Arduino no 8
int LED1 = 2, LED2 = 3, LED3 = 4, LED4 = 5, LED5 = 6, LED6 = 7;

IRrecv PenerimaIR(pinIR);
decode_results hasil;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);

  lcd.init(); // inisialisasi LCD
  lcd.backlight(); // aktifkan backlight dan siap tampilkan pesan
  lcd.setCursor(0, 0);
  lcd.print("Projek Remote");
  lcd.setCursor(0, 1);
  lcd.print("Tekan Tombol");

  // Mulai menerima signal
  PenerimaIR.enableIRIn();
}

void TampilLCD(String kode, String jenis) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kode " + kode);
  lcd.setCursor(0, 1);
  lcd.print(jenis);
}

void loop() {
  if (PenerimaIR.decode(&hasil)) {
    String KodeTombol = String(hasil.value);
    if (KodeTombol == "1303526340") {
      TampilLCD(KodeTombol, "Power");
      //matikan semua LED
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      digitalWrite(LED6, LOW);
    } else if (KodeTombol == "1303525830") {
      TampilLCD(KodeTombol, "Mute");
    } else if (KodeTombol == "1303511550") {
      TampilLCD(KodeTombol, "Volume Naik");
    } else if (KodeTombol == "1303554390") {
      TampilLCD(KodeTombol, "Play/Pause");
    } else if (KodeTombol == "1303544190") {
      TampilLCD(KodeTombol, "Volume Turun");
    } else if (KodeTombol == "1303540620") {
      TampilLCD(KodeTombol, "OK");
    } else if (KodeTombol == "1303532460") {
      TampilLCD(KodeTombol, "Panah Atas");
    } else if (KodeTombol == "1303530420") {
      TampilLCD(KodeTombol, "Panah Bawah");
    } else if (KodeTombol == "1303550310") {
      TampilLCD(KodeTombol, "Panah Kiri");
    } else if (KodeTombol == "1303544700") {
      TampilLCD(KodeTombol, "Panah Kanan");
    } else if (KodeTombol == "1303552860") {
      TampilLCD(KodeTombol, "Return");
    } else if (KodeTombol == "1303515630") {
      TampilLCD(KodeTombol, "Menu");
    } else if (KodeTombol == "1303527870") {
      TampilLCD(KodeTombol, "Home");
    } else if (KodeTombol == "1303529910") {
      TampilLCD(KodeTombol, "Angka 1");
      digitalWrite(LED1, HIGH);
    } else if (KodeTombol == "1303562550") {
      TampilLCD(KodeTombol, "Angka 2");
      //hidupkan dua LED
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
    } else if (KodeTombol == "1303524300") {
      TampilLCD(KodeTombol, "Angka 3");
      //hidupkan tiga LED
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
    } else if (KodeTombol == "1303540110") {
      TampilLCD(KodeTombol, "Angka 4");
      //hidupkan empat LED
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
    } else if (KodeTombol == "1303572750") {
      TampilLCD(KodeTombol, "Angka 5");
      //hidupkan lima LED
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
    } else if (KodeTombol == "1303516140") {
      TampilLCD(KodeTombol, "Angka 6");
      //hidupkan keenam LED
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
      digitalWrite(LED6, HIGH);
    } else if (KodeTombol == "1303531950") {
      TampilLCD(KodeTombol, "Angka 7");
    } else if (KodeTombol == "1303564590") {
      TampilLCD(KodeTombol, "Angka 8");
    } else if (KodeTombol == "1303520220") {
      TampilLCD(KodeTombol, "Angka 9");
    } else if (KodeTombol == "1303542660") {
      TampilLCD(KodeTombol, "Titik .");
    } else if (KodeTombol == "1303568670") {
      TampilLCD(KodeTombol, "Angka 0");
    } else if (KodeTombol == "1303575300") {
      TampilLCD(KodeTombol, "Back Space");
    }

    PenerimaIR.resume();
  }
  delay(100);
}
