
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST  "firstproject-99bb2-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "yEf6VGsxnPXyfKp0B0sUeuWBQCxX0VqWRGEk6VPR"
#define WIFI_SSID "Room102"
#define WIFI_PASSWORD "Room@102_6"

// int sensor=D1;

void setup() {
  Serial.begin(115200);
//   pinMode(sensor, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());               // prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to the firebase
}

int num1 = 0;
void loop() {
  while (Serial.available() > 0) {
    num1 = Serial.parseInt();
  }

  if (num1 == 0) {
    Firebase.pushString("light", “OFF”); // setup path to send light readings
  } else {
    Firebase.pushString("light", “ON”);
  }
  if (Firebase.failed()) {

    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(2000);
}