// Necessary Library Imports
#include <Servo.h>

// Class handling the logic regarding the ultrasonic sensor
class Sensor 
{
  public:
    // Initializing data pins
    const int trigPin;
    const int echoPin;

    // Constructor function to initialize trigger and echo pins
    Sensor(int trigPin, int echoPin) : trigPin(trigPin), echoPin(echoPin) {}
};

// Class handling sonar logic and processing
class Sonar 
{
  public:
    // Function to calculate distance to target using the sensor
    static long calculateDistance(const Sensor& sensor) 
    {
      // Set trigger pin to off
      digitalWrite(sensor.trigPin, LOW);

      // Delay for stability
      delayMicroseconds(2);

      // Turn on the trigger pin
      digitalWrite(sensor.trigPin, HIGH);

      // Let trigger pin sing for 10 microseconds
      delayMicroseconds(10);

      // Turn the trigger pin back off
      digitalWrite(sensor.trigPin, LOW);

      // Record the amount of time it took the echo pin to hear the trigger pins song
      long duration = pulseIn(sensor.echoPin, HIGH);

      // Return that trvel time
      return duration;
    }

    // Function to convert microseconds to inches
    static long microsecondsToInches(long microseconds) 
    {
        // Return distance to target in inches
        return microseconds / 74 / 2;
    }

    // Function to convert microseconds to centimeters
    static long microsecondsToCentimeters(long microseconds) 
    {
        // Return distance to target in centimeters
        return microseconds / 29 / 2;
    }
};

// Create a Servo object to control the servo motor
Servo myservo;

// Define trigger (transmition) and echo (receiver) pins on the ultrasonic sensor
const int trigPin = 7;
const int echoPin = 8;

// Initiate the sensor with the defined pins
Sensor sensor(trigPin, echoPin);

// Function that initiates upon program launch
void setup() 
{
    // Initialize serial moniter communication
    Serial.begin(9600);

    // Attach servo to arduino pin 9
    myservo.attach(9);

    // Set the trigger pin to be the output
    pinMode(sensor.trigPin, OUTPUT);

    // Set the echo pin to be the input
    pinMode(sensor.echoPin, INPUT);
}

// Main function runs repeatedly
void loop() 
{
    // Declare local variables
    long duration, inches, cm;

    // Sweep the servo from 0 to 180 degrees counter-clockwise
    // For each angle the the servo can move to
    for (int pos = 0; pos <= 180; pos += 1) 
    {
        // Move the servo to that angle
        myservo.write(pos);

        // Allow time for servo to reach position
        delay(30);

        // Calculate distance of target using the sensor
        duration = Sonar::calculateDistance(sensor);

        // Convert the signal transmission time to inches
        inches = Sonar::microsecondsToInches(duration);

        // Convert the signal transmission time to centimeters
        cm = Sonar::microsecondsToCentimeters(duration);

        // Print:
        // Inches to target,
        Serial.print(inches);
        Serial.print("in, ");

        // Centimeters to target
        Serial.print(cm);
        Serial.print("cm, ");

        // Degree of the angle of which the recording was taken
        Serial.print(pos);
        Serial.print("°");
        Serial.println();
    }

    // Repeat logic for sweeping the servo back to 0 degrees, clockwise
    for (int pos = 180; pos >= 0; pos -= 1) 
    {
        myservo.write(pos);
        delay(30);
        duration = Sonar::calculateDistance(sensor);
        inches = Sonar::microsecondsToInches(duration);
        cm = Sonar::microsecondsToCentimeters(duration);

        Serial.print(inches);
        Serial.print("in, ");
        Serial.print(cm);
        Serial.print("cm, ");
        Serial.print(pos);
        Serial.print("°");
        Serial.println();
    }

    // Debug info
    Serial.println("Completed one full sweep.");
    // Small delay after a full sweep to observe behavior
    delay(500); 
}