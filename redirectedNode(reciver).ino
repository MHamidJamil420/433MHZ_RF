#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0xC1, 0x1E, 0x6B};
// EC:FA:BC:C1:1E:6B

typedef struct struct_message {
  float pin;
  float PinCode;
} struct_message;
const long interval = 10000;
unsigned long previousMillis = 0; // will store last time DHT was updated
// Create a struct_message called MsgToBeSend to hold sensor readings
struct_message MsgToBeSend;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  } else {
    Serial.println("Delivery fail");
    // when room Node is not working
  }
}
int incomingPin = 0;
int incomingPinCode = 0;
// Callback when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  digitalWrite(LED_BUILTIN,
               HIGH);             // turn the LED on (HIGH is the voltage level)
  delay(100);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  // delay(50);

  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingPin = incomingReadings.pin;
  incomingPinCode = incomingReadings.PinCode;
}

void getReadings() {
  Serial.print("incomingPin : " + String(incomingPin) + ", incomingPinCode " +
               String(incomingPinCode));
}

void printIncomingReadings() {
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Pin: ");
  Serial.print(incomingPin);
  Serial.print("  __  ");
  Serial.print("Code: ");
  Serial.println(incomingPinCode);
  // Serial.println("");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("reciver here!");
  // Init DHT sensor
  // dht.begin();

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    // Get DHT readings
    getReadings();

    // Set values to send
    MsgToBeSend.pin = random(1, 6);
    MsgToBeSend.PinCode = random(0, 2);
    Serial.println("Pin " + String(MsgToBeSend.pin) + " PinCode " +
                   String(MsgToBeSend.PinCode));
    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *)&MsgToBeSend,
                 sizeof(MsgToBeSend));

    // Print incoming readings
    printIncomingReadings();
    delay(500);
  }
}