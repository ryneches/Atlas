#include <Atlas.h>
#include <SoftwareSerial.h>

Atlas A = Atlas();

void setup(){}

void loop(){
    A.on();
    A.off();
    A.on();
    Serial.println( A.read(23.23) );
}
