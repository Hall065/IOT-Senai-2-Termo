int pinoPIR = 2;     // Pino digital do sensor PIR
int pinoLED = 13;    // LED no pino 13 (pode ser externo também)
int contador = 0;    // Contador de pessoas

void setup() {
  pinMode(pinoPIR, INPUT);   // PIR como entrada
  pinMode(pinoLED, OUTPUT);  // LED como saída
  Serial.begin(9600);        // Inicia comunicação Serial
}

void loop() {
  int leitura = digitalRead(pinoPIR);

  if (leitura == HIGH) {          // Se o PIR detectar movimento
    contador++;                   // Incrementa o contador
    digitalWrite(pinoLED, HIGH);  // Acende LED
    Serial.print("Pessoa detectada! Total: ");
    Serial.println(contador);

    delay(2000); // Delay para evitar múltiplas contagens por 1 detecção
  } else {
    digitalWrite(pinoLED, LOW);   // LED apagado sem movimento
  }
}