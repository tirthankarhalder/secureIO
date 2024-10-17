void setup() {
  Serial.begin(115200);  // Start serial at 115200 baud rate
  delay(2000);           // 2-second delay for stability

  Serial.println("ESP32-S3 is now printing to the Serial Monitor!");
}

void loop() {
  Serial.println("This message is printed every 2 seconds.");
  delay(2000);  // Print every 2 seconds
}
