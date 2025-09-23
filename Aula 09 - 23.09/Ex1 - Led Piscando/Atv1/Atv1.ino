void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT); //Define o pino de saída
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH); //Liga o LED
  delay(50); //Espera 1 Seg
  digitalWrite(13, LOW); //Desliga o LED
  delay(50); // Espera 1 Seg

  digitalWrite(12, HIGH); //Liga o LED
  delay(50); //Espera 1 Seg
  digitalWrite(12, LOW); //Desliga o LED
  delay(50); // Espera 1 Seg
}
