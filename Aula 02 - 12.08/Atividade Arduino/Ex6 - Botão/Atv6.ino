 int botaoPin = 2;
 int ledPin = 13;

void setup() {
  pinMode(botaoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
}

void loop() {
  if (digitalRead(botaoPin) == HIGH) {       
    digitalWrite(ledPin, HIGH);   // aplica novo estado no LED
    delay(2000);    
    digitalWrite(ledPin, LOW);                    // debounce simples
  }
} 