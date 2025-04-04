#include <AudioAnalyzer.h>
#include <Servo.h>

// Analyzer Setup
Analyzer Audio = Analyzer(4, 5, A5); // Strobe -> 4, RST -> 5, Analog -> A5
int FreqVal[7]; // Store frequency band values

// Servo Setup
Servo myServo;
int currentServoPos = 100;  // Start position
const int servoMaxStep = 1; // Max movement per change

// Relay Pins (LEDs and Water Pump)
const int redRelay = 4;
const int greenRelay = 5;
const int blueRelay = 6;
const int waterRelay = 8;

// Thresholds for Activating Effects
const int lowThreshold = 300;
const int midThreshold = 600;  // Low intensity activation threshold
const int highThreshold = 800; // High intensity activation threshold

void setup() {
  Serial.begin(57600);
  Audio.Init(); // Initialize Audio Analyzer
  
  // Setup Servo
  myServo.attach(9);
  myServo.write(currentServoPos); // Set initial position
  
  // Setup Relays as Outputs
  pinMode(redRelay, OUTPUT);
  pinMode(greenRelay, OUTPUT);
  pinMode(blueRelay, OUTPUT);
  pinMode(waterRelay, OUTPUT);
  
  // Turn Everything Off Initially
  digitalWrite(redRelay, LOW);
  digitalWrite(greenRelay, LOW);
  digitalWrite(blueRelay, LOW);
  digitalWrite(waterRelay, LOW);
  
  Serial.println("🎵 Sound-Activated Fountain System Initialized 🎵");
}

void loop() {
  Audio.ReadFreq(FreqVal); // Read frequency bands
  
  // Process and display outputs
  handleEffects(FreqVal);
  
  delay(50); // Short delay for smoother transitions
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
