#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// === Configurações ===
#define DHTPIN 13        
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LCD 16x2: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

Servo exaustor;

const int buzzerPin = 10;
const int servoPin = 9;

// Limites
const float LIM_IDEAL = 20.0;
const float LIM_QUENTE = 27.0;
const float LIM_MUITO = 30.0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.begin(16, 2);
  lcd.print("CPD MONITOR v3");
  delay(2000);
  lcd.clear();

  exaustor.attach(servoPin);
  exaustor.write(0);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);
}

void loop() {
  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro no sensor ");
    lcd.setCursor(0, 1);
    lcd.print("Verifique DHT11");
    delay(2000);
    return;
  }

  String status;
  int anguloServo = 0;

  if (temperatura <= LIM_IDEAL) {
    status = "IDEAL";
    noTone(buzzerPin);
    anguloServo = 0;
  } 
  else if (temperatura <= LIM_QUENTE) {
    status = "QUENTE";
    noTone(buzzerPin);
    anguloServo = 90;
  } 
  else if (temperatura <= LIM_MUITO) {
    status = "MTO QUENTE";
    noTone(buzzerPin);
    anguloServo = 180;
  } 
  else {
    status = "PERIGO";
    tone(buzzerPin, 1200);
    anguloServo = 270;
  }

  exaustor.write(anguloServo);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatura, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.print(status);
  lcd.print("   ");

  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C  |  Status: ");
  Serial.print(status);
  Serial.print("  | Servo: ");
  Serial.println(anguloServo);

  // ==== Recepção de comandos da API ====
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');

    if (cmd == "BUZZER_ON") {
      tone(buzzerPin, 1200);
    } 
    else if (cmd == "BUZZER_OFF") {
      noTone(buzzerPin);
    }
  }

  delay(1000);
}
