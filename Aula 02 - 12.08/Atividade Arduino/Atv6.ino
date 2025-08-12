const int botaoPin = 2;
const int ledPin = 13;
bool ledLigado = false;

void setup() {
  pinMode(botaoPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (digitalRead(botaoPin) == LOW) {
    ledLigado = !ledLigado;             // inverte o estado do LED
    digitalWrite(ledPin, ledLigado);   // aplica novo estado no LED
    delay(200);                        // debounce simples
    while (digitalRead(botaoPin) == LOW); // espera o botão ser solto
  }
}