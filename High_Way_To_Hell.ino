#include <Servo.h>

Servo myServo;  // Create servo object
const int redRelay = 4;
const int greenRelay = 5;
const int blueRelay = 6;

// Water relay pin
const int waterRelay = 8;

// Sound sensor pins
const int soundSensorPin = 7;  // Digital output pin for sound sensor activation
const int soundAnalogPin = A0; // Analog output pin for sound intensity

// Relay states
bool redState = false;
bool greenState = false;
bool blueState = false;
bool waterState = false;

void setup() {
    Serial.begin(9600);  // Start Serial Monitor
    myServo.attach(9);   // Attach servo to pin 9

    // Set LED pins as OUTPUT
    pinMode(redRelay, OUTPUT);
    pinMode(greenRelay, OUTPUT);
    pinMode(blueRelay, OUTPUT);
}

void loop() {
  highwaytohell();
}


void highwaytohell() {
  digitalWrite(redRelay, HIGH);
  digitalWrite(greenRelay, HIGH);
  digitalWrite(blueRelay, HIGH);
  digitalWrite(waterRelay, HIGH);
  HTHpt1();
  digitalWrite(waterRelay, LOW);
  HTHpt2();
  HTHpt3();
  HTHpt4();
  myServo.write(70);
  delay(4000);
  digitalWrite(redRelay, HIGH);
  digitalWrite(waterRelay, HIGH);
}
// Function to move servo and toggle LEDs
void HTHpt1() {
    myServo.write(80);
    delay(600);

    electguitar();

    delay(1350);

    electguitar();
    delay(150);
    electguitar();

    delay(1200);

    electguitar();
    delay(150);
    electguitar();

    delay(300);

    electguitar();
    delay(150);
    electguitar();

    delay(300);

    electguitar();
    delay(300);
    electguitarfast();
    electguitarfast();
    
    delay(1200);
    digitalWrite(blueRelay, LOW);

    electguitar();
    delay(150);
    electguitar(); 
    //start drum
    
}

void unused() {
    unsigned long startTime = millis();
    while (millis() - startTime < 3900) { 
    delay(1350);

    electguitar();
    delay(150);
    electguitar();

    delay(1200);

    electguitar();
    delay(150);
    electguitar();

    delay(300);

    electguitar();
    delay(300);
    electguitarfast();
    electguitarfast();

    
    }

}

void HTHpt2() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 40000) { // Run for 20 seconds
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs12();
            delay(500);

            if (millis() - startTime >= 40000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs12();
            delay(500);

            if (millis() - startTime >= 40000) return; // Stop after 20 sec
        }
    }
  }
void HTHpt3() {
        myServo.write(85);
        digitalWrite(redRelay, LOW);
        delay(500);
        myServo.write(90);
        digitalWrite(greenRelay, LOW);
        delay(500);
        myServo.write(95);
        digitalWrite(blueRelay, LOW);
        delay(500);

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 75; angle -= 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(200);
        }
        //flicker
        flickerLED();
    }

void HTHpt4() {
    unsigned long startTime = millis(); // Record the start time
    digitalWrite(redRelay, LOW);
    while (millis() - startTime < 15000) { // Run for 20 seconds
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredblue();
            delay(500);

            if (millis() - startTime >= 15000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredblue();
            delay(500);

            if (millis() - startTime >= 15000) return; // Stop after 20 sec
        }

    }
  }


void electguitarfast() {
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(150);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);

}
void electguitar() {
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(300);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);

}

void flickerLED() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 1500) { // Run for 20 seconds
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(150);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(150);
    
    if (millis() - startTime >= 1500) return;
    }
}

void toggleLEDsredblue() {
    static int ledState = 0;

    // Turn off all LEDs first
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);

    // Turn on one LED at a time in sequence
    if (ledState == 0) {
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, LOW);
    } else if (ledState == 1) {
        digitalWrite(greenRelay, HIGH);
        digitalWrite(blueRelay, HIGH);
    }
    // Cycle through LEDs
    ledState = (ledState + 1) % 2;
}
// Function to toggle LEDs correctly
void toggleLEDs12() {
    static int ledState = 0;

    // Turn off all LEDs first
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);

    // Turn on one LED at a time in sequence
    if (ledState == 0) {
        digitalWrite(greenRelay, HIGH);
    } else if (ledState == 1) {
        digitalWrite(blueRelay, HIGH);
    }
    // Cycle through LEDs
    ledState = (ledState + 1) % 2;
}

void toggleLEDs() {
    static int ledState = 0;

    // Turn off all LEDs first
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);

    // Turn on one LED at a time in sequence
    if (ledState == 0) {
        digitalWrite(redRelay, HIGH);
    } else if (ledState == 1) {
        digitalWrite(greenRelay, HIGH);
    } else if (ledState == 2) {
        digitalWrite(blueRelay, HIGH);
    }

    // Cycle through LEDs
    ledState = (ledState + 1) % 3;
}

