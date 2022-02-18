#define output1 9
#define output2 10
#define output3 11
#define output4 12

#define senderPin1 2
#define senderPin2 3
#define senderPin3 4
#define senderPin4 5

void setup() {
  pinMode(output1, OUTPUT);
  digitalWrite(output1, LOW);
  pinMode(output2, OUTPUT);
  digitalWrite(output2, LOW);
  pinMode(output3, OUTPUT);
  digitalWrite(output3, LOW);
  pinMode(output4, OUTPUT);
  digitalWrite(output4, LOW);

  pinMode(senderPin1, OUTPUT);
  digitalWrite(senderPin1, LOW);
  pinMode(senderPin2, OUTPUT);
  digitalWrite(senderPin2, LOW);
  pinMode(senderPin3, OUTPUT);
  digitalWrite(senderPin3, LOW);
  pinMode(senderPin4, OUTPUT);
  digitalWrite(senderPin4, LOW);
  Serial.begin(9600);
  delay(100);
}
void loop() {
  digitalWrite(senderPin1, HIGH);
  delay(100);
  digitalWrite(senderPin1, LOW);
  delay(100);
  digitalWrite(senderPin2, HIGH);
  delay(100);
  digitalWrite(senderPin2, LOW);
  delay(100);
  digitalWrite(senderPin3, HIGH);
  delay(100);
  digitalWrite(senderPin3, LOW);
  delay(100);
  digitalWrite(senderPin4, HIGH);
  delay(100);
  digitalWrite(senderPin4, LOW);
  delay(100);
  Serial.println(">>>");
}