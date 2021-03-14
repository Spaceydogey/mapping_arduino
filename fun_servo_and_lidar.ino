const String SERVO_LIDAR_MODULE = "S&L";

void setupServoAndLidar() {
  if (!lox.begin()) {
    while (1);
    bLog("Unable to init LIDAR", SERVO_LIDAR_MODULE);
  }

  servo.attach(SERVO_PIN);

  bLogCompleted(SERVO_LIDAR_MODULE);
}


void launchScan() {
  bLog("Launching scan", SERVO_LIDAR_MODULE);

  VL53L0X_RangingMeasurementData_t measure;

  JSONVar data;

  servo.write( SERVO_SHIFT );

  for (int i = 0; i < SERVO_STEPS_COUNT; i++) {
    servo.write((int) i * SERVO_STEP);

    delay(100); // wait 50 ms for the servo to rotate

    lox.rangingTest(&measure, false);

    delay(50); // wait 20 ms for the LIDAR to scan

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data

      if (measure.RangeMilliMeter >= 1000) {
        data[i] = -1;
      }
      else {
        data[i] = (int) (measure.RangeMilliMeter / 10);
      }
    } else {
      data[i] = 0;
    }
  }


  servo.write( SERVO_SHIFT );

  Serial.println(JSON.stringify(data));
  sendMessage(3, data);

}
