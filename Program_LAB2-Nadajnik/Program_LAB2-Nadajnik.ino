#include <VirtualWire.h> // Attach RF modules library
#define LED_PIN 5 // Define no of the LED pin
#define OK_PIN 3 // Define no of the button pin
#define TRANSMIT_PIN 6 // Define FS100A data transmit pin
void setup() {
pinMode(OK_PIN, INPUT_PULLUP); // OK button declaration
pinMode(LED_PIN, OUTPUT); // LED pin declaration
vw_set_tx_pin(TRANSMIT_PIN); // VirtualWire library settings of the data transmit pin
vw_setup(2000); // VirtualWire transmision speed
digitalWrite(LED_PIN, HIGH); // Turn off the LED
}
void loop() {
String toSend = ("Adamadacho"); // Message text
char msg[20]; // Create 20-elements char table
toSend.toCharArray(msg, toSend.length() + 1); // convert text to char table
if (digitalRead(OK_PIN) == LOW) { // If an OK button has been pressed
delay(20); // Wait 20ms to stabilise button debounce
digitalWrite(LED_PIN, LOW); // Turn on the LED
vw_send((uint8_t *)msg, strlen(msg)); // Send the mesage
vw_wait_tx();
while (digitalRead(OK_PIN) == LOW) { // Wait until the button will be released
delay(20); // Wait 20ms to stabilise button debounce
}
}
digitalWrite(LED_PIN, HIGH); // Turn off the LED
delay(1000);
}