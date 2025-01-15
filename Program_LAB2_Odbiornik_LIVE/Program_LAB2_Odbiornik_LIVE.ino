#include <VirtualWire.h> // Załącz bibliotekę VirtualWire

#define RECEIVE_PIN 11 // Pin odbioru dla odbiornika
#define LED_PIN 2      // Pin diody LED sygnalizującej "LIVE bit"

unsigned long lastReceivedTime = 0; // Czas ostatniego odebrania wiadomości
const unsigned long timeout = 3000; // Czas maksymalny bez sygnału "LIVE" (3 sekundy)

void setup() {
  pinMode(LED_PIN, OUTPUT);        // Ustawienie pinu LED jako wyjście
  vw_set_rx_pin(RECEIVE_PIN);      // Ustawienie pinu odbioru
  vw_setup(2000);                  // Prędkość transmisji (2000 bps)
  vw_rx_start();                   // Inicjalizacja odbiornika
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];   // Bufor na odebraną wiadomość
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // Długość bufora

  // Sprawdź, czy odebrano wiadomość
  if (vw_get_message(buf, &buflen)) {
    // Sprawdź, czy wiadomość to "LIVE"
    String message = "";
    for (int i = 0; i < buflen; i++) {
      message += (char)buf[i];
    }
    if (message == "LIVE") {
      digitalWrite(LED_PIN, HIGH);   // Włącz diodę LED
      lastReceivedTime = millis();  // Zaktualizuj czas ostatniego odebrania
    }
  }

  // Sprawdź, czy czas od ostatniego sygnału "LIVE" przekroczył limit
  if (millis() - lastReceivedTime > timeout) {
    digitalWrite(LED_PIN, LOW);     // Wyłącz diodę LED
  }
}
