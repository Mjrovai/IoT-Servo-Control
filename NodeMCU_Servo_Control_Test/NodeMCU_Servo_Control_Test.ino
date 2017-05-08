/***************************************************************************************************************
 *  Servo Control using NodeMCU ESP-12 Develop Kit V1.0 
 *  Servo connected to NodeMCU pin D2

 *  Developed by MJRovai V.1 06 May 2017 
 ********************************************************************************************************************************/
#define SW_VERSION "ServoCtrlTst_V.1" 

/* NodeMCU */
#include <ESP8266WiFi.h>

/* Servo */
#define servo1Pin D2
#include <Servo.h>
Servo servo1;

/* potenciometer */
#define potPin A0

/* Initial pot reading and servo position set the position to neutral */
int PotReading = 1023/2;
int servo1Angle = 90;

void setup()
{
  Serial.begin(115200);
  delay(10);
  servo1.attach(servo1Pin);
}

void loop()
{                    
  PotReading = analogRead(potPin);                 // Read Analog data from potenciometer
  servo1Angle = map(PotReading, 3, 1010, 180, 0);  // Map the pot reading to an angle from 0 to 180 
  servo1.write(servo1Angle);                       // Move the servo to a position
  Serial.println(servo1Angle);
  delay(1000);                                     // Delay to prevent errors
}

