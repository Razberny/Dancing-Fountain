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
const int redRelay = 6;
const int greenRelay = 7;
const int blueRelay = 8;

// Water relay pin
const int waterRelay = 9;


// Relay states
bool redState = false;
bool greenState = false;
bool blueState = false;
bool waterState = false;

// Sound sensor state
bool soundSensorState = false;
bool HappyBirthdayState = false;
bool HighWayToHellState = false;
bool BelieverState = false;
bool BadRomanceState = false;
bool FireworkState = false;


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
  myServo.attach(10); // Servo on pin 9
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
      HappyBirthdayState = false;
  }
  if(HighWayToHellState){
      highwaytohell();
      HighWayToHellState = false;
  }
  if(BelieverState){
      believer();
      BelieverState = false;
  }
   if(BadRomanceState){
      badromance();
      BadRomanceState = false;
  }
  if(FireworkState){
      firework();
      FireworkState = false;
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
  else if (command == "highwaytohell") {
    HighWayToHellState = !HighWayToHellState;
    Serial.println(HighWayToHellState ? "HighWayToHell ACTIVATED" : "HighWayToHell DEACTIVATED");
  }
  else if (command == "believer") {
    BelieverState = !BelieverState;
    Serial.println(BelieverState ? "Believer ACTIVATED" : "Believer DEACTIVATED");
  }
  else if (command == "badromance") {
    BadRomanceState = !BadRomanceState;
    Serial.println(BadRomanceState ? "BadRomance ACTIVATED" : "BadRomance DEACTIVATED");
  }
  else if (command == "firework"){
    FireworkState = !FireworkState;
    Serial.println(FireworkState ? "Firework ACTIVATED " : "Firework DEACTIVATED");
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
            toggleLEDsredblueR();
            delay(500);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }
        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 70; angle -= 15) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDsredblueR();
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

void toggleLEDsredblueR() {
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
void firework() {
    fireworkpt1();
    fireworkpt2();
    fireworkpt3();
    fireworkpt4();
    fireworkpt5();
}

void fireworkpt1() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 8000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 99; angle += 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 8000) return; // Stop after 20 sec
        }

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
    }
  }

void fireworkpt2() {
 unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 29000) { // Run for 20 seconds
    myServo.write(100);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    digitalWrite(redRelay, HIGH);
    delay(500);
    myServo.write(92);
    digitalWrite(redRelay, LOW);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, HIGH);
    delay(200);
    myServo.write(84);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, HIGH);
    delay(450);
    myServo.write(78);
    digitalWrite(redRelay, HIGH);
    digitalWrite(greenRelay, HIGH);
    digitalWrite(blueRelay, LOW);    
    delay(250);
    myServo.write(70);
    digitalWrite(greenRelay, LOW);
    digitalWrite(blueRelay, LOW);
    digitalWrite(redRelay, LOW);
    delay(500);
            if (millis() - startTime >= 29000) return; // Stop after 20 sec
        }
    }
  

void fireworkpt3() {
    unsigned long startTime = millis(); // Record the start time

    while (millis() - startTime < 30000) { // Run for 20 seconds
    digitalWrite(waterRelay, LOW);    
        // Move Servo from 70 to 100
        for (int angle = 70; angle <= 99; angle += 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 30000) return; // Stop after 20 sec
        }

        // Move Servo from 100 back to 70
        for (int angle = 100; angle >= 71; angle -= 1) {
            myServo.write(angle);
            Serial.print("Servo Angle: ");
            Serial.println(angle);

            // LED sequence
            toggleLEDs4();
            delay(150);

            if (millis() - startTime >= 30000) return; // Stop after 20 sec
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