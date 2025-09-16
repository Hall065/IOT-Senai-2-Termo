// Pinos dos LEDs
const int ledVermelho = 2;
const int ledAmarelo  = 3;
const int ledVerde    = 4;
const int ledPedestre = 5;

// Pino do botão
const int botao = 6;

bool pedidoPedestre = false;

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledPedestre, OUTPUT);

  pinMode(botao, INPUT); // botão com resistor pull-down de 10k
}

void loop() {
  // Verifica se o botão foi pressionado
  if (digitalRead(botao) == HIGH) {
    pedidoPedestre = true; // registra o pedido de travessia
  }

  if (pedidoPedestre) {
    cicloPedestre();
    pedidoPedestre = false; // reseta o pedido
  } else {
    cicloSemaforo();
  }
}

void cicloSemaforo() {
  // Verde - veículos passam
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledPedestre, LOW);
  delay(4000);

  // Amarelo - atenção
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, HIGH);
  delay(2000);

  // Vermelho - veículos param
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, HIGH);
  delay(4000);
}

void cicloPedestre() {
  // Sinaliza vermelho para veículos
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, HIGH);

  // Acende LED do pedestre
  digitalWrite(ledPedestre, HIGH);
  delay(5000); // tempo para atravessar

  // Apaga LED do pedestre
  digitalWrite(ledPedestre, LOW);

  // Opcional: deixa o semáforo vermelho mais um pouco
  delay(1000);
}
