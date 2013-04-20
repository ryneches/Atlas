/*

To use Atlas without a 74HC4052-based multiplexer shield, edit Atlas.h
and comment out the line
  
  #define SHIELD

This will switch to function definitions that don't need the PORTX
argument, and removes some functions and variables related to the
multiplexer, and should result in a smaller binary.

*/
#include <Atlas.h>
#include <AltSoftSerial.h>

Atlas A = Atlas();

void setup() {
  Serial.begin( 9600 );
  // get version strings for each sensor
  Serial.println( A.version() );
}

void loop() {
 // get temperature corrected readings
 Serial.println( A.read( 23.4 ) );
}
