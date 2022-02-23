#include "FirebaseESP8266.h" // Install Firebase ESP8266 library
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

// Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

int led = LED_BUILTIN;

int softMargin = 2;
int global_hc_1_reading = 0;

FirebaseJson json;

int buzzer = 4;
void checkHost() {
  Firebase.setFloat(firebaseData, "/FirebaseIOT/led2", 0);
  Serail.println("Wait...!");
  delay(1000);
  int timeOut;
  for (timeOut = 25; timeOut > 0; timeout--) {
    if (Firebase.getString(ledData, "/FirebaseIOT/led2")) {
      // Serial.print(ledData.stringData());
      if (ledData.stringData() == "1") {
        Serial.print(ledData.stringData());
        digitalWrite(led, HIGH);
        timeOut = 0;
        Serial.println("Host is working!");

      } else if (ledData.stringData() == "0") {
        digitalWrite(led, LOW);
        if (timeOut == 25) {
          Serial.print("failed! Host is down, watinting for host");
        }
        Serial.print(".");
        delay(1000);
      }
    }
  }
}
void Alert(int delaY, int alertFor) {
  for (; alertFor > 0; alertFor -= (delaY * 2)) {
    digitalWrite(buzzer, HIGH);
    delay(delaY);
    digitalWrite(buzzer, LOW);
    delay(delaY);
  }
}
void setup() {

  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

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
  Serial.println("Checking host status!");
  checkHost();
}

void sensorUpdate() {

  int distance = 0;

  if (Firebase.getString(firebaseData, "/FirebaseIOT/Ultrasound_1")) {
    Serial.println("Distance : " + firebaseData.stringData() + " in");
    distance = int(firebaseData.stringData());
  } else {
    Serial.println("Distance error!");
  }

  if (!((distance >= global_hc_1_reading - softMargin) &&
        (distance <= global_hc_1_reading + softMargin))) {
    global_hc_1_reading = distance;
    Alert();
  }
}
void loop() {
  checkHost();
  sensorUpdate();
  delay(100);
}