const String _D_MODULE = "DEFAULT";


void setupLog() {
  Serial.begin(9600);
}


void bLog(String message, String module=_D_MODULE) {
  Serial.println("[" + module + "]: " + message); 
}

void bLogCompleted(String module=_D_MODULE) {
  bLog("Setup completed", module);
}

void bLog_2(String messages[2], String module=_D_MODULE) {
  String message = "";

  for (int i = 0; i <= 2; i++) {
    message += messages[i] + " ";
  }

  bLog(message, module);
}

void bLog_3(String messages[3], String module=_D_MODULE) {
  String message = "";

  for (int i = 0; i <= 3; i++) {
    message += messages[i];
  }
  
  bLog(message, module);
}
