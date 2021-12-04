int vib_pin = 9; // pin sensor vibration
int led_pin = 8; // pin LED

void setup() {  
  pinMode(vib_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {  
  int val = digitalRead(vib_pin);  
  if (val == 1)
  {
    // Jika terdeteksi getaran
    digitalWrite(led_pin, HIGH);
    delay(1000);
    digitalWrite(led_pin, LOW);
    delay(1000);
  }
  else
    digitalWrite(led_pin, LOW);  
}
