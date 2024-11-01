
#include <WiFiS3.h>
#include <MQTTClient.h>
#include <stdlib.h>
#include <string.h>

const char WIFI_SSID[] = "your ssid";          // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "password";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "arduino-uno-r4-clientgdxytscux";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that Arduino should publish/subscribe
const char PUBLISH_TOPIC[] = "vansenger";    // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC[] = "vansenger";  // CHANGE IT AS YOU DESIRE

const int PUBLISH_INTERVAL = 1 * 1000;  // 60 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

const int trigPinleft = 1;
const int echoPinleft = 0;
const int trigPinright = 13;
const int echoPinright = 10;

long durationleft, durationright;
int distanceleft, distanceright;
int count=13;

const int segments[] = {2, 3, 4, 5, 6, 7, 8}; // Segment pins a-g
const int leftSegment = 11, rightSegment = 12;

const int digitPatterns[][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  Serial.begin(9600);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // wait 10 seconds for connection:
    delay(10000);
  }
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  connectToMQTT();

    pinMode(trigPinleft, OUTPUT);
    pinMode(echoPinleft, INPUT);
    pinMode(trigPinright, OUTPUT);
    pinMode(echoPinright, INPUT);
    for (int i = 0; i < 7; i++) {
      pinMode(segments[i], OUTPUT);
    }
    pinMode(leftSegment, OUTPUT);
    pinMode(rightSegment, OUTPUT);
}

void loop() {
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() {
    // Clear the trigPin
    digitalWrite(trigPinleft, LOW);
    digitalWrite(trigPinright, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPinleft, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPinleft, LOW);

    durationleft = pulseIn(echoPinleft, HIGH);

    digitalWrite(trigPinright, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPinright, LOW);
    
    // Read the echoPin, return the sound wave travel time in microseconds
    durationright = pulseIn(echoPinright, HIGH);
    
    // Calculate the distance in cm and inches
    distanceleft = durationleft * 0.034 / 2;
    distanceright = durationright * 0.034 / 2;

    Serial.println(distanceleft);
    Serial.println(distanceright);

  if (distanceleft <= 70) {
      if (count > 0 && count <= 13) {
        count--;
        Serial.print("count = ");
        Serial.println(count);
      }else {
        Serial.println("FULL");
      }
  }else if (distanceright <= 70) {
      if (count >= 0 && count < 13) {
        count++;
        Serial.print("count = ");
        Serial.println(count);
      }else {
        Serial.println("Available");
      }
  int digit1, digit2;
    if (count/10 == 0) {
    	digit1 = 0;
      digit2 = count%10;
    }else {
    	digit1 = (int)count/10;
      digit2 = count%10;
    }
    showTwoDigits(digit1, digit2);
    
    // delay(1000); // Wait 1 second before the next measurement
  }


  // int val = millis();
  //int val = analogRead(A0);
  String val_str = String(count);

  // Convert the string to a char array for MQTT publishing
  char messageBuffer[10];
  val_str.toCharArray(messageBuffer, 10);

  // Publish the message to the MQTT topic
  mqtt.publish(PUBLISH_TOPIC, messageBuffer);

  // Print debug information to the Serial Monitor in one line
  Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));
}


void messageHandler(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT: topic: " + topic + " | payload: " + payload);

  // You can process the incoming data , then control something
  /*
  process something
  */
}

void showTwoDigits(int digit1, int digit2) {
  unsigned long startTime = millis();
  while (millis() - startTime < 100) {
    displayDigit(digit1, rightSegment);
    delay(2);
    displayDigit(digit2, leftSegment);
    delay(2);
  }
}

void displayDigit(int digit, int activeSegment) {
  digitalWrite(leftSegment, activeSegment == leftSegment ? HIGH : LOW);
  digitalWrite(rightSegment, activeSegment == rightSegment ? HIGH : LOW);

  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], digitPatterns[digit][i] ? HIGH : LOW);
  }
}
