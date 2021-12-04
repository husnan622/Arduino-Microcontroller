int pinRelay = 8; // Pin S Relay ke Pin 8 Arduino
int pinLED = 9;   // Pin LED Resistor ke Pin 9 Arduino
int pinLDR = A0;  // pin LDR ke Pin A0 Arduino (analog)
int nilaiLDR = 0; // Nilai Awal LDR dari intensitas cahaya yang diterima

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLDR, INPUT);
}

void loop() {
  nilaiLDR = analogRead(pinLDR);
  Serial.println("Pembacaan LDR: " + String(nilaiLDR));
  
  // Ambang nilaiLDR bisa diganti antara rentang 0-1024
  // tergantung tingkat kegelapan/pencahayaan yang diingingkan
  // sehingga memicu relay mengaktifkan lampu untuk menyala
  if (nilaiLDR <= 300) {
    digitalWrite(pinLED, HIGH);
    digitalWrite(pinRelay, HIGH);
    Serial.println("LDR Gelap, maka LED dan Lampu Menyala");
  } else {
    digitalWrite(pinLED, LOW);
    digitalWrite(pinRelay, LOW);
    Serial.println("---------------------");
  }
  delay(1000); // Proses ditunda setiap 1 detik
}
