int pinMerah= 8;   // Pin Led Merah dari resistor
int pinHijau = 9;  // Pin Led Hijau dari resistor
int pinBiru = 10;  // Pin Led Biru dari resistor

void setup() {
  pinMode(pinMerah, OUTPUT);
  pinMode(pinHijau, OUTPUT);
  pinMode(pinBiru, OUTPUT);
}

void loop() {
  aturWarna(255, 0, 0); // Warna Merah
  delay(1000);
  aturWarna(0, 255, 0); // Warna Hijau
  delay(1000);
  aturWarna(0, 0, 255); // Warna Biru
  delay(1000);
  aturWarna(255, 255, 255); // Warna Putih
  delay(1000);
  aturWarna(170, 0, 255); // Warna Ungu
  delay(1000);
}

void aturWarna(int nilaiMerah, int nilaiHijau, int nilaiBiru) {
  analogWrite(pinMerah, nilaiMerah);
  analogWrite(pinHijau, nilaiHijau);
  analogWrite(pinBiru, nilaiBiru);
}
