#ifndef ATLAS_H
#define ATLAS_H

#include "Arduino.h"
#include "AltSoftSerial.h"

#define muxPin1 2
#define muxPin2 3

#define baud 38400

#define BufferLength 128

class Atlas { 
public :
	Atlas();
	~Atlas();
    void on( int port );
	void off( int port );
    String version( int port );
    String read( int port, float temp );
private :
    select( int i );
    String querystamp();
};

#endif
