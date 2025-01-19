#define LEDYellow 4
#define LEDRed 3
#define LEDBlue 2

char odebraneDane;

void setup() {
  Serial.begin(9600);
  pinMode(LEDYellow, OUTPUT);
  pinMode(LEDRed, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    odebraneDane = Serial.read();
  }

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

  if (odebraneDane == '7') {
    digitalWrite(LEDYellow, HIGH);
    digitalWrite(LEDRed, HIGH);
    digitalWrite(LEDBlue, HIGH);
  } else if (odebraneDane == '8') {
    digitalWrite(LEDYellow, LOW);
    digitalWrite(LEDRed, LOW);
    digitalWrite(LEDBlue, LOW);
  }
}
