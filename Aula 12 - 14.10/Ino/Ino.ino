const int led1Pin = 7;
const int led2Pin = 8;
const int led3Pin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'A': digitalWrite(led1Pin, HIGH); break;
      case 'a': digitalWrite(led1Pin, LOW); break;
      case 'B': digitalWrite(led2Pin, HIGH); break;
      case 'b': digitalWrite(led2Pin, LOW); break;
      case 'C': digitalWrite(led3Pin, HIGH); break;
      case 'c': digitalWrite(led3Pin, LOW); break;
    }
  }
}
