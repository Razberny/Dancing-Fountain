#include <Servo.h>

Servo myServo;  // Create servo object
const int redRelay = 4;
const int greenRelay = 5;
const int blueRelay = 6;

// Water relay pin
const int waterRelay = 8;

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
  badromance();
  delay(20000);
}


void badromance() {
    digitalWrite(waterRelay, LOW);
    badromancept1();
    raraslow();
    rarafast();
    badromancept2();
    iwantyourlove();
    delay(4000);
    badromancept3();
    delay(250);
    iwantyourlove2();
    delay(4000);
    badromancept4();
    badromancept5();
    badromancept1();
    raraslow();
    myServo.write(70);
    digitalWrite(waterRelay, HIGH);
    delay(2000);
    digitalWrite(redRelay, HIGH);
}



void badromancept1() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 17000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 71; angle -= 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 17000) return; // Stop after 20 sec
        }

        for (int angle = 70; angle <= 99; angle += 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 17000) return; // Stop after 20 sec
        }
    }
  }

void raraslow(){
  unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 8000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
    digitalWrite(redRelay, LOW);
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 100; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredblue();
            delay(500);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 70; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredblue();
            delay(500);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }   
    }
}

void rarafast() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 8000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
    digitalWrite(redRelay, LOW);
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 100; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredorange();
            delay(500);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 70; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredorange();
            delay(500);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }   
    }

}

void iwantyourlove(){
    myServo.write(70);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(1200);
    myServo.write(80);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(250);
    myServo.write(90);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(250);
    myServo.write(100);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(1000);
    myServo.write(70);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
}
void iwantyourlove2(){
    myServo.write(70);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(1200);
    myServo.write(80);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(250);
    myServo.write(90);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(250);
    myServo.write(100);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(250);
    digitalWrite(waterRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(800);
    myServo.write(70);
    digitalWrite(waterRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(200);
}

void badromancept2() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 9000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 9000) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 9000) return; // Stop after 20 sec
        }

        
    }
  }

void badromancept3(){
  unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 8500) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 8500) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 8500) return; // Stop after 20 sec
        }

        
    }
}

void badromancept4() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 8000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 71; angle -= 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }

        for (int angle = 70; angle <= 99; angle += 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }
    }
  }

void badromancept5() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 15000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 15000) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(500);

            if (millis() - startTime >= 15000) return; // Stop after 20 sec
        }

        
    }
  }

void fireworkpt4() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 9000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 85; angle += 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(480);

            if (millis() - startTime >= 9000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 85; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4bicolors();
            delay(480);

            if (millis() - startTime >= 9000) return; // Stop after 20 sec
        }
    }
  }

void fireworkpt5() {
      delay(300);
      myServo.write(70);
      digitalWrite(redRelay, LOW);
      digitalWrite(greenRelay, HIGH);
      digitalWrite(blueRelay, HIGH);
      delay(700);
      digitalWrite(redRelay, HIGH);
      digitalWrite(greenRelay, LOW);
      digitalWrite(blueRelay, HIGH);
      delay(700);
      digitalWrite(redRelay, HIGH);
      digitalWrite(greenRelay, HIGH);
      digitalWrite(blueRelay, LOW);
      delay(2400);
      digitalWrite(redRelay, LOW);
      digitalWrite(greenRelay, LOW);
      digitalWrite(blueRelay, HIGH);
      delay(700);
      digitalWrite(redRelay, LOW);
      digitalWrite(greenRelay, HIGH);
      digitalWrite(blueRelay, LOW);
      delay(700);
      digitalWrite(redRelay, LOW);
      digitalWrite(greenRelay, LOW);
      digitalWrite(blueRelay, LOW);
      delay(3000);
      digitalWrite(greenRelay, HIGH);
      digitalWrite(blueRelay, HIGH);
      digitalWrite(redRelay, HIGH);
      digitalWrite(waterRelay, HIGH);
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

void toggleLEDsredorange() {
    static int ledState = 0;

    // Turn off all LEDs first
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, LOW);
    

    // Turn on one LED at a time in sequence
    if (ledState == 0) {
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, LOW);
    } else if (ledState == 1) {
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, HIGH);
    }
    // Cycle through LEDs
    ledState = (ledState + 1) % 2;
}

void toggleLEDsredblue() {
    static int ledState = 0;

    // Turn off all LEDs first
    digitalWrite(redRelay, LOW);
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

void toggleLEDs4() {
    static int ledState = 0;

    if (ledState == 0) {
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, HIGH);
        digitalWrite(blueRelay, HIGH);
    } else if (ledState == 1) {
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, HIGH);
    } else if (ledState == 2) {
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, HIGH);
        digitalWrite(blueRelay, LOW);
    } else if (ledState == 3) {
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, HIGH);
    }

    // Cycle through LEDs
    ledState = (ledState + 1) % 4;
}

void toggleLEDs4bicolors() {
    static int ledState = 0;

    if (ledState == 0) {
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, HIGH);
    } else if (ledState == 1) {
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, LOW);
    } else if (ledState == 2) {
        digitalWrite(redRelay, LOW);
        digitalWrite(greenRelay, HIGH);
        digitalWrite(blueRelay, LOW);
    } else if (ledState == 3) {
        digitalWrite(redRelay, HIGH);
        digitalWrite(greenRelay, LOW);
        digitalWrite(blueRelay, LOW);
    }

    // Cycle through LEDs
    ledState = (ledState + 1) % 4;
}