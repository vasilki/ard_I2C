// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <time.h>
unsigned int K_LED_PIN = 13;
unsigned long gl_starttime = 0;

void setup() {
  pinMode(K_LED_PIN,OUTPUT);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void my_diod_blink_1s(unsigned int par_LED)
{
  static unsigned long loc_current_time_ms = 0;
  static boolean loc_bool = LOW;
  unsigned long loc_time = millis();
  
  if(loc_time - loc_current_time_ms >=  1000)
  {
    digitalWrite(par_LED,loc_bool);
    loc_current_time_ms = loc_time;
    loc_bool = !loc_bool;
  }
  else
  {
    
  }
    
  return;
}

void my_diod_high_1s(unsigned int par_LED, unsigned long par_starttime)
{
  unsigned long loc_time = millis();

  if(par_starttime != 0)
  {
    if(loc_time - par_starttime >=  1000)
    {
      digitalWrite(par_LED,LOW);
    }
    else
    {
      digitalWrite(par_LED,HIGH);
    }
  }
  else
  {
    /*nothing to do*/
  }
    
  return;
}

void loop() {
  unsigned long loc_time = millis();
  
  my_diod_high_1s(K_LED_PIN, gl_starttime);
  if ((gl_starttime != 0)&&(loc_time - gl_starttime > 2000))
  {
    gl_starttime = 0;    
  }
  else
  {
    /*nothing to do*/
  }
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  gl_starttime = millis();
  // as expected by master
}
