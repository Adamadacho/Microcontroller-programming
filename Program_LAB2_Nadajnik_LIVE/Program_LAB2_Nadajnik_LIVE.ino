#include <VirtualWire.h> // Załącz bibliotekę VirtualWire
#define LED_PIN 5         // Pin diody LED
#define OK_PIN 3          // Pin przycisku
#define TRANSMIT_PIN 6    // Pin sygnału RF

unsigned long lastSendTime = 0;  // Zmienna do śledzenia czasu
const unsigned long interval = 1000; // Czas w ms między wysyłaniem Live bit

void setup() {
  pinMode(OK_PIN, INPUT_PULLUP);  // Ustawienie przycisku jako wejście
  pinMode(LED_PIN, OUTPUT);       // Ustawienie diody jako wyjście
  vw_set_tx_pin(TRANSMIT_PIN);    // Ustawienie pinu RF
  vw_setup(2000);                 // Ustawienie prędkości transmisji
  digitalWrite(LED_PIN, HIGH);    // Wyłącz diodę na start
}

void loop() {
  unsigned long currentTime = millis(); // Pobranie bieżącego czasu

  // Wysyłanie Live bit co określony czas
  if (currentTime - lastSendTime >= interval) {
    String liveMessage = "Live bit";  // Sygnał Live bit
    char liveMsg[20];
    liveMessage.toCharArray(liveMsg, liveMessage.length() + 1);
    vw_send((uint8_t *)liveMsg, strlen(liveMsg));  // Wyślij wiadomość
    vw_wait_tx(); // Zaczekaj na zakończenie transmisji
    lastSendTime = currentTime;  // Aktualizacja czasu wysyłki
  }

  // Wysyłanie wiadomości po wciśnięciu przycisku
  if (digitalRead(OK_PIN) == LOW) {
    delay(20); // Debounce
    String message = "Adamadacho";  // Główna wiadomość
    char msg[20];
    message.toCharArray(msg, message.length() + 1);
    digitalWrite(LED_PIN, LOW); // Włącz diodę LED
    vw_send((uint8_t *)msg, strlen(msg));  // Wyślij wiadomość
    vw_wait_tx(); // Zaczekaj na zakończenie transmisji
    while (digitalRead(OK_PIN) == LOW) {
      delay(20); // Czekaj na zwolnienie przycisku
    }
    digitalWrite(LED_PIN, HIGH); // Wyłącz diodę LED
  }
}
