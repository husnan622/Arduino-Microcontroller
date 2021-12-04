#include <JC_Button.h>
#include <Rotary.h>

#define pinCLK 2
#define pinDT 3
#define pinSW 4

Button tombolSW(pinSW);
Rotary r = Rotary(pinCLK, pinDT);
uint8_t urutan = 1;

void setup() {  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(5, HIGH);
  tombolSW.begin();
}

void loop() {
  // Rotary encoder sebagai saklar push button
  tombolSW.read();
  if (tombolSW.wasReleased())
  {
    // Matikan semua LED
    for (int i = 5; i <= 10; i++) {
      digitalWrite(i, LOW);      
    }
    delay(2000);
    
    // Hidupkan semua LED dari kiri ke kanan
    for (int i = 5; i <= 10; i++) {
      digitalWrite(i, HIGH);
      delay(200);
    }
    
    delay(1000); // tunda 1 detik
    
    // Matikan semua LED dari kanan ke kiri
    for (int i = 10; i >= 5; i--) {
      digitalWrite(i, LOW);
      delay(200);
    }
    delay(1000); // tunda 2 detik

    // Hanya menghidupkan LED pertama
    digitalWrite(5, HIGH);
    urutan = 1;
  }

  unsigned char result = r.process();
  if (result == DIR_CW) {
    // putar kanan
    if (urutan <= 6) {            
      urutan++; // tambahkan urutan dengan 1
    } else {
      urutan = 1; // kembalikan ke urutan 1
    }
  } else if (result == DIR_CCW) {
    // putar kiri (DIR_CCW)
    if (urutan >= 1) {            
      urutan--; // kurangi urutan dengan 1
    } else {
      urutan = 6; // kembalika ke urutan 6
    }
  }
  LEDHidup(urutan); // panggil fungsi LEDHidup
}

void LEDHidup(uint8_t item) {
  for (int i = 5; i <= 10; i++) {
    digitalWrite(i, LOW); // matikan semua LED
  }
  // item ditambah 4 karena pin LED dimulai dari 5
  // hidupkan LED ini saja
  digitalWrite(item + 4, HIGH); 
}

