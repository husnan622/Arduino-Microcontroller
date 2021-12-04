#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define lebarPassword 7

// Inisialisasi library
// Atur alamat LC pada 0x27 untuk tampilan LCD 16 karakter 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

char Data[lebarPassword]; // 6 is the number of chars it can hold + the null char = 7
char Master[lebarPassword] = "123456"; // Password (bisa diganti dengan yang lain)
byte data_count = 0, master_count = 0;
bool Password_Benar;

int pinSolenoid = 11; // Solenioid dihubungkan dengan pin 11 Arduino
int pinBuzzer = 13;   // Buzzer dihubungkan dengan pin 13 Arduino

const byte ROWS = 4;
const byte COLS = 4;

// Keypad ukuran 4X4
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Menghubugkan dengan Pin Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Inisialisasi keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(pinSolenoid, OUTPUT);
  digitalWrite(pinSolenoid, LOW); // Solenoid normal mengunci
  pinMode(pinBuzzer, OUTPUT);  
  lcd.init();     // Inisialisasi LCD
  lcd.backlight(); // Menghidupkan backlight
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Password :"); // tampilkan di LCD

  char customKey = customKeypad.getKey(); // mendapatkan nilai tombol keypad
  if (customKey) // Memastikan jika tombol keypad ditekan
  {
    Data[data_count] = customKey; // Menyimpan karakter ke array
    lcd.setCursor(data_count, 1); // Menggerakkan kursor untuk menunjukkan penambahan karakter baru
    lcd.print(Data[data_count]);  // Mencetak karakter
    data_count++;                 // Penambahan data array dengan 1
  }

  // Jika index array sama dengan jumlah karakter yang diharapkan maka bandingkan dengan master
  if (data_count == lebarPassword - 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Password : ");

    // Bandingkan nilai keypad dengan password (6 digit ="123456")
    if (strcmp(Data, Master)) {
      // Jika password salah
      digitalWrite(pinSolenoid, LOW); // Solenoid normal mengunci      
      lcd.setCursor(0, 1);
      lcd.print("Password Salah"); // Pesan password salah ke LCD
      
      // Bunyikan buzzer jika salah
      tone(pinBuzzer, 1000); // Kirim siganal suara 1KHz
      delay(1000);  
      noTone(pinBuzzer);
      delay(1000);
    }
    else {
      // Jika password salah
      digitalWrite(pinSolenoid, HIGH); // Solenoid membuka (menarik ujung solenoid ke dalam)      
      lcd.setCursor(0, 1);
      lcd.print("Password Benar"); // Pesan password benar ke LCD      
    }

    delay(3000);
    lcd.clear();
    clearData();
  }
}

void clearData()
{
  while (data_count != 0) {
    Data[data_count--] = 0; // Bersihkan array untuk password baru
  }
  return;
}
