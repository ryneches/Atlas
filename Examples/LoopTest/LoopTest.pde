#include <AltSoftSerial.h>

AltSoftSerial s;
int m = 0;

void init_stamp() {
  // blink four times
  for( int j = 0; j < 5; j++ ) { 
    s.print( "l0\r" );
    delay(50);
    s.print( "l1\r" );
    delay(50);
  }
  // enter quiecent mode
  s.print( "e\r" );
}

void off_stamp() {
  // turn off LED
  s.print( "l0\r" );
  delay(10);
}

void select( int i ) {
  off_stamp();
  switch( i ) {
    case 0:
      digitalWrite( 2, LOW  );
      analogWrite(  3, 0    );
      break;
    case 1:
      digitalWrite( 2, LOW  );
      analogWrite(  3, 255  );
      break;
    case 2:
      digitalWrite( 2, HIGH );
      analogWrite(  3, 0    );
      break;
    case 3:
      digitalWrite( 2, HIGH );
      analogWrite(  3, 255  );
      break;
  }
  delay(16);
  init_stamp();
}


void setup() {
  pinMode(2, OUTPUT); // set MUX pin 1
  pinMode(3, OUTPUT); // set MUX pin 2
  
  Serial.begin(38400);
  s.begin(38400);
  
  Serial.println( "Atlas Shield test." );
  
}

void loop() {
  select( m );
  delay(1000);
  Serial.print( String(m) + " : " );
  char c = 0;
  String buffer = "";
  s.print( "22.45\r" );
  delay( 1000 );
  while(s.available()) {
    c = s.read();
    buffer += c;
    if( c == '\r' ) {
      Serial.println( buffer );
      break;
    }
  }
  m++;
  if ( m == 4 ) m = 0;  
}
