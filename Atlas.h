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

#define USE_MUX

class Atlas {
public :
	Atlas();
	~Atlas();
    void on();
	void off();
    
    #ifdef USE_MUX
    String version( int port );
    String read( int port, long temp );
    #else
    String version();
    String read( long temp );
    #endif
 
private :
    
    #ifdef USE_MUX
    void select( int i );
    String querystamp( int port, String query );
    #else
    String querystamp( String query );
    #endif

};

#endif
