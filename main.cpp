/*
Project started 7/6/2023
Based on Paul McWhorter's tutorial using an BO055 9-axis module by Adafruit
Compiles for NANO
Works as intended
Roll and Pitch modules (math_helper) untested
Last revision 8/10/2023
*/

#include <Arduino.h>
#include <LibPrintf.h>

#include "sensor_helper.h"
#include "math_helper.h"
#include "lcd_helper.h"

#define DEBUG 1 // write 0 to turn all the serialprint statements off
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

int debugDelay = 3000;

void setup()
{

  // initialise serial monitor
  Serial.begin(115200);

  // initialise IMU sensor
  sensor::setupSensor();
}

void loop()
{
  float accX;
  float accY;
  float accZ;

  float gyrX;
  float gyrY;
  float gyrZ;

  float quatW;
  float quatX;
  float quatY;
  float quatZ;

  uint8_t temp = sensor::getTemp();

  debug("Temperature is ");
  debugln(temp);
  debugln(" C");

  sensor::getAccelerationData(accX, accY, accZ); // in m/sec^2

  printf("acceleration data passed by reference \n %.2f, %.2f, %.2f \n", accX, accY, accZ); // will not need this. Will print from the sensor helper
  printf("\n");

  sensor::getGyroscopeData(gyrX, gyrY, gyrZ); // in radians/sec

  printf("gyroscope data passed by reference \n %.2f, %.2f, %.2f \n", gyrX, gyrY, gyrZ); // will not need this. Will print from the sensor helper
  printf("\n");

  sensor::getQuaternions(quatW, quatX, quatY, quatZ);

  printf("quaternions data passed by reference \n %.2f, %.2f, %.2f, %.2f \n", quatW, quatX, quatY, quatZ); // will not need this. Will print from the sensor helper
  printf("\n");

  delay(debugDelay);

  int Pitch = trigonometry::getPitch(quatW, quatX, quatY, quatZ);

  int Roll = trigonometry::getRoll(quatW, quatX, quatY, quatZ);
  
 attitude::tftsetup();

 attitude::updateHorizon(Pitch, Roll);

}
