#include <Servo.h>
Servo myservo;  // Cria um objeto baseado na biblioteca Servo
int potpin = 0;  // Pino analógico ligado ao potenciômetro
int val;// Variável para ler o valor do potenciômetro

void setup() {
  myservo.attach(9);  // Diz que o objeto "myservo" está ligado ao pino 9
}

void loop() {
  val = analogRead(potpin); // Ler e armazena o valor do potenciometro
  val = map(val, 0, 1023, 0, 180); // Faz um mapeamento 
  myservo.write(val); // Comando para mandar o servo para posição "val" que foi mapeada
  delay(15);  // Espera de 15 ms
}