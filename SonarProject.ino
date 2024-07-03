// Necessary Library Imports
#include <Servo.h>

// Local Declarations
Servo myservo;
const int trigPin = 7;
const int echoPin = 8;
int pos = 0;
long duration;

// Initially Run Code Function
void setup() 
{
  // Open the serial port to write the sonar data to
  Serial.begin (9600);

  // Match the servo command wire to arduino pin 9
  myservo.attach (9);

  // Initialize the trigger (transmitter) pin on the ultrasonic sonar sensor to be the input
  pinMode (trigPin, OUTPUT);

  // Initialize the echo (receiver) pin on the ultrasonic sonar sensor to be the output
  pinMode (echoPin, INPUT);
}

// Function that holds code that continuously repeats
void loop() 
{

  // Local Variable declarations
  long duration, inches, cm;

  // For each angle the servo can allign itself to, out of 180
  for (pos = 0; pos <= 180; pos += 1)
  {
    // Tell the servo to move to the current positional data
    myservo.write (pos);

    // Call functions to translate the signal duration from the sensor into an integer
    duration = calculateDistance ( );

    // Calculate the distance to target in inches
    inches = microsecondsToInches (duration);

    // Calculate the distance to target in centimeters 
    cm = microsecondsToCentimeters (duration);

    // Print the inches to target, centimeters to target, and potentiometer degree target was recorded at to the serial port
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm, ");
    Serial.print (pos);
    Serial.print ("°");
    Serial.println();

    // Amount of time in between each servo angle rotation (in microseconds)
    delay (30);
  }

  // Repeat the previous logic in the other direction
  for (pos = 180; pos >= 0; pos -= 1)
  {
    myservo.write (pos);

    duration = calculateDistance ( );
    inches = microsecondsToInches (duration);
    cm = microsecondsToCentimeters (duration);

    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm, ");
    Serial.print (pos);
    Serial.print ("°");
    Serial.println();

    delay (30);
  }

}

// Function to convert the signal duration received from the sonar sensor into an integer to be used in further calculations
int calculateDistance(){ 
  
  // Tell the trigger pin to wait without power
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);

  // Record the data the sensor receives while on high power for ten microseconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);

  // Turn the sensor back off
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the signal wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH); 

  // Returns signal travel time
  return duration;
}


// Function to convert the signal travel time into inches
long microsecondsToInches (long microseconds)
{
  // Return the distance to target in inches
  return microseconds / 74 / 2;
}

// Function to convert the signal travel time to centimeters
long microsecondsToCentimeters (long microseconds)
{
  // Return distance to target in centimeters
  return microseconds / 29 / 2;
}