#include <Servo.h>            // Include Servo library
#include <SoftwareSerial.h>   // Include SoftwareSerial for Bluetooth

// Define Bluetooth module pins
SoftwareSerial bluetooth(2, 3); // RX, TX

// Servo setup
Servo myServo;

// Relay pins
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

// Sound sensor state
bool soundSensorState = false;

// Sound threshold (adjust as needed)
const int soundThreshold = 500; // Range: 0-1023 (higher values = louder sounds)

// Command buffer
String command = "";

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  bluetooth.begin(9600);

  // Initialize servo
  myServo.attach(9); // Servo on pin 9
  myServo.write(90); // Initial position (90 degrees)

  // Set up relay pins
  pinMode(redRelay, OUTPUT);
  pinMode(greenRelay, OUTPUT);
  pinMode(blueRelay, OUTPUT);
  pinMode(waterRelay, OUTPUT);

  // Set up sound sensor pins
  pinMode(soundSensorPin, OUTPUT);

  // Turn off all relays initially
  digitalWrite(redRelay, LOW);
  digitalWrite(greenRelay, LOW);
  digitalWrite(blueRelay, LOW);
  digitalWrite(waterRelay, LOW);
  digitalWrite(soundSensorPin, LOW);

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
    int soundLevel = analogRead(soundAnalogPin); // Read sound intensity
    Serial.print("Sound intensity: ");
    Serial.println(soundLevel);

    // Detect if sound level exceeds the threshold
    if (soundLevel >= soundThreshold) {
      Serial.println("Loud sound detected!");
      // Add any additional action for loud sound here
    }

    delay(1000); // Adjust delay for better readability on the serial monitor
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
    digitalWrite(soundSensorPin, soundSensorState ? HIGH : LOW);
    Serial.println(soundSensorState ? "Sound Sensor ACTIVATED" : "Sound Sensor DEACTIVATED");
  }

  // Invalid command
  else {
    Serial.println("Invalid Command");
  }
}


