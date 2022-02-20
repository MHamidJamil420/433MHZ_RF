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

int led = 5; // Connect LED to D5

//.....................................................
String getString() {
  String sdata = "";
  char ch = '0';
  bool condit = true;
  while (condit) {
    // if (Serial.available() > 0)
    // {
    ch = Serial.read(); // get the character
    delay(20);
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9') || (ch == '=')) {
      sdata += ch;

    } else if (ch == '!') {
      Serial.println("Bypassed");
      loop();
      return "NULL";
    } else if (ch == '~') {
      Serial.println("Sr we got ");
      Serial.println(sdata);
      condit = false;
      // FileNameLoop = sdata;
    } else if (ch == '`') {
      Serial.println("Str cleared");
      sdata = "";
      // Serial.println(sdata);
      // condit = false;
      // FileNameLoop = sdata;
    }
    // }
  }
  return sdata;
}
//.....................................................

// Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseData ledData;

FirebaseJson json;

void setup() {

  Serial.begin(115200);

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

  float h, t;

  if (Firebase.getString(firebaseData, "/FirebaseIOT/temperature")) {
    Serial.println("Temperature : " + firebaseData.stringData() + " C");
  } else {
    Serial.println("temperature error!");
  }

  if (Firebase.getString(firebaseData, "/FirebaseIOT/humidity")) {
    Serial.println("Humidity : " + firebaseData.stringData() + " %");
  } else {
    Serial.println("humidity error!");
  }
}
int num1 = 0;
void loop() {
  sensorUpdate();
  if (Serial.available() >= 1) {
    // num1 = getString().toInt();
    num1 = Serial.parseInt();
    num1--;
    Serial.println("setting led value : " + String(num1));
    if (Firebase.setFloat(firebaseData, "/FirebaseIOT/led", num1)) {
      Serial.println("Led value : " + String(num1));
    } else {
      Serial.println("Led value error!");
    }
  }

  if (Firebase.getString(ledData, "/FirebaseIOT/led2")) {
    Serial.println(ledData.stringData());
    if (ledData.stringData() == "1") {
      digitalWrite(led, HIGH);
    } else if (ledData.stringData() == "0") {
      digitalWrite(led, LOW);
    }
  }
  delay(100);
}