// LED no pino 13
const int led = 13;

// Duração das unidades de tempo no Morse (quanto menor, mais rápido)
const int dotTime = 200;   // ponto (.)
const int dashTime = dotTime * 3; // traço (-)
const int spaceTime = dotTime * 7; // espaço entre palavras

// Texto para converter
String frase = "SOS ARDUINO";

// Tabela de Código Morse
String morse[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",  // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",        // S-Z
  "-----", ".----", "..---", "...--", "....-", ".....",            // 0-5
  "-....", "--...", "---..", "----."                               // 6-9
};

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Transmitindo em Morse...");
}

void loop() {
  for (int i = 0; i < frase.length(); i++) {
    char c = toupper(frase[i]); // deixa maiúsculo

    if (c == ' ') {
      delay(spaceTime); // espaço entre palavras
    } 
    else {
      String codigo = getMorse(c);
      Serial.print(c);
      Serial.print(" -> ");
      Serial.println(codigo);

      transmitir(codigo);
      delay(dotTime * 3); // pausa entre letras
    }
  }

  while (1); // trava o loop depois de transmitir
}

// Retorna o código Morse de um caractere
String getMorse(char c) {
  if (c >= 'A' && c <= 'Z') {
    return morse[c - 'A'];
  } else if (c >= '0' && c <= '9') {
    return morse[c - '0' + 26];
  } else {
    return "";
  }
}

// Pisca o LED conforme o código Morse
void transmitir(String codigo) {
  for (int i = 0; i < codigo.length(); i++) {
    if (codigo[i] == '.') {
      digitalWrite(led, HIGH);
      delay(dotTime);
      digitalWrite(led, LOW);
    } 
    else if (codigo[i] == '-') {
      digitalWrite(led, HIGH);
      delay(dashTime);
      digitalWrite(led, LOW);
    }
    delay(dotTime); // pausa entre sinais da mesma letra
  }
}
