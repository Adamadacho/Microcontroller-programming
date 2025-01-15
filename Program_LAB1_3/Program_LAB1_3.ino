// Definicja pinów
const int ledPin = 13;       // Pin dla diody LED
const int buttonPin = 2;     // Pin dla przycisku

// Zmienne globalne
int mode = 0;                // Aktualny tryb (0, 1, 2)
bool buttonPressed = false;  // Stan przycisku
unsigned long lastTime = 0;  // Do kontroli migania diody
unsigned long interval = 1000; // Domyślny czas migania (1 sekunda)

void setup() {
  pinMode(ledPin, OUTPUT);   // Pin LED jako wyjście
  pinMode(buttonPin, INPUT); // Pin przycisku jako wejście
}

void loop() {
  // Odczyt stanu przycisku
  int buttonState = digitalRead(buttonPin);

  // Sprawdzanie, czy przycisk został wciśnięty
  if (buttonState == LOW && !buttonPressed) { // LOW oznacza wciśnięcie
    buttonPressed = true;
    mode = (mode + 1) % 3; // Przechodzenie między trybami 0, 1, 2
  } else if (buttonState == HIGH) {
    buttonPressed = false;
  }

  // Realizacja trybów
  switch (mode) {
    case 0: // Tryb 1: Dioda stale wyłączona
      digitalWrite(ledPin, LOW);
      break;

    case 1: // Tryb 2: Dioda miga co 1 sekundę
      interval = 1000; // Czas migania 1 sekunda
      blinkLED();
      break;

    case 2: // Tryb 3: Dioda miga szybko (0,2 sekundy)
      interval = 200; // Czas migania 0,2 sekundy
      blinkLED();
      break;
  }
}

// Funkcja migania diody
void blinkLED() {
  unsigned long currentTime = millis(); // Aktualny czas w milisekundach
  if (currentTime - lastTime >= interval) {
    lastTime = currentTime;
    int ledState = digitalRead(ledPin); // Odczyt aktualnego stanu diody
    digitalWrite(ledPin, !ledState);   // Zmiana stanu diody
  }
}
