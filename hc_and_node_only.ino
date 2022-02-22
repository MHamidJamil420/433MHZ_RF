
#define echoPin 4 //  attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 5 // attach pin D3 Arduino to pin Trig of HC-SR04
long duration;    // variable for the duration of sound wave travel
int distance;     // variable for the distance measurement
int globle_HC_1 = 0;
int softMargin = 2;
int global_hc_1_reading = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  Serial.begin(115200);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  distance = distance / 2.54;
  if (!((distance >= global_hc_1_reading - softMargin) &&
        (distance <= global_hc_1_reading + softMargin))) {
    global_hc_1_reading = distance;
    Serial.println(" -->> D1:  " + String(distance));
  }
  delay(1000);
}