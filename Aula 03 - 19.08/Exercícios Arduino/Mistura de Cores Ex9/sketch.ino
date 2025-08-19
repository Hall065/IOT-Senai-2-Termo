// Pinos PWM do LED RGB
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Gradualmente muda o vermelho
  for (int r = 0; r <= 255; r++) {
    analogWrite(redPin, r);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(10);
  }

  // Gradualmente muda o verde
  for (int g = 0; g <= 255; g++) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, g);
    analogWrite(bluePin, 0);
    delay(10);
  }

  // Gradualmente muda o azul
  for (int b = 0; b <= 255; b++) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, b);
    delay(10);
  }

  // Combina cores: vermelho + verde = amarelo
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);
    analogWrite(greenPin, 255 - i);
    analogWrite(bluePin, 0);
    delay(10);
  }

  // Aqui você pode adicionar mais combinações de cores
}
