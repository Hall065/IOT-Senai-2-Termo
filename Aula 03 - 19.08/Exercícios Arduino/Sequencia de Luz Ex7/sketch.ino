// Quantidade de LEDs
const int numLEDs = 8;

// Pinos conectados aos LEDs
int leds[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Acende um a um
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(leds[i], HIGH);
    delay(150); // espera
  }

  // Apaga um a um
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(leds[i], LOW);
    delay(150);
  }
}
