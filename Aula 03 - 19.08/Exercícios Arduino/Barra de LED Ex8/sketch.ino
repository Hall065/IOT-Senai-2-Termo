// Quantidade de LEDs
const int numLEDs = 8;

// Pinos dos LEDs
int leds[] = {2, 3, 4, 5, 6, 7, 8, 9};

// Pino do potenciômetro
const int pot = A0;

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int valor = analogRead(pot); // lê 0-1023 do potenciômetro
  Serial.println(valor);

  // Converte leitura para quantidade de LEDs acesos
  int ledsAcender = map(valor, 0, 1023, 0, numLEDs);

  for (int i = 0; i < numLEDs; i++) {
    if (i < ledsAcender) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  delay(50); // atualiza rápido
}
