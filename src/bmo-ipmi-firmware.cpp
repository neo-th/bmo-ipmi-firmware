#include <Arduino.h>

const int powerPin = 2; // PWRBTN# connected to digital pin 2
const int resetPin = 3;  // RESET# connected to digital pin 3
const int statusPin = 4; // PLED# connected to digital pin 4

void setup() {
  Serial.begin(9600);
  
  pinMode(powerPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(statusPin, INPUT);
  
  // Set default state to HIGH (no action)
  digitalWrite(powerPin, HIGH);
  digitalWrite(resetPin, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    bool systemIsOn = digitalRead(statusPin) == HIGH;
    
    if (command == "POWER ON") {
        if (!systemIsOn) {
            digitalWrite(powerPin, LOW);
            delay(500);
            digitalWrite(powerPin, HIGH);
            Serial.println("Powered On");
        } else {
            Serial.println("System already on");
        }
    } 
    else if (command == "POWER OFF") {
        if (systemIsOn) {
            digitalWrite(powerPin, LOW);
            delay(500);
            digitalWrite(powerPin, HIGH);
            Serial.println("Powered Off");
        } else {
            Serial.println("System already off");
        }
    } 
    else if (command == "RESET") {
        digitalWrite(resetPin, LOW);
        delay(500);
        digitalWrite(resetPin, HIGH);
        Serial.println("System Reset");
    }
  }
}

