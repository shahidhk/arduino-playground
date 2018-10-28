float Kp=32,Ki=0,Kd=0;//80 
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0;
int sensor[6]={0, 0, 0, 0, 0, 0};
int initial_motor_speed=255;

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);
void run(char w, char d);

int L1 = 3; //Left Motor Pin 1 +ve fwd
int L2 = 4; //Left Motor Pin 2 -ve bckwd
int R1 = 7; //Right Motor Pin 1 +ve fwd
int R2 = 8; //Right Motor Pin 2 -ve bckwd

int Lpwm = 5; //PWM Pin 1 Left motor
int Rpwm = 6; //PWM Pin 2 Right motor


void run(char w, char d)
{
  switch(d){
    case 'f':
      switch(w){
        case 'r':
          digitalWrite(R2,LOW);
          digitalWrite(R1,HIGH);
          break;
        case 'l':
          digitalWrite(L2,HIGH);
          digitalWrite(L2,LOW);
          break;
      }
    case 'b':
      switch(w){
        case 'r':
          digitalWrite(R2,LOW);
          digitalWrite(R1,HIGH);
          break;
        case 'l':
          digitalWrite(L2,HIGH);
          digitalWrite(L1,LOW);
          break;
      }
  }
}

void setup()
{
 pinMode(Lpwm,OUTPUT); 
 pinMode(Rpwm,OUTPUT); 
 pinMode(L1,OUTPUT); 
 pinMode(L2,OUTPUT); 
 pinMode(R1,OUTPUT); 
 pinMode(R2,OUTPUT);
 
     digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);

}

void loop()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
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

  if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==0)){error=6;}
  //else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=20;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)){error=4;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)){error=3;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)){error=2;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=1;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)){error=0;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=1;}
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-2;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-3;}
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-4;}
  //else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-20;}
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){error=-6;}
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==1)){
    if(previous_error>0){error=30;}
    else if(previous_error<0){error=-30;}
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
     if (left_motor_speed>255){left_motor_speed=255;}
    if (right_motor_speed>255){right_motor_speed=255;}
    if (left_motor_speed<0){left_motor_speed=0;}
    if (right_motor_speed<0){right_motor_speed=0;}
    
    analogWrite(Lpwm,left_motor_speed);   //Left Motor Speed
    analogWrite(Rpwm,right_motor_speed);  //Right Motor Speed
    //following lines of code are to make the bot move forward

}

