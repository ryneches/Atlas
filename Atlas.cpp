#include "Atlas.h"

AltSoftSerial _atlas;
String buffer = "";
char c = 0;
int mux_port = 0;

// Constructor
Atlas::Atlas(){
    pinMode( muxPin1, OUTPUT );
    pinMode( muxPin2, OUTPUT );
    _atlas.begin( baud );
}

// Destructor
Atlas::~Atlas(){/*nothing to destruct*/}

// select a port on the MUX
void Atlas::select( int i ) {
    off();
    switch( i ) {
        case 0:
            digitalWrite( muxPin1, LOW  );
            analogWrite(  muxPin2, 0    );
            break;
        case 1:
            digitalWrite( muxPin1, LOW  );
            analogWrite(  muxPin2, 255  );
            break;
        case 2:
            digitalWrite( muxPin1, HIGH );
            analogWrite(  muxPin2, 0    );
            break;
        case 3:
            digitalWrite( muxPin1, HIGH );
            analogWrite(  muxPin2, 255  );
            break;
    }
    mux_port = i;
    // pause in case there's any ringing in the circuit
    delay(8);
    // toss out any extra stuff in the buffer
    while( _atlas.available() ) _atlas.read();
    // blink four times
    for( int j = 0; j < 5; j++ ) { 
        off();
        delay(50);
        on();
        delay(50);
    }
    // enter quiecent mode
    _atlas.print( "e\r" );
    delay(100);
}

// query the stamp and then read a line of data
String Atlas::querystamp( int port, String query ) {
    select( port );
    char c = 0;
    buffer = "";
    _atlas.print( query );
    delay( 1000 );
    while( _atlas.available() ) {
        c = _atlas.read();
        buffer += c;
        if( c == '\r' ) {
            break;
        }
    }
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
String Atlas::version( int port ){
    select( port );
    return querystamp( port, "i\r" );    
}

// take a temperature corrected measurement
String Atlas::read( int port, float temp ){
    return querystamp( port, String((long)temp) );
}
