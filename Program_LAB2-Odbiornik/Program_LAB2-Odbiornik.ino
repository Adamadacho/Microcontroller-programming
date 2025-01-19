#include <VirtualWire.h> // Załącz bibliotekę VirtualWire

#define LED_PIN 2        // Pin dla diody LED
#define RECEIVE_PIN 11   // Pin dla sygnału z odbiornika RF

void setup() {
  pinMode(LED_PIN, OUTPUT);    // Ustawienie pinu LED jako wyjście
  Serial.begin(9600);          // Inicjalizacja monitora portu szeregowego
  vw_set_rx_pin(RECEIVE_PIN);  // Ustawienie pinu odbioru danych
  vw_setup(2000);              // Ustawienie prędkości transmisji (2000 bps)
  vw_rx_start();               // Inicjalizacja odbiornika
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];   // Bufor na odebraną wiadomość
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Długość bufora

  if (vw_get_message(buf, &buflen)) { // Jeśli odebrano dane
    digitalWrite(LED_PIN, HIGH);      // Włącz diodę LED
    for (int i = 0; i < buflen; i++) {
      Serial.print(buf[i], HEX);      // Wyświetl dane w formacie HEX
      Serial.print(" ");
    }
    Serial.println();                 // Nowa linia
    delay(500);                       // Krótkie opóźnienie
  }
  digitalWrite(LED_PIN, LOW);         // Wyłącz diodę LED
}
