#include "Atlas.h"

AltSoftSerial _atlas;
String buffer = "";
char c = 0;

#ifdef USE_MUX
int mux_port = 0;
#endif

// Constructor
Atlas::Atlas(){
    #ifdef USE_MUX
    pinMode( muxPin1, OUTPUT );
    pinMode( muxPin2, OUTPUT );
    #endif

    _atlas.begin( baud );
}

// Destructor
Atlas::~Atlas(){/*nothing to destruct*/}

#ifdef USE_MUX
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
#endif

// query the stamp and then read a line of data
#ifdef USE_MUX
String Atlas::querystamp( int port, String query ) {
    select( port );
#else
String Atlas::querystamp( String query ) {
#endif

    Serial.println( "query : " + query );
    char c = 0;
    buffer = "";
    _atlas.print( query );
    delay( 1200 );
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
#ifdef USE_MUX
String Atlas::version( int port ){
    select( port );
    return querystamp( port, String("i\r") );
}
#else
String Atlas::version() {
     return querystamp( String("i\r") );
}
#endif

// take a temperature corrected measurement
#ifdef USE_MUX
String Atlas::read( int port, long temp ){
    return querystamp( port, String(temp) );
}
#else
String Atlas::read( long temp ){
    return querystamp( String(temp) );
}
#endif
