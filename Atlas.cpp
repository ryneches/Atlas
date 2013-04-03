#include "Atlas.h"

SoftwareSerial _atlas( rxPin, txPin );
char inchar = 0;
String buffer = "";

// Constructor
Atlas::Atlas(){
    pinMode( rxPin, INPUT  );
    pinMode( txPin, OUTPUT );
    _atlas.begin( baud );
}

// Destructor
Atlas::~Atlas(){/*nothing to destruct*/}

// read a line of data from the stamp
String Atlas::readstamp() {
    buffer = "";
    while( _atlas.available() > 0 ) {
        inchar = (char)_atlas.read();
        buffer += inchar;
        Serial.println( inchar );
        if( inchar == '\r' ) break;
    }
    Serial.println( "hello" + buffer );
    return buffer;
}

// turn the LED on
void Atlas::on(){
    _atlas.print( "l1\r" );
}

// turn the LED off
void Atlas::off(){
    _atlas.print( "l0\r" );
}

// get the version string
String Atlas::version(){
    flush();
    _atlas.print( "i\r" );
    delay(10);
    return readstamp();    
}

// single read mode
void Atlas::single(){
    _atlas.print( "e\r" );
}

// flush the serial input
void Atlas::flush(){
    while( _atlas.available() > 0 ) _atlas.read();
}

// take a temperature corrected measurement
String Atlas::read( float temp ){
    flush();
    _atlas.print( temp );
    _atlas.print( "\r" );
    delay(100);
    return readstamp();
}
