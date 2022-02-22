
// FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h" // Install Firebase ESP8266 library
#include <DHT.h> // Install DHT11 Library and Adafruit Unified Sensor Library
#include <ESP8266WiFi.h>
#define FIREBASE_HOST                                                          \
  "firstproject-99bb2-default-rtdb.asia-southeast1.firebasedatabase.app/" // Without
                                                                          // http://
                                                                          // or
                                                                          // https://
                                                                          // schemes
#define FIREBASE_AUTH "yEf6VGsxnPXyfKp0B0sUeuWBQCxX0VqWRGEk6VPR"
#define WIFI_SSID "Room102"
#define WIFI_PASSWORD "Room@102_6"

#define DHTPIN 2 // Connect Data pin of DHT to D2
int led = 5;     // Connect LED to D5

#define echoPin 4 //  attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 5 // attach pin D3 Arduino to pin Trig of HC-SR04
long duration;    // variable for the duration of sound wave travel
int distance;     // variable for the distance measurement
int globle_HC_1 = 0;
int softMargin = 2;
int global_hc_1_reading = 0;

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String readString;
// Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  Serial.begin(115200);
  dht.begin();
  pinMode(led, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void sensorUpdate() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //========================================

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

  //========================================

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C  ,"));
  Serial.print(f);
  Serial.println(F("F  "));

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", t)) {
    // Serial.println("PASSED");
    // Serial.println("PATH: " + firebaseData.dataPath());
    // Serial.println("TYPE: " + firebaseData.dataType());
    // Serial.println("ETag: " + firebaseData.ETag());
    // Serial.println("------------------------------------");
    // Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", h)) {
    // Serial.println("PASSED");
    // Serial.println("PATH: " + firebaseData.dataPath());
    // Serial.println("TYPE: " + firebaseData.dataType());
    // Serial.println("ETag: " + firebaseData.ETag());
    // Serial.println("------------------------------------");
    // Serial.println();
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
  if (globle_HC_1 != distance && distance != 0) {
    if (Firebase.setFloat(firebaseData, "/FirebaseIOT/Ultrasound_1",
                          distance)) {
      Serial.println("U_Distance 1 updated!");
      globle_HC_1 = distance;
      Serial.print(F("Pass1"));
    } else {
      Serial.println("U_Distance 1 not updated successfully!");
    }
  }
}

bool dataEnterd = false;
void loop() {
  sensorUpdate();

  if (Firebase.getString(ledData, "/FirebaseIOT/led")) {
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      digitalWrite(led, HIGH);
    } else if (ledData.stringData() == "0") {
      digitalWrite(led, LOW);
    }
  }
  delay(100);
}