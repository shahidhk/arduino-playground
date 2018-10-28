// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo servoLeft;  // create servo object to control a servo 
Servo servoRight;                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int pos2 = 0;
void setup() 
{ 
  servoLeft.attach(9);
  servoRight.attach(6);
  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 20)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servoLeft.write(pos);
       // tell servo to go to position in variable 'pos' 
    delay(15);
    for (pos2 = 0; pos < 180; pos+=1){
      servoRight.write(pos2);
      delay(15);
    }
    for (pos2 = 180 ; pos2>=2; pos2-=1){
      servoRight.write(pos2);
      delay(15);
    }
    pos2=0;
        // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=20)     // goes from 180 degrees to 0 degrees 
  {                                
    servoLeft.write(pos);
        // tell servo to go to position in variable 'pos' 
    delay(15);
    for (pos2 = 0; pos < 180; pos+=1){
      servoRight.write(pos2);
      delay(15);
    }
    for (pos2 = 180 ; pos2>=2; pos2-=1){
      servoRight.write(pos2);
      delay(15);
    }
    pos2=0;    // waits 15ms for the servo to reach the position 
  } 
  
} 
