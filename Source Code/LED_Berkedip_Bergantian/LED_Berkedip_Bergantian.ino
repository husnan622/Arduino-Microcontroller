int ledPinMerah = 8; // Pinout 8 ke kaki LED positif LED Merah
int ledPinKuning = 9; // Pinout 9 ke kaki LED positif LED Kuning
int ledPinHijau = 10; // Pinout 10 ke kaki LED positif LED Hijau

void setup() {
  pinMode(ledPinMerah, OUTPUT);
  pinMode(ledPinKuning, OUTPUT);
  pinMode(ledPinHijau, OUTPUT);
}

void loop() {
  digitalWrite(ledPinMerah, HIGH); // LED Merah Hidup
  digitalWrite(ledPinKuning, LOW); // LED Kuning Mati
  digitalWrite(ledPinHijau, LOW);  // LED Hijau Mati
  delay(2000); // Tunda 2000ms atau 2 detik

  digitalWrite(ledPinMerah, LOW); // LED Merah Mati
  digitalWrite(ledPinKuning, HIGH); // LED Kuning Hidup
  digitalWrite(ledPinHijau, LOW);  // LED Hijau Mati
  delay(2000); // Tunda 2000ms atau 2 detik

  digitalWrite(ledPinMerah, LOW); // LED Merah Mati
  digitalWrite(ledPinKuning, LOW); // LED Kuning Mati
  digitalWrite(ledPinHijau, HIGH);  // LED Hijau Hidup
  delay(2000); // Tunda 2000ms atau 2 detik
}
