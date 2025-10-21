#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define LED_VERMELHO 8
#define LED_AZUL 7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
}

void loop() {
  // 🔹 Lê comandos vindos do Flask
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "LED1_ON") digitalWrite(LED_AZUL, HIGH);
    else if (comando == "LED1_OFF") digitalWrite(LED_AZUL, LOW);
    else if (comando == "LED2_ON") digitalWrite(LED_VERMELHO, HIGH);
    else if (comando == "LED2_OFF") digitalWrite(LED_VERMELHO, LOW);
  }

  // 🔹 Lê sensor DHT
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("{\"error\":\"Falha na leitura do sensor\"}");
  } else {
    Serial.print("{\"temperatura\":");
    Serial.print(temperatura);
    Serial.print(",\"umidade\":");
    Serial.print(umidade);
    Serial.println("}");
  }

  delay(3000);
}
