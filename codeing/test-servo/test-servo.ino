#include <ESP32Servo.h>
#include "esp_camera.h"

Servo lidServo;

void setup() {
  sensor_t *s = esp_camera_sensor_get();
  Serial.printf("Camera PID: 0x%x\n", s->id.PID);
  lidServo.attach(3); 
}

void loop() {
  lidServo.write(0);  // start closed
  delay(2000);
  Serial.print("Here1");
  
  lidServo.write(90);  // open
  delay(3000);

  Serial.print("Here2");
  
  lidServo.write(0); 
}