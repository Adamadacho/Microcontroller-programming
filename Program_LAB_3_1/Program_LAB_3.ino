#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

#define LEDYellow 4
#define LEDRed 3
#define LEDBlue 2

char odebraneDane;

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
  }

  // Sterowanie diodami
  if (odebraneDane == '1') {
    digitalWrite(LEDYellow, HIGH);
  } else if (odebraneDane == '2') {
    digitalWrite(LEDYellow, LOW);
  }

  if (odebraneDane == '3') {
    digitalWrite(LEDRed, HIGH);
  } else if (odebraneDane == '4') {
    digitalWrite(LEDRed, LOW);
  }

  if (odebraneDane == '5') {
    digitalWrite(LEDBlue, HIGH);
  } else if (odebraneDane == '6') {
    digitalWrite(LEDBlue, LOW);
  }
}
