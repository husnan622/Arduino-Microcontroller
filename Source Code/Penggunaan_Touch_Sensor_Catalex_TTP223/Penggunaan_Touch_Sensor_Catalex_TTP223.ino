#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TFTLCD.h>

#define pinLED 2
#define pinTouch 3
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinTouch, INPUT);
  digitalWrite(pinLED, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inisialisasi OLED 128x64 atau 0.96"

  display.clearDisplay(); // Bersihkan layar OLED
  display.setTextColor(BLACK, WHITE); // Background teks inverse
  display.setCursor(26, 14); // Posisi koordinat tulisan (x,y)
  display.println("SENTUH AKU!"); // Cetak tulisan
  display.display(); // buffer setting
  delay(3000); // tunda 3 detik
}

void loop() {
  int val = digitalRead(pinTouch);
  if (val == HIGH) {
    digitalWrite(pinLED, HIGH);
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(26, 5);    
    display.println("SENTUH AKU!");          
    display.setCursor(20, 15);
    display.println("--- LED HIDUP ---");
    display.display();
  } else {
    digitalWrite(pinLED, LOW);
    
    display.clearDisplay();    
    display.setTextColor(WHITE);
    display.setCursor(26, 5);
    display.println("SENTUH AKU!");    
    display.setCursor(26, 15);
    display.println("LED MATI");
    display.display();
  }
}
