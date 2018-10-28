
// Code for solving zone A 

int s1,s2,s3,s4,s5,s6,s7,sT;
int leftmotorP=3;
int leftmotorN=4;
int rightmotorN=7;
int rightmotorP=8;
int pwmL=5;
int pwmR=6;
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT); //sensor 1 //9
  pinMode(A1,INPUT); //sensor 2 //10
  pinMode(A2,INPUT); //sensor 3 //11
  pinMode(A3,INPUT); //sensor 4 //12
  pinMode(A4,INPUT); //sensor 5 //13
  pinMode(9,INPUT); //sensor 6
  pinMode(10,INPUT); //sensor 7
  pinMode(leftmotorP,OUTPUT);
  pinMode(leftmotorN,OUTPUT);
  pinMode(rightmotorP,OUTPUT);
  pinMode(rightmotorN,OUTPUT);
  pinMode(A5,INPUT);  // Tsop Sensor
  pinMode(pwmL,OUTPUT);
  pinMode(pwmR,OUTPUT);
  delay(500);
}
void loop() {
  s1=digitalRead(A0);
  s2=digitalRead(A1);
  s3=digitalRead(A2);
  s4=digitalRead(A3);
  s5=digitalRead(A4);
  s6=digitalRead(9);
  s7=digitalRead(10);
  sT=digitalRead(A5);
  //Serial.println(sT);
  if(sT==1)
    linefollow();
  if(sT==0) {
    // Serial.println(sT);
    analogWrite(pwmL,200*255/200);
    digitalWrite(leftmotorP,LOW);                  
    digitalWrite(leftmotorN,HIGH);
    analogWrite(pwmR,200*255/200);
    digitalWrite(rightmotorP,LOW);
    digitalWrite(rightmotorN,HIGH);
    delay(100);                            // delay of coming back
    analogWrite(pwmL,200*255/200);
    digitalWrite(leftmotorP,LOW);
    digitalWrite(leftmotorN,HIGH);
    analogWrite(pwmR,200*255/200);
    digitalWrite(rightmotorP,HIGH);
    digitalWrite(rightmotorN,LOW);
    delay(200);
    s1=digitalRead(A0);
    s2=digitalRead(A1);
    s3=digitalRead(A2);
    s4=digitalRead(A3);
    s5=digitalRead(A4);
    s6=digitalRead(9);
    s7=digitalRead(10);
    sT=digitalRead(A5);
    while( (s7==1)||(s6==1)||(s5==1)) {
      s1=digitalRead(A0);
      s2=digitalRead(A1);
      s3=digitalRead(A2);
      s4=digitalRead(A3);
      s5=digitalRead(A4);
      s6=digitalRead(9);
      s7=digitalRead(10);
      sT=digitalRead(A5);
    analogWrite(pwmL,200*255/200);
    digitalWrite(leftmotorP,LOW);
    digitalWrite(leftmotorN,HIGH);
    analogWrite(pwmR,200*255/200);
    digitalWrite(rightmotorP,HIGH);
    digitalWrite(rightmotorN,LOW);
    }
    linefollow1();
  }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////functions

// line follow function
void linefollow() {
  while(1) {
    s1=digitalRead(A0);
    s2=digitalRead(A1);
    s3=digitalRead(A2);
    s4=digitalRead(A3);
    s5=digitalRead(A4);
    s6=digitalRead(9);
    s7=digitalRead(10);
    //move straight
    if(((s1==1)&&(s2==1)&&(s3==1)&&(s4==0)&&(s5==1)&&(s6==1)&&(s7==1))||((s1==1)&&(s2==1)&&(s3==0)&&(s4==0)&&(s5==0)&&(s6==1)&&(s7==1))) {
      // Serial.println("straight");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    if((s2==0)&&(s3==0)&&(s4==0)&&(s5==0)&&(s6==0)) {///////////// T junction//////////////
      // Serial.println("T"); 
      //turn Right
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,150*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
      delay(100);
    }
    //move soft right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==0)&&(s5==0)&&(s6==1)&&(s7==1)) {
      // Serial.println("s right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,150*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //move right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s5==0)&&(s6==0)&&(s7==1)) {
      //  Serial.println("right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,100*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //right at cross
    if((s1==1)&&(s4==0)&&(s5==0)&&(s6==0)&&(s7==0)) {
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,100*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
      delay(200);
    }
    //move hard right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==1)&&(s6==0)&&(s7==0)) {
      Serial.println("h right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,0*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
    }
    //move hard hard right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==1)&&(s6=1)&&(s7==0)) {
      //  Serial.println("h right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
    }
    //move soft left
    if((s1==1)&&(s2==1)&&(s3==0)&&(s4==0)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //  Serial.println("s left");
      analogWrite(pwmL,150*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //move left
    if((s1==1)&&(s2==0)&&(s3==0)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //  Serial.println("left");
      analogWrite(pwmL,100*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    // left at cross
    if((s1==0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s7==1)) {
      analogWrite(pwmL,100*255/200);
      digitalWrite(leftmotorP,LOW);
      digitalWrite(leftmotorN,HIGH);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
      delay(200);
    }
    //move hard left
    if((s1==0)&&(s2==0)&&(s4==1)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //  Serial.println("h left");
      analogWrite(pwmL,0*255/200);
      digitalWrite(leftmotorP,LOW);
      digitalWrite(leftmotorN,HIGH);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH); 
      digitalWrite(rightmotorN,LOW);
    }
    // hard hard left
    if((s1==0)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //  Serial.println("h left");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,LOW);
      digitalWrite(leftmotorN,HIGH);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH); 
      digitalWrite(rightmotorN,LOW);
    }
    if (sT==1)
      break;
  }
}




// ///////////////////////////////////////////line follow1 function for line following after detecting obstacle////////////////////////////////////////////////////////////////////////

void linefollow1() {
  while(1) {
    s1=digitalRead(A0);
    s2=digitalRead(A1);
    s3=digitalRead(A2);
    s4=digitalRead(A3);
    s5=digitalRead(A4);
    s6=digitalRead(9);
    s7=digitalRead(10);
    //move straight
    if(((s1==1)&&(s2==1)&&(s3==1)&&(s4==0)&&(s5==1)&&(s6==1)&&(s7==1))||((s1==1)&&(s2==1)&&(s3==0)&&(s4==0)&&(s5==0)&&(s6==1)&&(s7==1))) {
      //Serial.println("straight");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    if(((s2==0)&&(s3==0)&&(s4==0)&&(s5==0))&&(s6==0)) {// T junction
      //Serial.println("T"); 
      //turn Right
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,150*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
      delay(100);
    }
    // left at cross break
    if((s1==0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s7==1)) {
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
      delay(200);
      break;
    }
    //move soft right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==0)&&(s5==0)&&(s6==1)&&(s7==1)) {
      //Serial.println("s right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,150*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //move right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s5==0)&&(s6==0)&&(s7==1)) {
      //Serial.println("right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,100*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //right at cross
    if((s1==1)&&(s4==0)&&(s5==0)&&(s6==0)&&(s7==0)) {
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,100*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
      delay(200);
    }
    //move hard right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==1)&&(s6==0)&&(s7==0)) {
      //Serial.println("h right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,0*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
    }
    //move hard hard right
    if((s1==1)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==1)&&(s6=1)&&(s7==0)) {
      //Serial.println("h right");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,LOW);
      digitalWrite(rightmotorN,HIGH);
    }
    //move soft left
    if((s1==1)&&(s2==1)&&(s3==0)&&(s4==0)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //Serial.println("s left");
      analogWrite(pwmL,150*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //move left
    if((s1==1)&&(s2==0)&&(s3==0)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //Serial.println("left");
      analogWrite(pwmL,100*255/200);
      digitalWrite(leftmotorP,HIGH);
      digitalWrite(leftmotorN,LOW);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
    }
    //move hard left
    if((s1==0)&&(s2==0)&&(s4==1)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //Serial.println("h left");
      analogWrite(pwmL,0*255/200);
      digitalWrite(leftmotorP,LOW);
      digitalWrite(leftmotorN,HIGH);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH); 
      digitalWrite(rightmotorN,LOW);
    }
    // hard hard left
    if((s1==0)&&(s2==1)&&(s3==1)&&(s4==1)&&(s5==1)&&(s6==1)&&(s7==1)) {
      //Serial.println("h left");
      analogWrite(pwmL,200*255/200);
      digitalWrite(leftmotorP,LOW);
      digitalWrite(leftmotorN,HIGH);
      analogWrite(pwmR,200*255/200);
      digitalWrite(rightmotorP,HIGH); 
      digitalWrite(rightmotorN,LOW);
    }
    if (sT==1)
      break;
  }
}












