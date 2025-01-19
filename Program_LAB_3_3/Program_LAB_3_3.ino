#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

#define LEDYellow 3
#define LEDRed 5
#define LEDBlue 6

char odebraneDane;
int moc = 0;  // Jasność (domyślnie 0)

void setup() {
  Serial.begin(9600);          // Komunikacja z monitorem szeregowym
  bluetooth.begin(9600);       // Komunikacja z HC-06
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
  Serial.println("Moduł Bluetooth gotowy!");
}

void loop() {
  if (bluetooth.available() > 0) {  // Sprawdź, czy dostępne są dane z Bluetooth
    odebraneDane = bluetooth.read(); // Odczytaj dane z HC-06
    Serial.print("Odebrane dane: "); 
    Serial.println(odebraneDane); // Wyświetl odebrane dane w monitorze szeregowym

    // Obsługa sterowania jasnością
    if (odebraneDane >= '0' && odebraneDane <= '9') {
      moc = (odebraneDane - '0') * 25;  // Konwersja '0'-'9' na jasność (0, 25, ..., 255)
      Serial.print("Ustawiona moc: ");
      Serial.println(moc);
    }
  }

  // Sterowanie diodami
  if (odebraneDane == 'Y') {  // Sterowanie żółtą diodą
    analogWrite(LEDYellow, moc);
    Serial.println("Sterowanie żółtą diodą");
  }

  if (odebraneDane == 'R') {  // Sterowanie czerwoną diodą
    analogWrite(LEDRed, moc);
    Serial.println("Sterowanie czerwoną diodą");
  }

  if (odebraneDane == 'B') {  // Sterowanie niebieską diodą
    analogWrite(LEDBlue, moc);
    Serial.println("Sterowanie niebieską diodą");
  }
}
