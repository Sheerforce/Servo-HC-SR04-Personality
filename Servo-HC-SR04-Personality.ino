#include <Servo.h> // Include the Servo library
#include <NewPing.h> // Include the NewPing library

#define SERVO_DATA_PIN 3 // Create a variable for the Servo Data pin
#define ECHO_PIN 5 // Create a variable for the Ultrasonic Echo pin
#define TRIG_PIN 6 // Create a variable for the Ultrasonic Trigger pin
#define MAX_DISTANCE 400 // Create a variable for the Max Distance (in cm) that the Ultrasonic Sensor looks for
#define MAX_DISTANCE_IN MAX_DISTANCE*0.39370 // Convert the Max Distance to inches (not necessary)
#define testDistance 20 // Create a variable for the amount (in degrees) that the Servo will travel to test the distance 
#define moveDistance 10 // Create a variable for the amount (in degrees) that the Servo will actually move upon receiving the direction to move
#define testDelay 100 // A variable that sets the delay for certain processes in the testSurroundings function

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Create a Sonar object for the Ultrasonic Sensor
Servo sonicservo; // Create a Servo object called sonicservo for the servo

int leftReading, rightReading, i, in, cm, uS, pos = 90; // Create some variables

void setup() { // Start the setup function
    Serial.begin(9600); // Initialize a serial connection with the computer
    sonicservo.attach(SERVO_DATA_PIN); // Attach the sonicservo object to the servo data pin on the Arduino
    sonicservo.write(90); // Center the servo
} // End the setup function

void loop() { // Start the loop function
    delay(30); // Pause the program for 30 ms to wait to receive the next position
    int cm = sonar.ping() / US_ROUNDTRIP_CM; // Use the sonar.ping() function to get the time in ms that it takes for the sensor to send out and receive back an ultrasonic sound, and then devide that by the time in ms that it takes for an ultrasonic sound to travel 1cm (round trip) to get the distance in cm 
    int in = cm * 0.39370; // Convert the cm value to inches (not neccessary) 
    testSurroundings(); // Call the testSurroundings() function (seen below)
    Serial.println(pos); // Write the current position (in degrees) to the serial monitor for debugging purposes
}

void testSurroundings() { // Start the testSurroundings function
    sonicservo.write(pos-testDistance); // Set the servo to it's current position minus the distance that has been set for it to test
    delay(testDelay); // Let the servo compute the line above
    int leftReading = sonar.ping()/US_ROUNDTRIP_CM; // Take an ultrasonic reading of it's current position
    delay(testDelay/2); // Wait for the ultrasonic sensor
    sonicservo.write(pos+testDistance); // Set the servo to it's current position plus the distance that has been set for it to test
    delay(testDelay); //Let the servo compute the line above
    int rightReading = sonar.ping()/US_ROUNDTRIP_CM; // Take an ultrasonic reading of it's current position
    delay(testDelay/2); // Wait for the ultrasonic sensor
    sonicservo.write(pos); // Write the servo back to it's initial position
    if(leftReading < rightReading && pos > 0) { 
        pos -= moveDistance;
    }
    else if(rightReading < leftReading && pos < 180) {
        pos += moveDistance;
    }
    /*
    The above if/else block checks which reading, the left one or the right one has the closer position in cm
    */
}
