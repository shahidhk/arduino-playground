float Kp=20,Ki=0,Kd=0;//80 
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
void linefollow(void);

int L1 = 3; //Left Motor Pin 1 +ve fwd
int L2 = 4; //Left Motor Pin 2 -ve bckwd
int R1 = 7; //Right Motor Pin 1 +ve fwd
int R2 = 8; //Right Motor Pin 2 -ve bckwd

int Lpwm = 5; //PWM Pin 1 Left motor
int Rpwm = 6; //PWM Pin 2 Right motor

int tsop = 0;

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
  

  run('l','f');
  run('r','f');

}

void loop()
{
    zone1();
    
    linefollow();
}

void zone1(void)
{
  read_sensor_values();
  if (flag==0){
    if(sensor[0]==0&&sensor[6]==0){
      flag=1; // First left
      delay(200);
      run('l','b');
      run('r','f');
      while(sensor[6]!=0||sensor[5]!=0||sensor[4]!=0){
        read_sensor_values();
      }
      delay(200);
      linefollow();
    }
  }
  else if (flag==1){
    check_tsop();
  }
  else if (flag==2){ //Skip the T junction afer coming back from the box
    read_sensor_values();
    // more conditions needed.
    if ((sensor[0]==1&&sensor[1]==1&&sensor[2]==0&&sensor[3]==0&&sensor[4]==0&&sensor[5]==0&&sensor[6]==0) || (sensor[0]==1&&sensor[1]==1&&sensor[2]==1&&sensor[3]==0&&sensor[4]==0&&sensor[5]==0&&sensor[6]==0)){
      motor_speed(200,200);
      run('l','f');
      run('r','f');
      delay(200);
      flag=3;
    }
  }
  else if (flag==3){
    if ((sensor[6]==1&&sensor[5]==1&&sensor[4]==0&&sensor[3]==0&&sensor[2]==0&&sensor[1]==0&&sensor[0]==0) || (sensor[6]==1&&sensor[5]==1&&sensor[4]==1&&sensor[3]==0&&sensor[2]==0&&sensor[1]==0&&sensor[0]==0)){
      motor_speed(255,200);
      run('l','f');
      run('r','b');
      delay(200);
      motor_speed(255,255);
      run('l','f');
      run('r','f');
      flag=4;
    }
  }
  
}

void linefollow()
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
  
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=3;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)){error=2;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=1;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=0;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-1;}
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-2;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-3;}
  
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=10;hard_flag=1;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=10;hard_flag=1;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)){error=10;hard_flag=1;}
  
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
      if(left_motor_speed>255){right_motor_speed = Kp*(left_motor_speed - 255);run('l','f');run('r','b');}
      else if(right_motor_speed>255){left_motor_speed = Kp*(right_motor_speed -255);run('r','f');run('l','b');}
      
    }

    
    motor_speed(left_motor_speed, right_motor_speed);

}

