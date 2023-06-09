// SD Card Module
#include <SPI.h>
#include <SD.h>
const int SDpin = 10; // 10 on a UNO board, 53 on a mega board

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// IR Remote
#include <IRremote.h>
const int IR_INPUT_PIN = 2;
IRrecv irrecv(IR_INPUT_PIN);
decode_results results;

// Traffic Lights - LED Outputs
const int ledRed = A0;
const int ledYellow = A1;
const int ledGreen = A2;

// Crash Sensor / Button
const int crashSensor = 2;

// DC Motor

const int E1 = 6;
const int M1 = 7;

// Servo
#include <Servo.h>
Servo myservo;

// Control Variables
bool motorOn = false;


/*  An unsigned int does not have a bit dedicated to whether or not a number is positive or negative. 
 *  This effectively doubles the maximum value of the variable, at the cost of losing the use of negative numbers.
 *  This is perfect for storing millis, as time values in this use case are never negative. */
const unsigned int timeBetweenActivation = 2000;
unsigned int lastActivatedTime;

void setup() {
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialisation
  //  Serial.print("Initializing SD card...");
  //  if (!SD.begin(SDpin)) {
  //    Serial.println("Initialization failed!");
  //    while (1)
  //      ;
  //  }

  // Crash Sensor / Button
  pinMode(crashSensor, INPUT);

  // DC Motor
  pinMode(M1, OUTPUT);

  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("Initialization done.");
  logEvent("System initialisation...");

  // Initialise time
  lastActivatedTime = -timeBetweenActivation; // Initialise the time in a way that on setup, button is ready to activate.
}

void loop() {
  // put your main code here, to run repeatedly:
  stopAndStartCar();
  handleEngineSpeed();
  toggleBuzzerAndLightsIfOnLine();
  adjustCarSeats();

  delay(100); // Allow time for Arduino to 'cool down'
}

/*
   Using the current ignition state, and input from the key (button), Detects when the key (button) is pressed and turns on the car (motor) accordingly.determines whether or not the car engine should be on
   and toggles it accordingly. This uses a pulse from the crash sensor to determine when the state
   needs to be changed.
   @params none
   @return none
*/

void stopAndStartCar() {
  int crashSensorValue = pulseIn(crashSensor, HIGH); // Grab a rising edge pulse from the crash sensor (only when value is moving from LOW to HIGH)

  /*
     Determine how if enough time has passed since the last button press.
     Use the absolute value to account for integer overflow
  */
  if (crashSensorValue > 0 && (abs(millis() - lastActivatedTime) >= timeBetweenActivation)) {
    motorOn = !motorOn;
    lastActivatedTime = millis();


    logEvent(motorOn ? "DC Motor has been turned on" : "DC Motor has been turned off");


    digitalWrite(M1, HIGH);
    analogWrite(E1, 255 - motorOn * 255); // Invert scale of 0-255 to motor values of 0-255
  }
}

/*
   Gathering input from sonarWithinThreshold(), determines the engine speed. For example, if an object is too close,
   the engine will drastically slow down to the point of stopping. Also gathers input from the potentiometer to determine the speed
   while the sensor is not detecting something.
   The use of a sonar sensor here is effective in this use case, as variations in light do not affect accuracy.
   However, the hardware in use may be inaccurate. The use of a higher quality sensor would improve accuracy and overall performance.
   @params none
   @return none
*/

void handleEngineSpeed() {
  boolean withinDistanceThreshold = sonarWithinThreshold(); // Receive processed input from sonar sensor
}

/*
   Processes the input from the sonar sensor into a boolean, using a constant threshold with padding to ensure that there is no 'stuttering'.
   @params none
   @return boolean true when the distance is lower than the set threshold, false otherwise
*/

boolean sonarWithinThreshold() {
  return true; // TBA Logic
}

/*
   Using input from the line sensor, determine whether or not the car is on a line. If it has been on a solid white line for a certain amount of time, plays the buzzer,
   and toggles the traffic light accordingly. GREEN = not on white line, RED = currently on white line, AMBER = been on white line recently.
   Uses the time since the last white line to reset the variable, buzzer and lights accordingly.
   @params none
   @return none
*/

void toggleBuzzerAndLightsIfOnLine() {

}

/*
   Using input from an infrared remote control, operates the servo, emulating a car seat adjusting.
   @params none
   @return none
*/

void adjustCarSeats() {

}
