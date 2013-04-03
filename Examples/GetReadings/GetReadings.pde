#include <Atlas.h>
#include <SoftwareSerial.h>

Atlas A = Atlas();

void setup(){
  A.on();
  A.off();
  A.on();
  A.single();
  Serial.begin( 9600 );
}

void loop(){
  //Serial.println( "Getting some data..." );
  Serial.println( A.read(23.23) );
  //Serial.println( A.version() );
  delay(50);
}
