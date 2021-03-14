void blink(int secs) {
  bLog("Blinking", "BLINK");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(secs * 1000);
  digitalWrite(LED_BUILTIN, LOW);
}
