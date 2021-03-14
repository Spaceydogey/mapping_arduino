

//////////////////WORKING or not lol////////////////////

const int SPEEDS_RANGE  = 100;
const int SPEEDS_OFFSET  = 50;
const int SPEED_PRECISION  = 5;
const int SPEEDS_LENGTH  = (int) (SPEEDS_RANGE  / SPEED_PRECISION);


double speed1_array[21];
double speed2_array[21];



double last_speed1 = 0;
double last_speed2 = 0;



//pwm is from 50 to 150
////////////////////////////////////////////////
///////////SETUP OF THE INITIALS SPEEDS/////////
////////////////////////////////////////////////
void setupInitialSpeed(double speed_array1[21], double speed_array2[21])
{
  for (int i = 0; i <= SPEEDS_LENGTH; i++)
  {
    if (speed_array1[i] >= 0.1)
    {
      initial_speed1 = speed_array1[i];
      initial_pwm1 = i * SPEED_PRECISION + SPEEDS_OFFSET;
      Serial.println(initial_speed1);
      break;
    }
  }

  for (int i = 0; i <= SPEEDS_LENGTH; i++)
  {
    if (speed_array2[i] >= 0.1)
    {
      initial_speed2 = speed_array2[i];
      initial_pwm2 = i * SPEED_PRECISION + SPEEDS_OFFSET;
      Serial.println(initial_speed2);
      break;
    }

  }
}



///////////////////
/////CS SETUP//////
///////////////////
void setupCS() {

  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);

  for (int i = 0 ; i <= SPEEDS_LENGTH; i++) {
    int power = i * SPEED_PRECISION + SPEEDS_OFFSET;


    encoder1_value = 0;
    encoder2_value = 0;

    unsigned long lastTime = millis();

    analogWrite(PWM1, power);   //PWM Speed Control
    analogWrite(PWM2, power);   //PWM Speed Control

    delay(500);

    unsigned long now = millis();



    double time_delta = now - lastTime;


    float x = (float) (encoder1_value / (int) (now - lastTime));

    Serial.println("x");
    Serial.println(x);


    double speed_1 = encoder1_value / time_delta;
    double speed_2 = encoder2_value / time_delta;


    //PRINTS
    Serial.println("power  then speed 1 2");
    Serial.println(power);
    Serial.println(speed_1);
    Serial.println(speed_2);


    //
    speed1_array[i] = speed_1;
    speed2_array[i] = speed_2;

  }
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  setupInitialSpeed(speed1_array, speed2_array);


  for (int i = 0; i <= SPEEDS_LENGTH; i++)
  {
    Serial.print("SPEED 1 and 2");
    Serial.print("\t");
    Serial.print(speed1_array[i]);
    Serial.print("\t");
    Serial.print(speed2_array[i]);
    Serial.print("\n");
  }
}



///////////////////////////////////////
////////SPEED TO PWM CONVERSION////////
///////////////////////////////////////

int SpeedtoPWMconverter1(double Speed) {
  double last_speed1 = 0;


  //////////////////PRINTS///////////////////////////
  /*Serial.print("PWM converter check");
    Serial.print("\t");
    Serial.print(Speed);
    Serial.print("\t");
    Serial.print(last_speed1);
    Serial.print("\t");
  */



  for (int i = 0 ; i <= SPEEDS_LENGTH; i++)

  {

    if (last_speed1 <= Speed <= speed1_array[i]  )

    {
      Serial.println("PWM FOUND");
      return i * SPEED_PRECISION + SPEEDS_OFFSET;
    }


    else {
      Serial.print(".");
      last_speed1 = speed1_array[i];

    }
  }
  Serial.print("null");
  Serial.print("\t");
}

int SpeedtoPWMconverter2(double Speed) {
  double last_speed2 = 0;
  for (int i = 0 ; i <= SPEEDS_LENGTH; i++)

  {
    if (last_speed2 <= Speed <= speed2_array[i])
    {
      return i * SPEED_PRECISION + SPEEDS_OFFSET;
    }
    else {
      last_speed2 = speed2_array[i];
    }
  }
}


/*int findPWMFromSpeed(double desired_speed, double speed_array[21]) {
  int last_speed  = 0;



  for (int i = 0; i <= SPEEDS_LENGTH; i++) {
  if (abs(desired_speed - last_speed) < abs(desired_speed  - speed_array[i]))
  {

  Serial.print("i and last speed and speed array i ");
  Serial.print("\t");
  Serial.print(i);
   Serial.print("\t");
  Serial.print(last_speed);
   Serial.print("\t");
  Serial.print(speed_array[i]);
  Serial.print("\n");
    int value= (i - 1) * SPEED_PRECISION  + SPEEDS_OFFSET;

    return value;
  }



  last_speed  = speed_array[i];
  }
  }



  int speedtoPWMconverter1(double Speed) {

  return findPWMFromSpeed(Speed, speed1_array);
  }



  int speedtoPWMconverter2(double Speed) {

  return findPWMFromSpeed(Speed, speed2_array);
  }*/
