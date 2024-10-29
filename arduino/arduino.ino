#define PIN_1A = 2
#define PIN_1B = 3
#define PIN_1C = 4
#define PIN_1D = 5
#define PIN_1E = 6
#define PIN_1F = 7
#define PIN_1G = 8

const int trigPinleft = 1;
const int echoPinleft = 0;
const int trigPinright = 13;
const int echoPinright = 10;

long durationleft, durationright;
int distanceleft, distanceright;
int count=13;
unsigned long time_A, time_B ,time_led;


void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second
    pinMode(trigPinleft, OUTPUT);
    pinMode(echoPinleft, INPUT);
    pinMode(trigPinright, OUTPUT);
    pinMode(echoPinright, INPUT);
}

void loop() {
    // Clear the trigPin
    digitalWrite(trigPinleft, LOW);
    digitalWrite(trigPinright, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin HIGH for 10 microseconds
    // digitalWrite(trigPin, HIGH);
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
    // distanceInch = duration * 0.0133 / 2;

    if (distanceleft <= 50) {
      // if (distanceright <= 50) {
        if (count > 0 && count <= 13) {
          count--;
          Serial.print("count = ");
          Serial.println(count);
        }else {
          Serial.println("FULL");
          // count = 0;
        }
      // }
    }else if (distanceright <= 50) {
      // if (distanceleft <= 50) {
        if (count >= 0 && count < 13) {
          count++;
          Serial.print("count = ");
          Serial.println(count);
        }else {
          Serial.println("Available");
          // count = 0;
        }
      // }
    }
    
    delay(1000); // Wait 1 second before the next measurement
}

