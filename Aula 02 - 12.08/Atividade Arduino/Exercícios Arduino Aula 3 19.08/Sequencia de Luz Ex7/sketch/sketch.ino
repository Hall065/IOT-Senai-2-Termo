//Biblioteca do DTH
#include "DHT.h"
//armazena o valor de temperatura
float temperatura;
//porta usada e o tipo de sensor
DHT dht(3, DHT11);
// CÓDIGO
void setup() {
Serial.begin(9600);// inicializando o monitor serial
dht.begin();// Inicializando o sensor
}
void loop() {
delay(2000);// Aguarda dois segundos entre as leituras
temperatura = dht.readTemperature();//Lê o valor da temperatura em C°
//Verificando se existe erro na leitura da temperatura
if (isnan(temperatura)) { Serial.println("ERRO NO SENSOR!");}
//Se tudo funcionar envia a temperatura para a serial
else {Serial.println(temperatura); /*em C°*/}
}
/*fim do código :)*/