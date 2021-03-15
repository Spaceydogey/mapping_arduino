///////////////////////////almost working/////////////////////////////

int last_pos1 = 0 ;  
int last_pos2 = 0;
double last_error1 = 0;
double last_error2 = 0 ;




void pid(double P1, double P2) {

  int Pos1 = encoder1_value;
  int Pos2 = encoder2_value;

  int u01 = 0;
  int u02 = 0;

 
  //Speed integration
  rPos1 += Speed * timechange; //timechange is defined in the movement function for the moment
  rPos2 += Speed * timechange;
  //rPos1 = Speed * timechange; //timechange is defined in the movement function for the moment
  //rPos2 = Speed * timechange;
<<<<<<< HEAD
  //int d1 = Pos1 - last_pos1;
  //int d2 = Pos2 - last_pos2;
=======
  int d1 = Pos1 - last_pos1;
  int d2 = Pos2 - last_pos2;
>>>>>>> 9234100b4eb3e4e1657c175d3a895586643d176f
    
  //error calculation
  double error1 = rPos1 - Pos1;
  double error2 = rPos2 - Pos2;
<<<<<<< HEAD
  //double rate_error1 = (error1 - last_error1)/timechange;
  //double rate_error2 = (error2 - last_error2)/timechange;
  //double error1 = rPos1 - d1;
  //double error2 = rPos2 - d2;

=======
  //double error1 = rPos1 - d1;
  //double error2 = rPos2 - d2;
>>>>>>> 9234100b4eb3e4e1657c175d3a895586643d176f
  
  double last_error1 = error1;
  double last_error2 = error2 ;
  //last_pos1 = Pos1;  
  //last_pos2 = Pos2;

  //output
  u1 = initial_pwm1; + P1 * error1;
  u2 = initial_pwm2 + P2 * error2;
  //u1 =P1 * error1 + 0.004*rate_error1;
  //u2 =P2 * error2 + 0006*rate_error2;
   
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
double error;
void regulation_foward(double distance, double P1, double P2)
{
  int Pos1 = encoder1_value;
  int Pos2 = encoder2_value;
  error = Pos1 - Pos2;
  while (error = ! 0 and (encoder1_value * encoder2_value) * (double)  0.5 * a * WHEEL_RADIUS <= distance)
  {
    int Pos1 = encoder1_value;
    int Pos2 = encoder2_value;
    error = Pos1 - Pos2;
    double u1 = -P1 * error;
    double u2 = P2 * error;
    double power1 = SpeedtoPWMconverter1(Speed);
    double power2 = SpeedtoPWMconverter2(Speed);
<<<<<<< HEAD
    int In_Pwm1 = round(u1);
    int In_Pwm2 = round(u2);
    In_Pwm1 = abs(In_Pwm1);
    In_Pwm2 = abs(In_Pwm2);
=======
    int In_Pwm1 = round(power1 + u1);
    int In_Pwm2 = round(power2 + u2);
     if (In_Pwm1 >= 120) In_Pwm1 = 120;
    if (In_Pwm2 >= 115) In_Pwm2 = 115;
    if (In_Pwm1  < initial_pwm1 ) In_Pwm1 = initial_pwm1;
    if (In_Pwm2 < initial_pwm2) In_Pwm2 = initial_pwm2;

>>>>>>> 9234100b4eb3e4e1657c175d3a895586643d176f

    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);
    now = millis();
    timechange = now - lastTime ;

  }
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
