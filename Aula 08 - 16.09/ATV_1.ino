#include "DHT.h"

#define DHTPIN 2       // Pino digital onde o DHT11 está conectado
#define DHTTYPE DHT11  // Tipo de sensor

DHT dht(DHTPIN, DHTTYPE);

// Pinos dos LEDs
const int ledVerde   = 3;
const int ledAmarelo = 4;
const int ledVermelho= 5;

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature(); // Lê temperatura em °C

  if (isnan(temp)) {
    Serial.println("Erro de leitura do sensor!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.println(temp);

  // Lógica dos LEDs
  if (temp < 25.0) {            // Normal
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } 
  else if (temp < 30.0) {       // Quente
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } 
  else {                        // Muito quente
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  delay(2000); // Atualiza a cada 2 segundos
}


//ATV_01