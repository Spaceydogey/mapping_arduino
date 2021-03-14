//////////////////////////WORKING////////////////////////////


const String ENCODER_MODULE_NAME = "ENCODERS";

void setupEncoders() {
  //Set encoder pins to input PULLUP is to reduce noise
  pinMode(ENCODER_1_PIN, INPUT_PULLUP);
  pinMode(ENCODER_2_PIN, INPUT_PULLUP);

  //set DIR & PWM pin to output
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  /// Add callback
  attachInterrupt(digitalPinToInterrupt(ENCODER_1_PIN), Encoder1, RISING );
  attachInterrupt(digitalPinToInterrupt(ENCODER_2_PIN), Encoder2, RISING);

  
  bLogCompleted(BLUETOOTH_MODULE_NAME);
}

// A callback that is attached to the encoder return pins
void Encoder1() {
  encoder1_value++;  
 //count the number of step, one step = 0.5 degree
}

void Encoder2() {
  encoder2_value++;
}
