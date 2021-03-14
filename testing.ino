#include <Arduino_JSON.h>
#include <Adafruit_VL53L0X.h>
#include <Servo.h>
#include <SoftwareSerial.h>

////////////////////////
///      LIDAR      ///
///////////////////////

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


//////////////////////
/////   SERVO    /////
//////////////////////

const int SERVO_PIN = 11;
const int SERVO_OPENING = 180; // The maxium LIDAR rotation
const int SERVO_SHIFT = 0;
const int SERVO_STEP = 4; // The number of degree per step
const int SERVO_STEPS_COUNT = 45;

Servo servo;
double Speed  = 0 ;
double initial_speed1 ;
double initial_speed2 ;
double initial_pwm1 ;
double initial_pwm2 ;

//////////////////////
////    WHEELS   ////
/////////////////////

const int ENCODER_1_PIN = 5;
const int ENCODER_2_PIN = 3;

// Dynamic variables for encoders, used for odometry & speed correction
int encoder1_value = 0;
int encoder2_value = 0;

const int PWM1 = 6;
const int DIR1 = 4;

const int PWM2 = 9;
const int DIR2 = 2;


double p1 = 0.12;
double p2  = 0.09;

const double WHEEL_RADIUS =  0.0405;

/////////////////////
///      PID     ///
////////////////////

double u1;
double u2;


unsigned long lastTime;
unsigned long now;
unsigned long timechange;

///////////////////////
///       ROBOT     ///
//////////////////////
const double ROBOT_TRACK = 0.17;

double rPos1;
double rPos2;

///////////////////////
///      GLOBAL     ///
///////////////////////

const double a = PI / 180;

////////////////////////
//      Bluetooth    ///
////////////////////////
JSONVar testData;  /// Only used in test mode

SoftwareSerial BTSerial(10, 12);


////////////////////////
///   COMMUNICATION ///
///////////////////////

const int MT_MOVE = 0;
const int MT_MOVE_FEEDBACK = 1;
const int MT_ORDER_SCAN = 2;
const int MT_SCAN_DATA = 3;
const int MT_SETUP_PID = 4;
const int MT_SETUP_PID_FEEDBACK = 5;
const int MT_BLINK = 6;

void testSetup() {
    setupLog();
  setupTestBluetooth();
  setupServoAndLidar();
  setupTestBluetooth();
  setupEncoders();
  setupCS();
}

void prodSetup() {
  setupLog();
  setupServoAndLidar();
  setupBluetooth();
  setupEncoders();
  setupCS();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  testSetup();

}



void loop() {
  //prodLoop();
  testLoop();
  
}

void testLoop() {
  Serial.println("LOOPING");

  while (true) {
    if (BTSerial.available()) {
      String received_data = BTSerial.readStringUntil('\n');
      
      if (received_data.length() > 1) {
        JSONVar parsed_data = parseMessage(received_data); // parse the message

        int type = (int) parsed_data[1];

        if (type == MT_MOVE) {
          Forward((double) parsed_data[2][0]);

          int rotateOrder = parsed_data[2][1];

          if (rotateOrder == 1) {
            Turn(false);
          }
          else if (rotateOrder == -1) {
            Turn(true);
          }
        }
        else if (type == MT_ORDER_SCAN) {
          launchScan();
        }
        else if (type == MT_SETUP_PID) {
          setPID((double) parsed_data[2][0], (double) parsed_data[2][1]);
        }
        else if (type == MT_BLINK) {
          for (int i = 1; i < (int) parsed_data[2]; i++) {
            blink(i);
            delay(1000);
          }
        }
      }
    }
    else {
      blink(1);
    }
  }
}
