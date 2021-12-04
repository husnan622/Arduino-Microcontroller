#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(7, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println();
  Serial.println("Initializing DFPlayer ...");
    
  if (!myDFPlayer.begin(mySoftwareSerial)) {  
    Serial.println("Unable to begin:");
    Serial.println("1. Cek ulang koneksi!");
    Serial.println("2. Masukkan microSD!");
    while(true);
  }
  Serial.println("DFPlayer Mini aktif.");
  
  myDFPlayer.volume(10);  //Set volume antara 0 sampai 30
  myDFPlayer.play(1);  //Play file mp3 pertama
}

void loop()
{
  static unsigned long timer = millis();
  
  if (millis() - timer > 3000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 setiap 3 detik.
  }
  
  if (myDFPlayer.available()) {
    //print pesan status dan error.
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); 
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println("Time Out!");
      break;
    case WrongStack:
      Serial.println("Stack Wrong!");
      break;
    case DFPlayerCardInserted:
      Serial.println("Card Inserted!");
      break;
    case DFPlayerCardRemoved:
      Serial.println("Card Removed!");
      break;
    case DFPlayerCardOnline:
      Serial.println("Card Online!");
      break;
    case DFPlayerPlayFinished:
      Serial.print("Number:");
      Serial.print(value);
      Serial.println(" Play Finished!");
      break;
    case DFPlayerError:
      Serial.print("DFPlayerError:");
      switch (value) {
        case Busy:
          Serial.println("Card not found");
          break;
        case Sleeping:
          Serial.println("Sleeping");
          break;
        case SerialWrongStack:
          Serial.println("Get Wrong Stack");
          break;
        case CheckSumNotMatch:
          Serial.println("Check Sum Not Match");
          break;
        case FileIndexOut:
          Serial.println("File Index Out of Bound");
          break;
        case FileMismatch:
          Serial.println("Cannot Find File");
          break;
        case Advertise:
          Serial.println("In Advertise");
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
