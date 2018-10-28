void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  
}
int c;
void loop()
  // put your main code here, to run repeatedly:
  if(Serial1.available())
  {
    c=Serial.read();
  Serial.println(c);
  Serial.println(":)");
  }
}
