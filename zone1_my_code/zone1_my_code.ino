
  read_sensor_values();
  if (flag==0){
    if(sensor[0]==0&&sensor[6]==0){
       // First left
       motor_speed(200,200);
      run('l','b');
      run('r','f');
      while(sensor[6]!=0||sensor[5]!=0||sensor[4]!=0){
        read_sensor_values();
      }
      flag=1;
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
      delay(500);
      flag=3;
    }
  }
  else if (flag==3){
    if ((sensor[6]==1&&sensor[5]==1&&sensor[4]==0&&sensor[3]==0&&sensor[2]==0&&sensor[1]==0&&sensor[0]==0) || (sensor[6]==1&&sensor[5]==1&&sensor[4]==1&&sensor[3]==0&&sensor[2]==0&&sensor[1]==0&&sensor[0]==0)){
      motor_speed(255,200);
      run('l','f');
      run('r','b');
      delay(500);
      motor_speed(255,255);
      run('l','f');
      run('r','f');
      flag=4;
    }
  }
  
