int buzzerPin = 4;

void setup() {
  pinMode(buzzerPin,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}

void alert(int pinNumber){
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);  
}

void loop() {
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  delay(1000);


}