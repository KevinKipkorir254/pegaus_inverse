void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  if (Serial.available()) {
    
    Serial.flush(); // Flush the serial buffer
    String receivedData = Serial.readStringUntil('\n'); // Read data until a newline character is encountered
    
    if (receivedData.length() > 0) {
      receivedData.trim(); 
      Serial.print(receivedData);
    }
  }
}
