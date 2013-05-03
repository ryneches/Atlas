#include <AltSoftSerial.h>

AltSoftSerial s;

void setup() {
    pinMode(2, OUTPUT); // set MUX pin 1
    pinMode(3, OUTPUT); // set MUX pin 2
    
    // select port 0
    //digitalWrite( 2, LOW  );
    //analogWrite(  3, 0    );
     
    // select port 1
    //digitalWrite( 2, HIGH );
    //analogWrite(  3, 0    );
 
    // select port 2
    digitalWrite( 2, LOW  );
    analogWrite(  3, 255  );
    
    // select port 3
    //digitalWrite( 2, HIGH );
    //analogWrite(  3, 255  );
 
    s.begin(38400);
    Serial.begin(38400);
}

void loop() {
    if (s.available()) Serial.write( s.read() );
    if (Serial.available()) s.write( Serial.read() );
}
