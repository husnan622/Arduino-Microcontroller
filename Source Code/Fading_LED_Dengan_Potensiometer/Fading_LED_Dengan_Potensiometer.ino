const int LEDPin = 8;  // Kaki LED positif dihubungkan ke pin 8
const int POTPin = A0; // Kaki tengah potensiometer dihubungkan ke pin analog A0

int nilaiPotensiometer = 0;
int nilaiOutput = 0; // asumsi bahwa posisi potensio dimulai paling kiri

void setup() {
  // Inisialisasi komunikasi serial dengan kecepatan 9600 bps
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(POTPin, INPUT);
}

void loop() {
  // Mendapatkan nilai pembacaan potensiometer
  nilaiPotensiometer = analogRead(POTPin);

  // Mentransformasi atau memetakan nilai pembacaan potensiometer
  // antara 0-1023 (nilai analog) menjadi antara 0-255
  // dengan menggunakan fungsi map arduino
  nilaiOutput = map(nilaiPotensiometer, 0, 1023, 0, 255);

  // Mengatur tingkat kecerahan LED antara 0-255
  analogWrite(LEDPin, nilaiOutput);    

  // Cetak hasilnya ke Serial Monitor
  Serial.print("\nNilai analog potensiometer (0-1023) = ");
  Serial.print(nilaiPotensiometer);
  Serial.print("\nOutput tingkat kecerahan (0-255)= ");
  Serial.print(nilaiOutput);

  // Tunda 2ms setiap kali ada pergesaran nilai potenstiometer
  delay(10);
}
