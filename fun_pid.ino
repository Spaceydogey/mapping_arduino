///////////////////////////almost working/////////////////////////////


void pid(double P1, double P2) {

  int Pos1 = encoder1_value;
  int Pos2 = encoder2_value;
  
  int u01 = 0;
  int u02 = 0;

 
  //Speed integration
  //rPos1 += Speed * timechange; //timechange is defined in the movement function for the moment
  //rPos2 += Speed * timechange;
  rPos1 = Speed * timechange; //timechange is defined in the movement function for the moment
  rPos2 = Speed * timechange;


  //error calculation
  //double error1 = rPos1 - Pos1;
  //double error2 = rPos2 - Pos2;
  double error1 = rPos1 - last_pos1;
  double error2 = rPos2 - last_pos2;
  
  int last_pos1 = Pos1;  
  int last_pos2 = Pos2;

  //output
  //u1 = sign(error1) * 60 + P1 * error1;
  //u2 = sign(error2) * 50 + P2 * error2;
  u1 =P1 * error1;
  u2 =P2 * error2;
   
//prints
  Serial.print("pos 1 & 2"); 
  Serial.print("\t");
  Serial.print(Pos1);
  Serial.print("\t");
  Serial.print(Pos2);
  Serial.print("\n");
  Serial.print("rpos 1 & 2");
  Serial.print("\t");
  Serial.print(rPos1);
  Serial.print("\t");
  Serial.print(rPos2);
  Serial.print("\n");
  Serial.print("Error 1 & 2");
  Serial.print("\t");
  Serial.print(error1);
  Serial.print("\t");
  Serial.print(error2);
  Serial.print("\n");

   
}


///////////////////////////////////////////////////////
////////////////////other pid//////////////////////////
///////////////////////////////////////////////////////
void regulation_foward(double distance, double P1, double P2)
{

  while (error = ! 0 and ((double)encoder1_value * (double)encoder2_value) * (double) * 0.5 * a * WHEEL_RADIUS <= distance)
  {
    int Pos1 = encoder1_value;
    int Pos2 = encoder2_value;
    error = Pos1 - Pos2;
    double u1 = P1 * error;
    double u2 = -P2 * error;


    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);
    now = millis();
    timechange = now - lastTime ;

  }

////////////////////////////////////////////////////////



void setPID(double new_p1, double new_p2) {
  p1 = new_p1;
  p2 = new_p2;
  
  JSONVar data;

  data[0] = 1;

  bLog("Setting up new values ", "PID");
  
  sendMessage(5, data);
}
