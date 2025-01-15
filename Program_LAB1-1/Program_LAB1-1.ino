// Definicja pinów
const int ledPin = 13;
const int buttonPin = 2;
void setup() {
// Ustawienie pinu LED jako wyjście
pinMode(ledPin, OUTPUT);
// Ustawienie pinu przycisku jako wejście
pinMode(buttonPin, INPUT);
}
void loop() {
// Odczyt stanu przycisku
int buttonState = digitalRead(buttonPin);
// Sprawdzenie stanu przycisku
if (buttonState == LOW) {
// Włączenie LED
digitalWrite(ledPin, HIGH);
} else {
// Wyłączenie LED
digitalWrite(ledPin, LOW);
}
}