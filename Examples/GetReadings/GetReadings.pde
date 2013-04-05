#include <Atlas.h>
#include <SoftwareSerial.h>

Atlas A = Atlas();

void setup(){
    Serial.begin( 9600 );
    A.single();
    A.on();
    delay(1000);
    A.off();
    delay(1000);
    A.on();
}

void loop(){
    Serial.println( A.read(23.32) );
    delay(1000);
}
