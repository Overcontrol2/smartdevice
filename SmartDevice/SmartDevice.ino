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
  stopAndStartCar()

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
