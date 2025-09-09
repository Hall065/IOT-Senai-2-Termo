/***********************************************************************************
 * Exemplo simples de uso do sensor DHT11 para interpretação via serial/Excel.
 ***********************************************************************************/

// Biblioteca do DHT
#include "DHT.h"

// Porta usada e o tipo de sensor
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Armazena o valor da temperatura
float temperatura;

void setup() {
  Serial.begin(9600);     // Inicializando o monitor serial
  dht.begin();            // Inicializando o sensor
}

void loop() {
  delay(2000); // Aguarda dois segundos entre as leituras
  
  temperatura = dht.readTemperature(); // Lê a temperatura em °C

  // Verificando se existe erro na leitura
  if (isnan(temperatura)) {
    Serial.println("ERRO NO SENSOR!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
  }
}