// Quantidade de LEDs
const int numLEDs = 8;

// Pinos dos LEDs
int leds[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Vai da esquerda para a direita
  for (int i = 0; i < numLEDs; i++) {
    acendeLed(i);
  }
  
  // Vai da direita para a esquerda
  for (int i = numLEDs - 2; i > 0; i--) {
    acendeLed(i);
  }
}

// Função para acender LED e apagar os outros
void acendeLed(int indice) {
  for (int j = 0; j < numLEDs; j++) {
    digitalWrite(leds[j], LOW); // apaga todos
  }
  digitalWrite(leds[indice], HIGH); // acende só o atual
  delay(150); // velocidade da “corrida”
}
