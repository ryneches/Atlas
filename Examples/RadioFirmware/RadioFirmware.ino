#include <AltSoftSerial.h>

AltSoftSerial s;
int m = 0;
int i = 0;
int j = 0;
char c = 0;
String buffer = "";

float read_temp(){
  float v_out; 
  float temp;
  digitalWrite(A0, LOW); 
  digitalWrite(2, HIGH);
  delay(2);
  v_out = analogRead(0); 
  digitalWrite(2, LOW);
  v_out*=0.00324; // (3.34 v) / (1024 bits) == 0.00324
  v_out*=1000;
  temp= 0.0512 * v_out -20.5128;
  return temp;
} 

void read_stamp( String query ) {
  s.print( query );
  buffer = ""; c = 0;
  delay( 1000 );
  while(s.available()) {
    c = s.read();
    if( c == '\r' ) {
      Serial.print( buffer );
      break;
    }
    buffer += c;
  }
  Serial.print( "\n" );
}

void init_stamp() {
  // pause in case there's any ringing in the circuit
  delay(8);
  // toss out any extra stuff in the buffer
  while( s.available() ) s.read();
  // blink four times
  for( int j = 0; j < 5; j++ ) { 
    s.print( "l0\r" );
    delay(50);
    s.print( "l1\r" );
    delay(50);
  }
  // enter quiecent mode
  s.print( "e\r" );
  
  delay(100);
  
  // flush serial port
  //while( s.available() ) {}
}

void off_stamp() {
  // turn off LED
  s.print( "l0\r" );
}

void select( int i ) {
  off_stamp();
  switch( i ) {
    case 0:
      digitalWrite( 2, LOW  );
      analogWrite(  3, 0    );
      break;
    case 1:
      digitalWrite( 2, HIGH );
      analogWrite(  3, 0    );
      break;
    case 2:
      digitalWrite( 2, LOW  );
      analogWrite(  3, 255  );
      break;
    case 3:
      digitalWrite( 2, HIGH );
      analogWrite(  3, 255  );
      break;
  }
  init_stamp();
}


void setup() {
  pinMode(2, OUTPUT); // set MUX pin 1
  pinMode(3, OUTPUT); // set MUX pin 2
  
  Serial.begin(19200);
  s.begin(38400);
  
  Serial.println( "Atlas Shield test." );
  for( int m = 0; m < 4; m++ ) {
    Serial.print( "Port " + String(m) + " : " );
    select( m );
    s.print( "i\r" );
    delay( 500 );
    buffer = ""; c = 0;
    while(s.available()) {
      c = s.read();
      buffer += c;
      if( c == '\r' ) {
        Serial.println( buffer );
        break;
      }
    }
  }
  m = 0;
}

void loop() {
  
  char tmp_buf[5]; // buffer for string/float conversion
  String T = dtostrf( read_temp(), 5, 2, tmp_buf );
  
  select( m );
  switch(m) {
    case 0 : // conductivity
      Serial.print( "Cond : " );
      read_stamp( T + "\r" );
      break;
    case 1 : // ORP
      Serial.print( "ORP  : " );
      read_stamp( "r\r" );
      break;
    case 2 : // D.O.
      Serial.print( "DO   : " );
      read_stamp( String( T ) + ",S" + "\r" );
      break;
    case 3 :
      Serial.print( "pH   : " );
      read_stamp( T + "\r" );
      break;
    case 5 :
      Serial.print( "Temp : " + T + "\n");
  }
  m++;
  if ( m == 6 ) m = 0;
}
