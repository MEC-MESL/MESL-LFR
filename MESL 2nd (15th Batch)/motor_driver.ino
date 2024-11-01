void wheel(int leftSpeed, int rightSpeed){
  

  if(leftSpeed == 0){

    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);

  }

  if(leftSpeed > 0){

    digitalWrite(inC, HIGH);
    digitalWrite(inD, LOW);

  }

  else if(leftSpeed < 0){

    digitalWrite(inC, LOW);
    digitalWrite(inD, HIGH);

  }

  if(rightSpeed == 0){

    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);

  }

  if(rightSpeed > 0){

    digitalWrite(inB, HIGH);
    digitalWrite(inA, LOW);

  }

  else if(rightSpeed < 0){

    digitalWrite(inB, LOW);
    digitalWrite(inA, HIGH);

  }

  // digitalWrite(inB, HIGH);
  // digitalWrite(inC, HIGH);

  if(abs(leftSpeed)> maxSpeed) leftSpeed= maxSpeed;
  if(abs(rightSpeed)> maxSpeed) rightSpeed= maxSpeed;

  analogWrite(enA, abs(rightSpeed));
  analogWrite(enB, abs(leftSpeed));
  
}



