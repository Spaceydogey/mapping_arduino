

/////////////////////////////////////
////////////////TURN/////////////////
/////////////////////////////////////


void Turn(bool right) {

  if (right)
  {
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, LOW);
  }
  else
  {
    digitalWrite(DIR1, LOW);
    digitalWrite(DIR2, HIGH);
  }       //set the direction of the robot reverse value if the robot goes backward


  Speed = max(initial_speed1, initial_speed2);
  //reset the encoder value
  encoder1_value = 0;
  encoder2_value = 0;
  rPos1 = 0;
  rPos2 = 0;


  /*while ((double)(encoder1_value + encoder2_value) * (double) (0.5) * WHEEL_RADIUS <=  45 * RACK and Speed < 0.3)
    {
    pid(p1, p2);
    Speed = Speed + 0.05;
    double power1 = SpeedtoPWMconverter1(Speed);
    double power2 = SpeedtoPWMconverter2(Speed);

    int In_Pwm1 = round(power1 + u1);
    int In_Pwm2 = round(power2 + u2);
    if (In_Pwm1 >= 120) In_Pwm1 = 120;
    if (In_Pwm2 >= 115) In_Pwm2 = 115;
    if (In_Pwm1  < initial_pwn1 ) In_Pwm1 = initial_pwm1;
    if (In_Pwm2 < initial_pwn2) In_Pwm2 = initial_pwm2;



    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);  //PWM Speed Control
    delay(15);
    now = millis();
    timechange = now - lastTime ;

    Serial.println(encoder1_value);
    Serial.println(encoder2_value);

    }*/
  Speed = 0.3;
  double power1 = SpeedtoPWMconverter1(Speed);
  double power2 = SpeedtoPWMconverter2(Speed);

  Serial.println((double)(encoder1_value + encoder2_value));

  while ((double)(encoder1_value + encoder2_value) * (double) (0.5) * WHEEL_RADIUS <=  45 *  ROBOT_TRACK)
  {
    pid(p1, p2);


    int In_Pwm1 = round(power1 + u1);
    int In_Pwm2 = round(power2 + u2);
    if (In_Pwm1 >= 120) In_Pwm1 = 120;
    if (In_Pwm2 >= 115) In_Pwm2 = 115;
    if (In_Pwm1  < initial_pwm1 ) In_Pwm1 = initial_pwm1;
    if (In_Pwm2 < initial_pwm2) In_Pwm2 = initial_pwm2;



    lastTime = millis();
    analogWrite(PWM1, In_Pwm1);  //PWM Speed Control
    analogWrite(PWM2, In_Pwm2);  //PWM Speed Control
    delay(15);
    now = millis();
    timechange = now - lastTime ;


    Serial.println(encoder1_value);
    Serial.println(encoder2_value);
    Serial.println( 85 * ROBOT_TRACK);
    Serial.println((double)(encoder1_value + encoder2_value) * (1 / 2) * WHEEL_RADIUS );
  }   //Stopping
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
}
