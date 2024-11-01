void lineFollow(){

  int error, delSpeed;
  float P, D;
  error= readSensor();

  if(error== 420){

    if(lastSensor == 1) wheel(-leftBaseSpeed, rightBaseSpeed);

    else if(lastSensor == 2) wheel(leftBaseSpeed, -rightBaseSpeed);
  }

  else{

    P= kp * error;
    D= kd * (error -  prevError);

    delSpeed = P + D;

    wheel((leftBaseSpeed + delSpeed), (rightBaseSpeed - delSpeed));

    prevError = error;
    
  }

}


