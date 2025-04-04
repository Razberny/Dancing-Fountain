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
    pinMode(waterRelay, OUTPUT);
}

void loop() {
    believer();
    
    delay(20000);
}


void believer() {
    believerpt1();  
    pain();
    believerpt2();
    believerlyric();
    pain(); 
    believerpt3();
    pain();
    believerpt4();
    myServo.write(70);
    digitalWrite(blueRelay, LOW);
    digitalWrite(redRelay, HIGH);
    delay(2000);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
}
// Function to move servo and toggle LEDs
void believerpt1() {
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 54000) { // Run for 20 seconds
    if (millis() - startTime >= 52000) return;
    myServo.write(70);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    delay(1000);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    if (millis() - startTime >= 52000) return;
    delay(500);
    myServo.write(78);
    digitalWrite(redRelay,LOW);
    delay(150);
    myServo.write(85);
    digitalWrite(greenRelay, LOW);
    delay(150);
    myServo.write(92);
    digitalWrite(blueRelay, LOW);
    delay(150);
    myServo.write(100);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    if (millis() - startTime >= 52000) return;
    
        // Move Servo from 100 back to 70
        for (int i = 0; i < 2; i++) {
            delay(1000);
            myServo.write(70);
            digitalWrite(waterRelay, LOW);
            digitalWrite(redRelay, LOW);
            digitalWrite(greenRelay, LOW);
            digitalWrite(blueRelay, LOW);
            delay(500);
            myServo.write(78);
            digitalWrite(redRelay,LOW);
            delay(150);
            myServo.write(85);
            digitalWrite(greenRelay, LOW);
            delay(150);
            myServo.write(92);
            digitalWrite(blueRelay, LOW);
            delay(150);
            myServo.write(100);
            digitalWrite(waterRelay, HIGH);
            digitalWrite(redRelay, HIGH);
            digitalWrite(greenRelay, HIGH);
            digitalWrite(blueRelay, HIGH);
            if (millis() - startTime >= 55000) return;
        }
        delay(1000);
        digitalWrite(redRelay, LOW);
        delay(800);
        if (millis() - startTime >= 55000) return;
    }
}

void pain() {
    myServo.write(70);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(1000);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
}

void believerpt2() {
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 10000) { // Run for 20 seconds
    if (millis() - startTime >= 10000) return; 
    delay(500);
    myServo.write(78);
    digitalWrite(greenRelay,LOW);
    delay(150);
    myServo.write(85);
    digitalWrite(greenRelay, HIGH);
    delay(150);
    myServo.write(92);
    digitalWrite(greenRelay, LOW);
    delay(150);
    myServo.write(100);
    digitalWrite(greenRelay, HIGH);
    if (millis() - startTime >= 10000) return;
    
        // Move Servo from 100 back to 70
        for (int i = 0; i < 2; i++) {
            delay(1000);
            myServo.write(70);
            digitalWrite(waterRelay, LOW);
            digitalWrite(blueRelay, LOW);
            delay(500);
            myServo.write(78);
            digitalWrite(blueRelay,HIGH);
            delay(150);
            myServo.write(85);
            digitalWrite(blueRelay, LOW);
            delay(150);
            myServo.write(92); 
            digitalWrite(blueRelay, HIGH);
            delay(150);
            myServo.write(100);
            digitalWrite(waterRelay, HIGH);
            digitalWrite(redRelay, HIGH);
            digitalWrite(blueRelay, LOW);
            if (millis() - startTime >= 10000) return;
        }
        delay(1000);
        digitalWrite(waterRelay, LOW);
        digitalWrite(blueRelay, HIGH);
        digitalWrite(redRelay, LOW);
        delay(1000);
        myServo.write(70);
        
        if (millis() - startTime >= 10000) return;
    }
}

void believerlyric(){
    digitalWrite(waterRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(1000);
    myServo.write(100);
    digitalWrite(waterRelay, LOW);
    digitalWrite(blueRelay, LOW); 
    digitalWrite(greenRelay, LOW);
    delay(1000);
    digitalWrite(blueRelay, HIGH); 
    digitalWrite(greenRelay, HIGH);
}

void believerpt3() {
   
    delay(1000);
    myServo.write(80);
    digitalWrite(redRelay, HIGH);
    delay(500);
    digitalWrite(redRelay,LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    delay(150);
    digitalWrite(redRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    delay(150);
    digitalWrite(redRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    delay(500);
    myServo.write(90);
    delay(500);
    digitalWrite(redRelay,LOW);
    digitalWrite(greenRelay,LOW);
    delay(150);
    digitalWrite(greenRelay, HIGH);
    delay(150);
    digitalWrite(greenRelay,LOW);
    delay(150);
    digitalWrite(greenRelay, HIGH);
    delay(150);
    digitalWrite(greenRelay, LOW);
    delay(150);
    digitalWrite(greenRelay, HIGH);
    delay(500);
    myServo.write(100);
    delay(500);
    digitalWrite(redRelay,LOW);
    digitalWrite(greenRelay,LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(blueRelay, HIGH);
    delay(150);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(blueRelay, HIGH);
    delay(150);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(blueRelay, HIGH);

    delay(300);
    digitalWrite(redRelay,LOW);
    digitalWrite(greenRelay,LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(150);
    digitalWrite(redRelay,LOW);
    digitalWrite(greenRelay,LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(150);
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(150);
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
     delay(150);
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    delay(150);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
}

void believerpt4() {
    unsigned long startTime = millis(); // Record the start time
    while (millis() - startTime < 5000) { // Run for 20 seconds
    if (millis() - startTime >= 5000) return; 
    delay(500);
    myServo.write(78);
    digitalWrite(greenRelay,LOW);
    delay(150);
    myServo.write(85);
    digitalWrite(greenRelay, HIGH);
    delay(150);
    myServo.write(92);
    digitalWrite(greenRelay, LOW);
    delay(150);
    myServo.write(100);
    digitalWrite(greenRelay, HIGH);
    if (millis() - startTime >= 5000) return;
    
        // Move Servo from 100 back to 70
        for (int i = 0; i < 2; i++) {
            delay(1000);
            myServo.write(70);
            digitalWrite(waterRelay, LOW);
            digitalWrite(blueRelay, LOW);
            delay(500);
            myServo.write(78);
            digitalWrite(blueRelay,HIGH);
            delay(150);
            myServo.write(85);
            digitalWrite(blueRelay, LOW);
            delay(150);
            myServo.write(92); 
            digitalWrite(blueRelay, HIGH);
            delay(150);
            myServo.write(100);
            digitalWrite(waterRelay, HIGH);
            digitalWrite(redRelay, HIGH);
            digitalWrite(blueRelay, LOW);
            if (millis() - startTime >= 5000) return;
        }
        delay(1000);
        digitalWrite(waterRelay, LOW);
        digitalWrite(blueRelay, HIGH);
        digitalWrite(redRelay, LOW);
        delay(1000);
        myServo.write(70);
        
        if (millis() - startTime >= 5000) return;
    }
}
// Function to toggle LEDs correctly
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

void hbdpt2() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 33000) { // Run for 20 seconds
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 95; angle += 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(300);

            if (millis() - startTime >= 33000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 75; angle -= 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(300);

            if (millis() - startTime >= 25000) return; // Stop after 20 sec
        }
    }
}

void hbdpt3() {
  for (int angle = 70; angle <= 100; angle += 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(520);

        }
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, LOW);
        delay(1000);
        digitalWrite(redRelay, HIGH);
        delay(1000);
        digitalWrite(waterRelay,HIGH);
        digitalWrite(greenRelay,HIGH);
        delay(1000);
        digitalWrite(blueRelay, HIGH);
        delay(1000);
        myServo.write(70);
        digitalWrite(waterRelay, LOW);
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay,LOW);
        digitalWrite(blueRelay, LOW);
        delay(20000);
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, HIGH);
        digitalWrite(blueRelay, HIGH);
}