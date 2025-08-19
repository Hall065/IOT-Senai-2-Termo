// Pino do LED (com PWM)
const int led = 9;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  // Aumenta o brilho
  for (int brilho = 0; brilho <= 255; brilho++) {
    analogWrite(led, brilho); // PWM: 0 apagado, 255 máximo
    delay(10); // define a velocidade do fade
  }

  // Diminui o brilho
  for (int brilho = 255; brilho >= 0; brilho--) {
    analogWrite(led, brilho);
    delay(10);
  }
}
