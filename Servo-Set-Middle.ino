#include <Servo.h>

#define SERVO_DATA_PIN 3

Servo sonicservo;

void setup(){
    sonicservo.attach(SERVO_DATA_PIN);
    sonicservo.write(90);
}

void loop(){
    Serial.println("Callibration finished!");
}
