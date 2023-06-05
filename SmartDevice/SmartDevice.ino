// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// IR Remote
#include <IRremote.h>
#define IR_INPUT_PIN    2
IRrecv irrecv(IR_INPUT_PIN);
decode_results results;

// Traffic Lights - LED Outputs
#define ledRed A0
#define ledYellow A1
#define ledGreen A2

// Crash Sensor / Button
#define crashSensor 2

// DC Motor
int E1 = 6;
int M1 = 7;

// Servo
#include <Servo.h>
Servo myservo;

// SD Card - Confirm Pin
#define SDpin 10 // 10 on a UNO board, 53 on a mega board

// Control Variables
int lastCrashSensorValue = 0;
boolean motorOn = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDpin)) {
    Serial.println("Initialization failed!");
    while (1)
      ;
  }

  // Crash Sensor / Button
  pinMode(crashSensor, INPUT);

  pinMode(M1, OUTPUT);

  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("Initialization done.");
  logEvent("System Initialisation...");
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
   and toggles it accordingly.
   @params none
   @return none
*/

void stopAndStartCar() {
  int crashSensorValue = digitalRead(crashSensor);
  crashSensorValue = 1 - crashSensorValue; // Invert value, default is 0 - On, 1 - Off

  if (crashSensorValue == 1 && lastCrashSensorValue == 0) { // Catch the sensor value on the rising edge
    motorOn = !motorOn;
  }

//  logEvent(motorOn ? "Motor has been turned on" : "Motor has been turned off");

  lastCrashSensorValue = crashSensorValue;
  
  digitalWrite(M1, HIGH);
  analogWrite(E1, 255-motorOn*255);
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
   @return true when the distance is lower than the set threshold.
*/

boolean sonarWithinThreshold() {
  return true; // TBA Logic
}

/*
   Using input from the line sensor, determine whether or not the car is on a line. If it has been on a solid white line for a certain amount of time, plays the buzzer,
   and toggles the traffic light accordingly. GREEN = not on white line, RED = currently on white line, AMBER = have been on white line recently.
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
