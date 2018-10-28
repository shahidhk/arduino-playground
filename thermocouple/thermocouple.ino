/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
int m0=31;
int m1=33;
int m2=35;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
}

void enable(int num){
  if (num==1){
    digitalWrite(m0,LOW);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
  }
  else if(num==2){
    digitalWrite(m0,HIGH);
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
  }
  else if(num==3){
    digitalWrite(m0,LOW);
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
  }
}
float read_C(int pin)
{
  int raw = analogRead(pin);
  float celsius = ( 5.0 * raw * 100.0) / 1024.0; // Currently assuming 100 degree celsius is 5V. Need to caliberate. 
  return celsius;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin A8:
  for (int i=1;i<4;i++){
    enable(i); // Enable multiplexer for thermocouple
    float celsius    = read_C(A9);// If this is giving zero, change to A8
    Serial.print("Celsius in thermocouple ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(celsius);
    delay(1000); // One second delay
  }
  Serial.println(" ");
  
  delay(500);        // delay in between reads for stability
}
