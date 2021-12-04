#include <IRremote.h>

int pinIR = 2; // Sensor Penerima IR

IRrecv PenerimaIR(pinIR);
decode_results hasil;

void setup() {
  Serial.begin(9600);
  // Mulai menerima signal
  PenerimaIR.enableIRIn();
}

void loop() {
  if (PenerimaIR.decode(&hasil)){
    Serial.print("Kode = ");
    Serial.println(hasil.value); // Tampilkan kode alamat tombol
    PenerimaIR.resume();    
  }
  delay(100);
}
