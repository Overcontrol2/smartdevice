// SD Card Module
#include <SPI.h>
#include <SD.h>

// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

// SD Card - Confirm Pin
#define SDpin 53 // 10 on a UNO board, 53 on a mega board

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);  // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card initialisation
  Serial.print("Initializing SD card...");
  if (!SD.begin(SDpin)) {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  stopAndStartCar();
  handleEngineSpeed();
  toggleLightsAndBuzzerIfOnLine();
  adjustCarSeats();
  

  delay(250); // Allow time for Arduino to 'cool down'
}

/*
 * Using the current ignition state, and input from the key (button), Detects when the key (button) is pressed and turns on the car (motor) accordingly.determines whether or not the car engine should be on
 * and toggles it accordingly.
 * @params none
 * @return none
 */

void stopAndStartCar() {
  
}

/* 
 *  Gathering input from sonarWithinThreshold(), determines the engine speed. For example, if an object is too close, 
 *  the engine will drastically slow down to the point of stopping. Also gathers input from the potentiometer to determine the speed
 *  while the sensor is not detecting something.
 *  The use of a sonar sensor here is effective in this use case, as variations in light do not affect accuracy. 
 *  However, the hardware in use may be inaccurate. The use of a higher quality sensor would improve accuracy and overall performance.
 * @params none
 * @return none
 */

void handleEngineSpeed() {
  boolean withinDistanceThreshold = sonarWithinThreshold(); // Receive processed input from sonar sensor
}

/*
 * Processes the input from the sonar sensor into a boolean, using a constant threshold with padding to ensure that there is no 'stuttering'.
 * @params none
 * @return true when the distance is lower than the set threshold.
 */

boolean sonarWithinThreshold() {
  return true; // TBA Logic
}

/*
 * Using input from the line sensor, determine whether or not the car is on a line. If it has been on a solid white line for a certain amount of time, plays the buzzer,
 * and toggles the traffic light accordingly. GREEN = not on white line, RED = currently on white line, AMBER = have been on white line recently.
 * Uses the time since the last white line to reset the variable, buzzer and lights accordingly.
 * @params none
 * @return none
 */

void toggleBuzzerAndLightsIfOnLine() {
  
}

/*
 * Using input from an infrared remote control, operates the servo, emulating a car seat adjusting.
 * @params none
 * @return none
 */

void adjustCarSeats() {
  
}
