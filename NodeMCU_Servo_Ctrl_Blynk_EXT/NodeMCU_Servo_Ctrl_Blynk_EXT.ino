/***************************************************************************************************************
 *  Servo Control using NodeMCU ESP-12 Develop Kit V1.0 
 *  Including Blynk Control
 *  Including 128x64 OLED Display
 *  Libraries needed:
 *   SSD1306Wire.h: https://github.com/squix78/esp8266-oled-ssd1306
 *   ESP8266WiFi.h: https://github.com/ekstrand/ESP8266wifi
 *   BlynkSimpleEsp8266.h: http://www.blynk.cc
 *  
 *  Servo connected to NodeMCU pin D2
 *  OLED pinout:
 *   - GND goes to ground
 *   - Vin goes to 3.3V
 *   - Data to I2C SDA (GPIO 0 ==>D3)
 *   - Clk to I2C SCL  (GPIO 2 ==>D4)
 *   
 *  Developed by MJRovai V.1 08 May 2017 
 ********************************************************************************************************************************/
#define SW_VERSION "ServoCtrlBlynk_V.1" 

/*NodeMCU */
#include <ESP8266WiFi.h>
char ssid [] = "YOUR SSID";
char pass [] = "YOUR PASSWORD";

/* Blynk */
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
char auth [] = "YOUR AUTH TOKEN"; // Servo Control Project // Servo Control Project

/* OLED */
#include "SSD1306Wire.h"
#include "Wire.h"
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = 0;
const int SCL_PIN = 2;
SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN);

/* Servo */
#define servo1Pin D2
#include <Servo.h>
Servo servo1;

/* Initial pot reading and servo position set the position to neutral */
#define potPin A0
int potReading = 1023/2;
int servo1Angle = 90;

/* Reads slider in the Blynk app and writes the value to "potReading" variable */
BLYNK_WRITE(V0) 
{
  potReading = param.asInt();
}

/* Display servo position on Blynk app */
BLYNK_READ(V1) 
{
  Blynk.virtualWrite(V1, servo1Angle);
}

void setup () 
{
  Serial.begin(115200); 
  servo1.attach(servo1Pin);
  displaySetup();
  Blynk.begin(auth, ssid, pass);
}

void loop() 
{
  Blynk.run();
  //PotReading = analogRead(potPin);               // Read Analog data from potenciometer not used here
  servo1Angle = map(potReading, 0, 1023, 0, 180);  // Map the pot reading to an angle from 0 to 180 
  servo1.write(servo1Angle);                       // Move the servo to a position
  displayAngle();
  delay (200);
}

/* Initiate and display setup data on OLED */
void displaySetup()
{
  display.init();         // initialize display
  display.clear();        // Clear display
  display.display();      // Put data on display
}

/*  Display Servo position */
void displayAngle()
{
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 0, "Servo Control");
  display.drawString(0, 45, "POSITION:" );
  display.setFont(ArialMT_Plain_24);
  display.drawString(80, 40, String(servo1Angle));
  display.display();
}

