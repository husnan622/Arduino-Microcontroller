int pinRelay = 8; // Pin S Relay ke Pin 8 Arduino
int pinLED = 9;   // Pin LED Resistor ke Pin 9 Arduino
int pinLM35 = A0;  // pin LM35 ke Pin A0 Arduino (analog)

void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLM35, INPUT);
}

void loop() {
  int suhucelcius = getTemperatureCel(pinLM35);
  int suhufarenheit = celsius_to_fahrenheit(suhucelcius);

  // Menampilkan nilai sensor LM35
  Serial.println("Temperatur Celcius: " + String(suhucelcius) + " - " + "Farenheit: " + String(suhufarenheit));  
  delay(500);

  if (suhucelcius >= 34) {
    // Mengaktifkan relay ON dan menghidupkan kipas angin
    // jika temperatur lebih dari sama dengan 34 derajat celcius
    digitalWrite(pinLED, HIGH);
    digitalWrite(pinRelay, HIGH);
  } else {
    digitalWrite(pinLED, LOW);
    digitalWrite(pinRelay, LOW);
  }
}

int getTemperatureCel(int pin) {
  int val = analogRead(pin);
  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;
  return (cel);
}

int celsius_to_fahrenheit(float cel) {
  float farh = (cel * 9) / 5 + 32;
  return (farh);
}
