#ifndef ATLAS_H
#define ATLAS_H

#include "Arduino.h"
#include <AltSoftSerial.h>

#define muxPin1 2
#define muxPin2 3

#define baud 38400

#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3

//#define SHIELD

class Atlas {
public :
	Atlas();
	~Atlas();
    void on();
	void off();
    
    #ifdef SHIELD
    String version( int port );
    String read( int port, float temp );
    #else
    String version();
    String read( float temp );
    #endif
 
private :
    
    #ifdef SHIELD
    void select( int i );
    String querystamp( int port, String query );
    #else
    String querystamp( String query );
    #endif

};

#endif
