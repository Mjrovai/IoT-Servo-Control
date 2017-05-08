/***************************************************************************************************************
 *  Servo Control using NodeMCU ESP-12 Develop Kit V1.0 
 *  Including 128x64 OLED Display
 *  Libraries needed:
 *   SSD1306Wire.h: https://github.com/squix78/esp8266-oled-ssd1306
 *   ESP8266WiFi.h: https://github.com/ekstrand/ESP8266wifi
 *  
 *  Servo connected to NodeMCU pin D2
 *  OLED pinout:
 *   - GND goes to ground
 *   - Vin goes to 3.3V
 *   - Data to I2C SDA (GPIO 0 ==>D3)
 *   - Clk to I2C SCL  (GPIO 2 ==>D4)
 *   
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

/* OLED */
#include "SSD1306Wire.h"
#include "Wire.h"
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = 0;
const int SCL_PIN = 2;
SSD1306Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN);

/* Initial pot reading and servo position set the position to neutral */
int PotReading = 1023/2;
int servo1Angle = 90;

void setup()
{
  Serial.begin(115200);
  delay(10);
  servo1.attach(servo1Pin);
  displaySetup();
}

void loop()
{                    
  PotReading = analogRead(potPin);                 // Read Analog data from potenciometer
  servo1Angle = map(PotReading, 3, 1010, 180, 0);  // Map the pot reading to an angle from 0 to 180 
  servo1.write(servo1Angle);                       // Move the servo to a position
  Serial.println(servo1Angle);
  displayAngle();
  delay(1000);                                     // Delay to prevent errors
}

/* Initiate and display setup data on OLED */
void displaySetup()
{
  display.init();         // initialize display
  display.clear();        // Clear display
  display.display();      // Put data on display

  Serial.println("Initiating Servo Control Test");
  display.setFont(ArialMT_Plain_24);
  display.drawString(10, 0, "MJRoBot");  
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 29, "Servo Cntrl Test");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 52, "SW Ver.:");
  display.drawString(45, 52, SW_VERSION);
  display.display();
  delay (3000);
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
