int ledPinMerah = 8; // Pinout 8 ke kaki LED positif LED Merah
int ledPinKuning = 9; // Pinout 9 ke kaki LED positif LED Kuning
int ledPinHijau = 10; // Pinout 10 ke kaki LED positif LED Hijau

int buttonPinMerah = 11; // Pushbutton Merah dihubungkan dengan pin 11
int buttonPinKuning = 12; // Pushbutton Kuning dihubungkan dengan pin 12
int buttonPinHijau = 13; // Pushbutton Hijau dihubungkan dengan pin 13

void setup() {
  pinMode(ledPinMerah, OUTPUT);
  pinMode(ledPinKuning, OUTPUT);
  pinMode(ledPinHijau, OUTPUT);

  digitalWrite(ledPinMerah, LOW);
  digitalWrite(ledPinKuning, LOW);
  digitalWrite(ledPinHijau, LOW);

  pinMode(buttonPinMerah, INPUT);
  pinMode(buttonPinKuning, INPUT);
  pinMode(buttonPinHijau, INPUT);
}

void loop() {
  // Jika saklar push button Merah ditekan  
  if (digitalRead(buttonPinMerah) == HIGH) {
    digitalWrite(ledPinMerah, HIGH); // LED Merah hidup
  } else {
    digitalWrite(ledPinMerah, LOW); // LED Merah mati
  }

  // Jika saklar push button Kuning ditekan
  if (digitalRead(buttonPinKuning) == HIGH) {
    digitalWrite(ledPinKuning, HIGH); // LED Kuning hidup
  } else {
    digitalWrite(ledPinKuning, LOW); // LED Kuning mati
  }

  // Jika saklar push button Hijau ditekan
  if (digitalRead(buttonPinHijau) == HIGH) {
    digitalWrite(ledPinHijau, HIGH); // LED Hijau hidup
  } else {
    digitalWrite(ledPinHijau, LOW); // LED Hijau mati
  }
}
