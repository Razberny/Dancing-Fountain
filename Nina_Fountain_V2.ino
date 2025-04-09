#include <AudioAnalyzer.h>
#include <Servo.h>            // Include Servo library
#include <SoftwareSerial.h>   // Include SoftwareSerial for Bluetooth

// Define Bluetooth module pins
SoftwareSerial bluetooth(2, 3); // RX, TX
Analyzer Audio = Analyzer(4, 5, A5); // Strobe -> 4, RST -> 5, Analog -> A5
int FreqVal[7]; // Store frequency band values

// Servo Setup
Servo myServo;
int currentServoPos = 100;  // Start position
const int servoMaxStep = 1; // Max movement per change

// Relay pins
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

// Sound sensor state
bool soundSensorState = false;
bool HappyBirthdayState = false;
// Sound threshold (adjust as needed)
const int lowThreshold = 300;
const int midThreshold = 600;  
const int highThreshold = 800;  

// Command buffer
String command = "";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  bluetooth.begin(9600);
  Audio.Init();

  // Initialize servo
  myServo.attach(9); // Servo on pin 9
  myServo.write(90); // Initial position (90 degrees)

  // Set up relay pins
  pinMode(redRelay, OUTPUT);
  pinMode(greenRelay, OUTPUT);
  pinMode(blueRelay, OUTPUT);
  pinMode(waterRelay, OUTPUT);

  // Set up sound sensor pins

  // Turn off all relays initially
  digitalWrite(redRelay, LOW);
  digitalWrite(greenRelay, LOW);
  digitalWrite(blueRelay, LOW);
  digitalWrite(waterRelay, LOW);


  Serial.println("System Ready");
}

void loop() {
  // Read data from Bluetooth
  while (bluetooth.available()) {
    char incomingChar = bluetooth.read(); // Read one character
    if (incomingChar == '\n') { // End of command
      handleCommand(command); // Process the command
      command = ""; // Clear the command buffer
    } else {
      command += incomingChar; // Append character to the command
    }
  }

  // Check sound intensity if sound sensor is activated
  if (soundSensorState) {
    Audio.ReadFreq(FreqVal); // Read frequency bands
  
  // Process and display outputs
    handleEffects(FreqVal);

    delay(50); // Adjust delay for better readability on the serial monitor
  }

  if(HappyBirthdayState){
      happybirthday();
  }
}



void handleCommand(String command) {
  command.trim(); // Remove any extra spaces or newlines

  // Servo Motor Control
  if (command.toInt() >= 1 && command.toInt() <= 180) {
    int servoPosition = command.toInt();
    myServo.write(servoPosition);
    Serial.print("Servo moved to: ");
    Serial.println(servoPosition);
  }

  // Relay Control
  else if (command == "red") {
    redState = !redState;
    digitalWrite(redRelay, redState ? HIGH : LOW);
    Serial.println(redState ? "Red LED ON" : "Red LED OFF");
  } 
  else if (command == "green") {
    greenState = !greenState;
    digitalWrite(greenRelay, greenState ? HIGH : LOW);
    Serial.println(greenState ? "Green LED ON" : "Green LED OFF");
  } 
  else if (command == "blue") {
    blueState = !blueState;
    digitalWrite(blueRelay, blueState ? HIGH : LOW);
    Serial.println(blueState ? "Blue LED ON" : "Blue LED OFF");
  } 

  // Water Control
  else if (command == "water") {
    waterState = !waterState;
    digitalWrite(waterRelay, waterState ? HIGH : LOW);
    Serial.println(waterState ? "Water Relay ON" : "Water Relay OFF");
  }

  // Sound Sensor Control
  else if (command == "sound") {
    soundSensorState = !soundSensorState;
    Serial.println(soundSensorState ? "Sound Sensor ACTIVATED" : "Sound Sensor DEACTIVATED");
  }

   else if (command == "happybirthday") {
    HappyBirthdayState = !HappyBirthdayState;
    Serial.println(HappyBirthdayState ? "HappyBirthday ACTIVATED" : "HappyBirthday DEACTIVATED");
  }
  // Invalid command
  else {
    Serial.println("Invalid Command");
  }
}

void handleEffects(int FreqVal[]) {
  // Extract relevant frequency bands
  int deepbass = FreqVal[0];
  int bass = FreqVal[1];    
  int semibass = FreqVal[2];   
  int mid = FreqVal[3];
  int semitreble = FreqVal[4];      
  int treble = FreqVal[5];   
  int ultra = FreqVal[6];

  // Display frequency intensities in Serial Monitor
  Serial.print("Deep Bass: "); Serial.print(deepbass);
  Serial.print("  | Bass: "); Serial.print(bass);
  Serial.print("  | Semibass: "); Serial.println(semibass);
  Serial.print("  | Mid: "); Serial.print(mid);
  Serial.print("  | Semitreble: "); Serial.print(semitreble);
  Serial.print("  | treble: "); Serial.println(treble);
  
  // LED and Water Control (Inverted Logic)
  bool redState = !(bass > lowThreshold || semibass > lowThreshold);
  bool greenState = !(ultra > midThreshold && mid > highThreshold);
  bool blueState = !(mid > midThreshold);
  bool waterState = !(semitreble > highThreshold && treble > highThreshold);
  
  digitalWrite(redRelay, redState);
  digitalWrite(greenRelay, greenState);
  digitalWrite(blueRelay, blueState);
  digitalWrite(waterRelay, waterState);
  
  // Print LED and Water States
  Serial.print(!redState ? "🔴 Red LED: ON  " : "⚫ Red LED: OFF  ");
  Serial.print(!greenState ? "🟢 Green LED: ON  " : "⚫ Green LED: OFF  ");
  Serial.print(!blueState ? "🔵 Blue LED: ON  " : "⚫ Blue LED: OFF  ");
  Serial.println(!waterState ? "💦 Water Pump: ON" : "🚫 Water Pump: OFF");
  
  // Servo Motion - Controlled 15° Steps
  int totalSound = bass + mid + treble; // Combine intensities
  int servoChange = map(totalSound, lowThreshold, highThreshold * 3, -servoMaxStep, servoMaxStep);
  servoChange = constrain(servoChange, -servoMaxStep, servoMaxStep); // Limit to ±15 degrees

  int newServoPos = currentServoPos - servoChange; // Change direction to move from 100 to 70
  newServoPos = constrain(newServoPos, 70, 100); // Prevent exceeding servo limits

  myServo.write(newServoPos);
  currentServoPos = newServoPos; // Update current position

  
  Serial.print("🔄 Servo Angle: ");
  Serial.print(currentServoPos);
  Serial.println("°");
  
  Serial.println("--------------------------------------");
}

void happybirthday() {
    digitalWrite(waterRelay, LOW);
    hbdpt1();  // Run the function for 20 seconds
    hbdpt2();
    hbdpt3();
}
// Function to move servo and toggle LEDs
void hbdpt1() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 25000) { // Run for 20 seconds
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 95; angle += 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(520);

            if (millis() - startTime >= 25000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 75; angle -= 5) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs();
            delay(520);

            if (millis() - startTime >= 25000) return; // Stop after 20 sec
        }
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