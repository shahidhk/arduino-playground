double value;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{ 
  value = analogRead(A0);
  
  // put your main code here, to run repeatedly:
  Serial.println(value);
  delay(500);
}
