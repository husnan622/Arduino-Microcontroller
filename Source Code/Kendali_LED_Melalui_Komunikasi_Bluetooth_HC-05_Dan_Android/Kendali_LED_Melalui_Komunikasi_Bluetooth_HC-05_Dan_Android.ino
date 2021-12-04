#include <SoftwareSerial.h>

const int LEDMerah = 2;
const int LEDHijau = 3;
const int LEDKuning = 4;

// Bluetooth RX -> Arduino TX pin 5
// Bluetooth TX -> Arduino RX pin 6
SoftwareSerial Bluetooth(6, 5); // RX, TX

int state = 0;

void setup() {
  // Hardware Serial
  Serial.begin(9600);

  // Software Serial
  Bluetooth.begin(9600);

  // Semua LED Pin Mode sebagai Output
  pinMode(LEDMerah, OUTPUT);
  pinMode(LEDHijau, OUTPUT);
  pinMode(LEDKuning, OUTPUT);
}

void loop() {
  if (Bluetooth.available() > 0)
  {
    // Jika Serial Bluetooth menerima byte data dari serial port
    // Nilai state adalah angka tabel ascii contoh angka 65='A'
    state = Bluetooth.read();
    // Menampilkan byte data ke serial monitor
    Serial.println("State = " + state);

    if (state == 'R') {
      digitalWrite(LEDMerah, HIGH);      
      state = 0; // Kembalikan ke state=0
    } else if (state == 'G') {
      // Hidupkan LED merah
      digitalWrite(LEDHijau, HIGH);      
      state = 0; // Kembalikan ke state=0     
    } else if (state == 'Y') {
      // Hidupkan LED kuning
      digitalWrite(LEDKuning, HIGH);      
      state = 0; // Kembalikan ke state=0
    } else if (state == "A") {
      // Matikan semua LED
      digitalWrite(LEDMerah, LOW);
      digitalWrite(LEDHijau, LOW);
      digitalWrite(LEDKuning, LOW);      
      state = 0; // Kembalikan ke state=0
    }
  }
}
