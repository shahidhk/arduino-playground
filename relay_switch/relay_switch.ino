const int ledPin = 12; // the pin that the LED is attached to
const int pirInput = 10;
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(pirInput, INPUT);
}

void loop() {
  // see if there's incoming serial data: 
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(ledPin, HIGH);
    } 
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(ledPin, LOW);
    }
  }
  
  if(digitalRead(pirInput)==1){
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin,LOW);
  }
}
