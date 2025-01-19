#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

#define LEDGreen 2  // Dioda zielona (Blue w oryginalnym kodzie)
#define LEDYellow 4 // Dioda żółta
#define LEDRed 3    // Dioda czerwona

char odebraneDane;

void setup() {
  Serial.begin(9600);          // Komunikacja z monitorem szeregowym
  bluetooth.begin(9600);       // Komunikacja z HC-06
  pinMode(LEDGreen, OUTPUT);
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDRed, OUTPUT);

  // Wyłącz wszystkie diody na start
  digitalWrite(LEDGreen, LOW);
  digitalWrite(LEDYellow, LOW);
  digitalWrite(LEDRed, LOW);

  Serial.println("Bluetooth gotowy!");
}

void loop() {
  if (bluetooth.available() > 0) {  // Sprawdź, czy dostępne są dane z Bluetooth
    odebraneDane = bluetooth.read(); // Odczytaj dane z HC-06
    Serial.print("Odebrane dane: ");
    Serial.println(odebraneDane); // Wyświetl odebrane dane w monitorze szeregowym
  }

  // Obsługa diod na podstawie odebranych danych
  if (odebraneDane == '1') {
    zapalZielona(); // Zapal zieloną diodę
  } else if (odebraneDane == '2') {
    zapalCzerwonaZoltyPo3Sek(); // Zapal czerwoną, a po 3 sek żółtą
  } else if (odebraneDane == '3') {
    swiatlaSkrzyzowanie(); // Sekwencja świateł jak na skrzyżowaniu
  } else if (odebraneDane == '4') {
    wylaczWszystkie(); // Wyłącz wszystkie diody
  }
}

// Funkcja zapalająca zieloną diodę
void zapalZielona() {
  digitalWrite(LEDGreen, HIGH);  // Zapal zieloną
  digitalWrite(LEDYellow, LOW); // Wyłącz pozostałe
  digitalWrite(LEDRed, LOW);
}

// Funkcja zapalająca czerwoną diodę, a po 3 sekundach żółtą
void zapalCzerwonaZoltyPo3Sek() {
  digitalWrite(LEDRed, HIGH);   // Zapal czerwoną diodę
  digitalWrite(LEDGreen, LOW); // Wyłącz pozostałe
  digitalWrite(LEDYellow, LOW);
  delay(3000);                  // Czekaj 3 sekundy
  digitalWrite(LEDYellow, HIGH); // Zapal żółtą
}

// Funkcja symulująca światła na skrzyżowaniu
void swiatlaSkrzyzowanie() {
  // Zielone światło
  digitalWrite(LEDGreen, HIGH);
  digitalWrite(LEDYellow, LOW);
  digitalWrite(LEDRed, LOW);
  delay(3000); // Świeci 3 sekundy

  // Żółte światło
  digitalWrite(LEDGreen, LOW);
  digitalWrite(LEDYellow, HIGH);
  digitalWrite(LEDRed, LOW);
  delay(1000); // Świeci 1 sekundę

  // Czerwone światło
  digitalWrite(LEDGreen, LOW);
  digitalWrite(LEDYellow, LOW);
  digitalWrite(LEDRed, HIGH);
  delay(3000); // Świeci 3 sekundy
}

// Funkcja wyłączająca wszystkie diody
void wylaczWszystkie() {
  digitalWrite(LEDGreen, LOW);  // Wyłącz zieloną
  digitalWrite(LEDYellow, LOW); // Wyłącz żółtą
  digitalWrite(LEDRed, LOW);    // Wyłącz czerwoną
}
