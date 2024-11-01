// Pin definitions for LEDs
const int redLed_1 = 2;
const int greenLed_1 = 4;
const int blueLed_1 = 8;
const int yellowLed_1 = 10;
const int redLed_2 = 11;
const int greenLed_2 = 12;
const int redLed_3 = 13;

// Pin definitions for Buzzer and Ultrasonic Sensor
const int buzzer = 3;
const int Trig = 6;
const int Echo = 5;

// Proximity distance thresholds (in centimeters)
const int proximity1 = 100;  // Red LED 1
const int proximity2 = 80;   // Green LED 1
const int proximity3 = 60;   // Blue LED 1
const int proximity4 = 40;   // Yellow LED 1
const int proximity5 = 20;   // Red LED 2
const int proximity6 = 10;   // Green LED 2
const int proximity7 = 5;    // Red LED 3 and buzzer

void setup() {
  // Initialize LED, buzzer, and ultrasonic sensor pins
  pinMode(redLed_1, OUTPUT);
  pinMode(greenLed_1, OUTPUT);
  pinMode(blueLed_1, OUTPUT);
  pinMode(yellowLed_1, OUTPUT);
  pinMode(redLed_2, OUTPUT);
  pinMode(greenLed_2, OUTPUT);
  pinMode(redLed_3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

long getDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // Calculate distance based on echo time
  long duration = pulseIn(Echo, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void activateLED(int ledPin) {
  // Turn on the specified LED
  digitalWrite(ledPin, HIGH);
}

void deactivateAll() {
  // Turn off all LEDs and buzzer
  digitalWrite(redLed_1, LOW);
  digitalWrite(greenLed_1, LOW);
  digitalWrite(blueLed_1, LOW);
  digitalWrite(yellowLed_1, LOW);
  digitalWrite(redLed_2, LOW);
  digitalWrite(greenLed_2, LOW);
  digitalWrite(redLed_3, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  long distance = getDistance();

  // Reset all LEDs and buzzer
  deactivateAll();

  // Check proximity levels to light up LEDs cumulatively
  if (distance <= proximity7) {
    activateLED(redLed_3);
    digitalWrite(buzzer, HIGH);
  }
  if (distance <= proximity6) {
    activateLED(greenLed_2);
  }
  if (distance <= proximity5) {
    activateLED(redLed_2);
  }
  if (distance <= proximity4) {
    activateLED(yellowLed_1);
  }
  if (distance <= proximity3) {
    activateLED(blueLed_1);
  }
  if (distance <= proximity2) {
    activateLED(greenLed_1);
  }
  if (distance <= proximity1) {
    activateLED(redLed_1);
  }

  delay(100);  // Add delay to control sensor polling rate
}
