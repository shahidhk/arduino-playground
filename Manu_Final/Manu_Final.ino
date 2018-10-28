float Kp=10,Ki=0,Kd=0;//80 
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0;
int sensor[6]={0, 0, 0, 0, 0, 0};
int initial_motor_speed=255;
int hard_flag=0;
int count=0;
int zone1_flag=1;
int flag=0;

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);
void run(char w, char d);
void check_tsop(void);
void zone1(void);
void motor_speed(int l, int r);
void linefollow_sh(void);
void linefollow1();
void linefollow();

int L1 = 3; //Left Motor Pin 1 +ve fwd
int L2 = 4; //Left Motor Pin 2 -ve bckwd
int R1 = 7; //Right Motor Pin 1 +ve fwd
int R2 = 8; //Right Motor Pin 2 -ve bckwd

int Lpwm = 5; //PWM Pin 1 Left motor
int Rpwm = 6; //PWM Pin 2 Right motor

int tsop = 0;
int s1,s2,s3,s4,s5,s6,s7,sT;
int leftmotorP=3;
int leftmotorN=4;
int rightmotorN=7;
int rightmotorP=8;
int pwmL=5;
int pwmR=6;

void run(char w, char d)
{
   if(w=='r'&&d=='f'){
            digitalWrite(R1,LOW);
            digitalWrite(R2,HIGH);
   }
  else if(w=='l'&&d=='f'){
            digitalWrite(L1,HIGH);
            digitalWrite(L2,LOW);
  }
  else if (w=='r'&&d=='b'){
            digitalWrite(R2,LOW);
            digitalWrite(R1,HIGH);
  }
  else if (w=='l'&&d=='b'){
            digitalWrite(L2,HIGH);
            digitalWrite(L1,LOW);
        }
}

void motor_speed(int l, int r)
{
    analogWrite(Lpwm,l);   //Left Motor Speed
    analogWrite(Rpwm,r);  //Right Motor Speed
}

void setup()
{
 pinMode(Lpwm,OUTPUT); 
 pinMode(Rpwm,OUTPUT); 
 pinMode(L1,OUTPUT); 
 pinMode(L2,OUTPUT); 
 pinMode(R1,OUTPUT); 
 pinMode(R2,OUTPUT);
 pinMode(12,INPUT);
 pinMode(9,INPUT);
 pinMode(10,INPUT);

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
  delay(200);
  
  run('l','f');
  run('r','f');

}

void loop()
{
  if(digitalRead(12)==1){
    zone1();}
  else{
    linefollow_sh();}
}

void zone1(void)
{
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

void linefollow_sh()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
}

void check_tsop()
{
  tsop = digitalRead(A5);
  if (tsop==0){
    delay(100);
    motor_speed(190,190);
    run('l','b');
    run('r','b');
    delay(300);
    run('l','b');
    run('r','f');
    while(sensor[6]!=0||sensor[5]!=0||sensor[4]!=0){
      read_sensor_values();
    }
    delay(200);
    run('l','f');
    run('r','f');
    flag=2;
  }  
}

void read_sensor_values()
{
  sensor[0]=digitalRead(A0);// Left most
  sensor[1]=digitalRead(A1);
  sensor[2]=digitalRead(A2);
  sensor[3]=digitalRead(A3);
  sensor[4]=digitalRead(A4);
  sensor[5]=digitalRead(9);
  sensor[6]=digitalRead(10);// Right most
  hard_flag=0;
  
  if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==0)){error=6;hard_flag=1;}
  //else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=20;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)){error=4;hard_flag=1;}
  
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=10;hard_flag=1;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=10;hard_flag=1;}
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=10;hard_flag=1;}
  
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=3;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)){error=2;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=0;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=0;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=0;}
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-2;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-3;}
  
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-10;hard_flag=1;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=-10;hard_flag=1;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)){error=-10;hard_flag=1;}
  
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-4;hard_flag=1;}
  //else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-20;}
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-6;hard_flag=1;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){
    hard_flag=1;
    if(previous_error>0){error=10;}
    else if(previous_error<0){error=-10;}
  }

}

void calculate_pid()
{
    P = error;
    I = I + error;
    D = error-previous_error;

    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_error=error;

}

void motor_control()
{
    // Calculating the effective motor speed:
    int left_motor_speed = initial_motor_speed+PID_value;
    int right_motor_speed = initial_motor_speed-PID_value;
    
    // The motor speed should not exceed the max PWM value
    // Not happening. Why???
    /*
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
    */
    if (hard_flag==0){    
      if (left_motor_speed>255){left_motor_speed=255;}
      if (right_motor_speed>255){right_motor_speed=255;}
      if (left_motor_speed<0){left_motor_speed=0;}
      if (right_motor_speed<0){right_motor_speed=0;}
      run('l','f');
      run('r','f');
    }
    else if (hard_flag==1){
      if(left_motor_speed>255){right_motor_speed = (Kp)*(left_motor_speed - 255);run('l','f');run('r','b');}
      else if(right_motor_speed>255){left_motor_speed = (Kp)*(right_motor_speed -255);run('r','f');run('l','b');}
      
    }

    
    motor_speed(left_motor_speed, right_motor_speed);

}


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
      analogWrite(pwmR,0*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
      
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
      analogWrite(pwmR,0*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
      delay(250);
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
      analogWrite(pwmR,0*255/200);
      digitalWrite(rightmotorP,HIGH);
      digitalWrite(rightmotorN,LOW);
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
      delay(250);
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
      delay(250);
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
      delay(250);
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


