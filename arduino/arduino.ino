#include <stdlib.h>
#include <string.h>

const int segments[] = {2, 3, 4, 5, 6, 7, 8}; // Segment pins a-g
const int leftSegment = 11, rightSegment = 12;

// Digit segment patterns (0-9)
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

const int trigPinleft = 1;
const int echoPinleft = 0;
const int trigPinright = 13;
const int echoPinright = 10;

long durationleft, durationright;
int distanceleft, distanceright;
int count=13;
// const unsigned long timeThreshold = 1000; // กำหนดช่วงเวลาสูงสุดในการผ่านระหว่างเซ็นเซอร์ซ้ายและขวา (1 วินาที)

// bool leftTriggered = false;
// bool rightTriggered = false;
// unsigned long leftTriggerTime = 0;
// unsigned long rightTriggerTime = 0;


void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second
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

    // Serial.print("distanceleft = ");
    // Serial.println(distanceleft);
    // Serial.print("distanceright = ");
    // Serial.println(distanceright);

    // unsigned long currentTime = millis();

    // // กรณีคนเริ่มผ่านเซ็นเซอร์ซ้ายก่อน
    // if (distanceleft <= 50 && !leftTriggered) {
    //     leftTriggerTime = currentTime;
    //     leftTriggered = true;
    //       // ตรวจจับว่าคนผ่านเซ็นเซอร์ขวาภายในเวลาที่กำหนดหลังจากซ้าย
    //     if (distanceright <= 50 && leftTriggered && (currentTime - leftTriggerTime) <= timeThreshold) {
    //         if (count > 0 && count <= 13) {
    //             count--;
    //             Serial.print("Count = ");
    //             Serial.println(count);
    //         } else {
    //             Serial.println("FULL");
    //         }
    //         leftTriggered = false; // รีเซ็ตสถานะ
    //     }
    // }

    // // กรณีคนเริ่มผ่านเซ็นเซอร์ขวาก่อน
    // else if (distanceright <= 50 && !rightTriggered) {
    //     rightTriggerTime = currentTime;
    //     rightTriggered = true;
    //         // ตรวจจับว่าคนผ่านเซ็นเซอร์ซ้ายภายในเวลาที่กำหนดหลังจากขวา
    //     if (distanceleft <= 50 && rightTriggered && (currentTime - rightTriggerTime) <= timeThreshold) {
    //         if (count >= 0 && count < 13) {
    //             count++;
    //             Serial.print("Count = ");
    //             Serial.println(count);
    //         } else {
    //             Serial.println("Available");
    //         }
    //         rightTriggered = false; // รีเซ็ตสถานะ
    //     }
    // }

    // // รีเซ็ตสถานะหากไม่ได้มีการผ่านอีกเซ็นเซอร์ภายในช่วงเวลาที่กำหนด
    // if (leftTriggered && (currentTime - leftTriggerTime) > timeThreshold) {
    //     leftTriggered = false;
    // }
    // if (rightTriggered && (currentTime - rightTriggerTime) > timeThreshold) {
    //     rightTriggered = false;
    // }

    // delay(1000);

    if (distanceleft <= 50) {
      if (count > 0 && count <= 13) {
        count--;
        Serial.print("count = ");
        Serial.println(count);
      }else {
        Serial.println("FULL");
      }
  }else if (distanceright <= 50) {
      if (count >= 0 && count < 13) {
        count++;
        Serial.print("count = ");
        Serial.println(count);
      }else {
        Serial.println("Available");
      }
  }

  int digit1, digit2;
  // for (int i = 0; i < ; i += 2) {
    if (count/10 == 0) {
    	digit1 = 0;
      digit2 = count%10;
    }else {
    	digit1 = (int)count/10;
      digit2 = count%10;
    }
    //int digit1 = text[i] - '0', digit2 = text[i + 1] - '0';
    showTwoDigits(digit1, digit2);
  // }
    
    delay(1000); // Wait 1 second before the next measurement
}

void showTwoDigits(int digit1, int digit2) {
  unsigned long startTime = millis();
  while (millis() - startTime < 1000) {
    // แสดง digit1 บน rightSegment
    displayDigit(digit1, rightSegment);
    delay(10);  // เพิ่มเวลาแสดงผล digit1 ให้ยาวขึ้น
    clearSegments(); // ปิดการแสดงผลทั้งหมดชั่วคราว

    // แสดง digit2 บน leftSegment
    displayDigit(digit2, leftSegment);
    delay(10);  // เพิ่มเวลาแสดงผล digit2 ให้ยาวขึ้น
    clearSegments(); // ปิดการแสดงผลทั้งหมดชั่วคราว
  }
}

// ฟังก์ชันสำหรับการปิดทุก segment
void clearSegments() {
  digitalWrite(leftSegment, LOW);
  digitalWrite(rightSegment, LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], LOW);
  }
}

void displayDigit(int digit, int activeSegment) {
  digitalWrite(activeSegment, HIGH); // เปิดใช้งาน segment ที่ต้องการ
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], digitPatterns[digit][i] ? HIGH : LOW);
  }
}


