#ifndef ATLAS_H
#define ATLAS_H

#include "Arduino.h"
#include "SoftwareSerial.h"

#define rxPin 3
#define txPin 2
#define baud 38400

#define BufferLength 128

class Atlas { 
public :
	Atlas();
	~Atlas();
    void on();
	void off();
    void single();
    String version();
    String read( float temp );
private :
    void flush();
    String readstamp();
};

#endif
