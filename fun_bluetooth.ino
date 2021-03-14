const String BLUETOOTH_MODULE_NAME = "BLUETOOTH";

// Start listening on the BTSerial !
void setupBluetooth() {
  BTSerial.begin(9600);

  bLogCompleted(BLUETOOTH_MODULE_NAME);
}

// Setup fake data for bluetooth testing
void setupTestBluetooth() {
  for (int i = 0; i < 50; i++) {
    testData[i] = i * 2;
  }

  setupBluetooth();
}

// Parse a string to a JSONVar
JSONVar parseMessage(String data) {
  JSONVar myArray = JSON.parse(data);

  bLog("Message parsed: " + data, BLUETOOTH_MODULE_NAME);

  delay(100);

  BTSerial.println("7");
  
  return myArray;
}

// Send a message in the form of an array to the computer
// Example:
//   sendMessage(0, 2, [10, 123, 21])
//   => sends [0, 2, [...]] to the computer as JSON
void sendMessage(int type, JSONVar content) {
  String jsonString = JSON.stringify(content);

  jsonString.replace(",", " ");
  jsonString.replace("[", "!");
  jsonString.replace("]", "#");

  jsonString = ((String) type) + jsonString;

  
  BTSerial.println(jsonString.c_str());
}
