#include <ArduinoJson.h>
#include <Servo.h>
#include "interpolation.h"


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




  float init_theta_11 = 0, init_theta_21 = 90, init_theta_31 = 1, init_theta_41 = 0;



void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud

  base_servo.attach(base);
  shoulder_servo.attach(shoulder);
  elbow_servo.attach(elbow);
  wrist_servo.attach(wrist);


  
   base_servo.write(init_theta_11);
   shoulder_servo.write(init_theta_21);
   elbow_servo.write(init_theta_31);
   wrist_servo.write(init_theta_41);
       
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
        Serial.println(-1*joint_2);
        Serial.print("joint_3: ");
        Serial.println(joint_3);
        Serial.print("joint_4: ");
        Serial.println(-1*joint_4);


        
    quintic_interpolation quintic_theta_1( 0, 200, init_theta_11, joint_1, 0, 0, 0, 0);
    quintic_interpolation quintic_theta_2( 0, 200, init_theta_21, joint_2, 0, 0, 0, 0);
    quintic_interpolation quintic_theta_3( 0, 200, init_theta_31, joint_3, 0, 0, 0, 0);
    quintic_interpolation quintic_theta_4( 0, 200, init_theta_41, joint_4, 0, 0, 0, 0);


        for(int i = 0; i<=200; i++)
        {

          int deg = (int)(quintic_theta_1.current_point(i));
          base_servo.write(deg + 90);
           
          deg = (int)(quintic_theta_2.current_point(i));
          shoulder_servo.write(-1*deg);

          deg = (int)(quintic_theta_3.current_point(i));
          elbow_servo.write(deg);

          deg = (int)(quintic_theta_4.current_point(i));
          wrist_servo.write(-1*deg);
          
          Serial.print(".");
        
        
        }
        Serial.println();
        init_theta_11 = joint_1, init_theta_21 = joint_2, init_theta_31 = joint_3, init_theta_41 = joint_4;
       
      }

      
    }
  }
}
