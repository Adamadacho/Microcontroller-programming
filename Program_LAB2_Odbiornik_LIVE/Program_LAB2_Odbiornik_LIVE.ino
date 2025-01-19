#include <VirtualWire.h> // Załącz bibliotekę VirtualWire

#define LED_PIN 2         // Pin diody LED
#define RECEIVE_PIN 11    // Pin sygnału RF
unsigned long lastLiveBitTime = 0;  // Czas ostatniego Live bit
const unsigned long timeout = 3000; // Czas w ms do uznania utraty komunikacji

void setup() {
  pinMode(LED_PIN, OUTPUT);     // Ustawienie diody jako wyjście
  Serial.begin(9600);           // Uruchomienie monitora portu szeregowego
  vw_set_rx_pin(RECEIVE_PIN);   // Ustawienie pinu RF
  vw_setup(2000);               // Ustawienie prędkości transmisji
  vw_rx_start();                // Start odbiornika
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];    // Bufor na wiadomość
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Długość bufora

  if (vw_get_message(buf, &buflen)) { // Jeśli odebrano wiadomość
    digitalWrite(LED_PIN, HIGH);      // Włącz diodę LED
    String receivedMessage = "";
    for (int i = 0; i < buflen; i++) {
      receivedMessage += (char)buf[i]; // Konwersja do tekstu
    }
    Serial.println(receivedMessage);  // Wyświetlenie wiadomości

    if (receivedMessage == "Live bit") {
      lastLiveBitTime = millis();  // Aktualizacja czasu ostatniego Live bit
    }
    delay(500);  // Krótkie opóźnienie dla czytelności sygnału
  }
  
  // Sprawdzanie utraty komunikacji
  if (millis() - lastLiveBitTime > timeout) {
    digitalWrite(LED_PIN, LOW);  // Wyłącz diodę LED
    Serial.println("Brak komunikacji!");
  }
}
