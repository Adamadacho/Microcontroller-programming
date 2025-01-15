#include <VirtualWire.h> // Załącz bibliotekę VirtualWire

#define TRANSMIT_PIN 12 // Pin transmisji dla nadajnika

void setup() {
  vw_set_tx_pin(TRANSMIT_PIN); // Ustawienie pinu transmisji
  vw_setup(2000);             // Prędkość transmisji (2000 bps)
}

void loop() {
  const char *msg = "LIVE";   // Wiadomość "LIVE"
  vw_send((uint8_t *)msg, strlen(msg)); // Wyślij wiadomość
  vw_wait_tx();               // Poczekaj na zakończenie transmisji
  delay(1000);                // Wysyłaj co 1 sekundę
}
