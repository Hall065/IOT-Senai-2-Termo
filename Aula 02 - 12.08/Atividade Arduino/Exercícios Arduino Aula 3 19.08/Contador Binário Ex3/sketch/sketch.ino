// Quantidade de LEDs (troque para 8 se quiser)
const int numLEDs = 4;

// Pinos conectados aos LEDs
int leds[] = {2, 3, 4, 5}; 

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Contador vai de 0 até o máximo que cabe nos LEDs
  for (int numero = 0; numero < (1 << numLEDs); numero++) {
    mostrarBinario(numero);
    delay(500); // meio segundo entre cada número
  }
}

// Função que acende os LEDs conforme o número em binário
void mostrarBinario(int valor) {
  for (int i = 0; i < numLEDs; i++) {
    int bit = (valor >> i) & 1; // pega o i-ésimo bit do valor
    digitalWrite(leds[i], bit);
  }
}
