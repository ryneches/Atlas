#include <Atlas.h>
#include <SoftwareSerial.h>
#include <Serial.h>

Atlas A = Atlas();

void setup(){}

void loop(){
    A.on();
    A.off();
    A.on();
    Serial.println( A.version() );
}
