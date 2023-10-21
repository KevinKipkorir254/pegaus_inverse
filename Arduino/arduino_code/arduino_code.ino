#include <ArduinoJson.h>
#include <Servo.h>


//declaring space requirements
StaticJsonDocument<200> doc;


int base = 11;
int shoulder = 12;
int elbow = 13;
int wrist = 6;

Servo base_servo;
Servo shoulder_servo;
Servo elbow_servo;
Servo wrist_servo;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud

  base_servo.attach(base);
  shoulder_servo.attach(shoulder);
  elbow_servo.attach(elbow);
  wrist_servo.attach(wrist);
}

void loop() {
  if (Serial.available()) {
    
    Serial.flush(); // Flush the serial buffer
    String receivedData = Serial.readStringUntil('\n'); // Read data until a newline character is encountered
    
    if (receivedData.length() > 0) {

      
      // Parse the JSON data
      DeserializationError error = deserializeJson(doc, receivedData);
      
      if (error) {
        Serial.print("JSON parsing error: ");
        Serial.println(error.c_str());
      } else {
        // Access JSON values
        int joint_1 = doc["joint_1"];
        int joint_2 = doc["joint_2"];
        int joint_3 = doc["joint_3"];
        int joint_4 = doc["joint_4"];
        
        // Use the joint values as needed
        Serial.print("Received JSON data - joint_1: ");
        Serial.println(joint_1);
        Serial.print("joint_2: ");
        Serial.println(joint_2);
        Serial.print("joint_3: ");
        Serial.println(joint_3);
        Serial.print("joint_4: ");
        Serial.println(joint_4);


        
       base_servo.write(joint_1);
       shoulder_servo.write(joint_2);
       elbow_servo.write(joint_3);
       wrist_servo.write(joint_4);
      }

      
    }
  }
}
