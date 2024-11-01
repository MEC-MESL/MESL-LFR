int readSensor(){

  // const int sValues[8]= {A0,A1,7,6,5,4,3,2};
  const int sValues[8]= {A0,A1,A2,A3,A4,A5,3,2};

  // {2, 3, 4, 5, 6, 7, A1, A0}
  int error=0, sumS=0, sumWS=0, linePos=0;

  for(int i=0; i<8; i++){
    sumS += !digitalRead(sValues[i]);
    Serial.print(!digitalRead(sValues[i]));
    Serial.print("  ");
    
  }
  Serial.println();
  

  if(sumS == 0) return 420;

  for(int i=0; i<8; i++){
    sumWS += ((!digitalRead(sValues[i]))* (i+1)*10);
  }
 

  linePos = (sumWS/sumS);

  error = linePos - 45;

  if(!digitalRead(sValues[0])== 1 ) lastSensor=1 ;

  else if(!digitalRead(sValues[7]) == 1) lastSensor=2;

  return error;

}


