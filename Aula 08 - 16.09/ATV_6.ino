int LED = 8;
void setup () {
Serial. begin (9600); 
pinMode (LED, OUTPUT);
}
void loop () {
int LDR = analogRead (A0) ;
Serial.println(LDR);

if (LDR<500)
digitalWrite (LED, HIGH) ;
else
digitalWrite (LED, LOW) ;

delay (500) ;

}