///////////////////NOT 100% DONE(especially TURN)///////////////////////////////


void _resetEncoders() {
  encoder1_value = 0;
  encoder2_value = 1;
}

void _changeModes(int mode1, int mode2) {

}




//////////////////////////////////////
///////////////FORWARD////////////////
//////////////////////////////////////


void Forward(double Distance) //Distance in meters
{
  //set the direction of the robot reverse value if the robot goes backward
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);

  Speed = max(initial_speed1, initial_speed2);

  // reset the encoder value
  encoder1_value = 0;
  encoder2_value = 0;

  rPos1 = 0;
  rPos2 = 0;

  //incresing speed loop
  while ((double)encoder1_value * a * WHEEL_RADIUS <= Distance and Speed < 0.5)
  { 
    double power1 = SpeedtoPWMconverter1(Speed);
    double power2 = SpeedtoPWMconverter2(Speed);
    pid(p1, p2);
    
    Speed = Speed + 0.05;


//    regulation_foward(Distance,p1,p2)

    //prints
    Serial.print("Speed");
    Serial.print("\t");
    Serial.print(Speed);
    Serial.print("\n");
    Serial.print("power  1 & 2");
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(SpeedtoPWMconverter1(Speed));
    Serial.print("\t");
    Serial.print(SpeedtoPWMconverter2(Speed));
    Serial.print("\n");

    //Motor inputs
    int In_Pwm1 = round(power1 + u1);
    int In_Pwm2 = round(power2 + u2);
    //max and min for the inputs
    if (In_Pwm1 >= 120) In_Pwm1 = 120;
    if (In_Pwm2 >= 115) In_Pwm2 = 115;
    if (In_Pwm1  < initial_pwm1 ) In_Pwm1 = initial_pwm1;
    if (In_Pwm2 < initial_pwm2) In_Pwm2 = initial_pwm2;


    //prints
    Serial.print("IN pwm  1 & 2");
    Serial.print("\t");
    Serial.print(In_Pwm1);
    Serial.print("\t");
    Serial.print(In_Pwm2);
    Serial.print("\n");
    Serial.print("u 1 & 2");
    Serial.print("\t");
    Serial.print(u1);
    Serial.print("\t");
    Serial.print(u2);
    Serial.print("\n");

    //Actual part of the code thats make the robot move
    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);  //PWM Speed Control
    delay(15);
    now = millis();
    timechange = now - lastTime ;
    //prints
    Serial.println(encoder1_value);
  }

  //////////////////////////////////////////////////////////////////
  //constant speed loop setup
  Speed = 0.5;
  double power1 = SpeedtoPWMconverter1(Speed);
  double power2 = SpeedtoPWMconverter2(Speed);


  //prints
  Serial.print("Speed");
  Serial.print("\t");
  Serial.print(Speed);
  Serial.print("\n");
  Serial.print("power  1 & 2");
  Serial.print(power1);
  Serial.print("\t");
  Serial.print(power2);
  Serial.print("\n");


  //constant speed loop
  while ((double)encoder1_value * a * WHEEL_RADIUS <= Distance)
  {

    pid(p1, p2);
    //    regulation_foward(Distance,p1,p2)
    //Motor inputs
    int In_Pwm1 = round(power1 + u1);
    int In_Pwm2 = round(power2 + u2);
    //min max motors input
    if (In_Pwm1 >= 120) In_Pwm1 = 120;
    if (In_Pwm2 >= 115) In_Pwm2 = 115;
    if (In_Pwm1  < initial_pwm1 ) In_Pwm1 = initial_pwm1;
    if (In_Pwm2 < initial_pwm2) In_Pwm2 = initial_pwm2;

    //prints
    Serial.print("IN pwm  1 & 2");
    Serial.print("\t");
    Serial.print(In_Pwm1);
    Serial.print("\t");
    Serial.print(In_Pwm2);
    Serial.print("\n");
    Serial.print("u 1 & 2");
    Serial.print("\t");
    Serial.print(u1);
    Serial.print("\t");
    Serial.print(u2);
    Serial.print("\n");

    //Actual part of the code thats make the robot move
    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);  //PWM Speed Control
    delay(15);
    now = millis();
    //timechange = now - lastTime ;

    Serial.println(encoder1_value);

  }
  //Stopping
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}
