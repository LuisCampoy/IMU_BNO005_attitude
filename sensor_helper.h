#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <LibPrintf.h>

#define DEBUG 1 // write 0 to turn all the serialprint statements off
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

namespace sensor
{

    Adafruit_BNO055 bno = Adafruit_BNO055();

#define BNO_READY bno.begin()
    int debugDelay = 3000;

    // forward declaration of functions
    void setupSensor();
    uint8_t getTemp();
    void getAccelerationData();
    void getGyroscopeData();
    void getQuaternions();

    void setupSensor()
    {
        #define BNO055_SAMPLERATE_DELAY_MS (100)

        /* Initialise the sensor */
        if (!BNO_READY)
        {
            /* There was a problem detecting the BNO055 ... check your connections */
            Serial.print("No BNO055 detected");
            while (true);
                
        }

        bno.begin();

        delay(BNO055_SAMPLERATE_DELAY_MS);

        bno.setExtCrystalUse(true);

        debugln("setup completed");

        delay(debugDelay);
    }

    uint8_t getTemp()
    {
        debugln("Requesting Temperature...");
        return bno.getTemp();
    }

    void getAccelerationData(float &_accX, float &_accY, float &_accZ)
    {

        imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

        _accX = acc.x();
        _accY = acc.y();
        _accZ = acc.z();

        debugln("requesting acceleration data in m/s^2...");
        debugln("acceleration retreived");

        printf("%.2f, %.2f, %.2f \n", _accX, _accY, _accZ);

        debug("");
        debug(acc.x());
        debug('\t');
        debug(acc.y());
        debug('\t');
        debugln(acc.z());
        debug("");

        delay(BNO055_SAMPLERATE_DELAY_MS);
    }

    void getGyroscopeData(float &_gyrX, float &_gyrY, float &_gyrZ)
    {

        imu::Vector<3> gyr = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

        _gyrX = gyr.x();
        _gyrY = gyr.y();
        _gyrZ = gyr.z();

        debugln("requesting gyroscope data in rads/sec...");
        debugln("gyroscopy retreived");

        printf("%.2f %.2f %.2f \n", _gyrX, _gyrY, _gyrZ);

        debug("");
        debug(_gyrX);
        debug('\t');
        debug(_gyrY);
        debug('\t');
        debugln(_gyrZ);
        debug("");
    }

    void getQuaternions(float &_quatW, float &_quatX, float &_quatY, float &_quatZ)
    {

        imu::Quaternion quat = bno.getQuat();

        _quatW = quat.w();
        _quatX = quat.x();
        _quatY = quat.y();
        _quatZ = quat.z();

        debugln("requesting quaternions data ...");
        debugln("quaternions retreived");

        printf("%.2f %.2f %.2f %.2f \n", _quatW, _quatX, _quatY, _quatZ);

        debug("");
        debug(_quatW);
        debug('\t');
        debug(_quatX);
        debug('\t');
        debug(_quatY);
        debug('\t');
        debugln(_quatZ);
        debug("");
    }

    // imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    //

}