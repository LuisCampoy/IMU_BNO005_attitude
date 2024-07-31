#pragma once

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <LibPrintf.h>

namespace trigonometry
{

    int getPitch();
    int getRoll();

    int getPitch(float _quatW, float _quatX, float _quatY, float _quatZ)
    {

        int _Pitch = -asin(2.0f * (_quatW * _quatY - _quatZ * _quatX));

        debug("Pitch= ");
        debugln(_Pitch);

        return _Pitch;
    }

    int getRoll(float _quatW, float _quatX, float _quatY, float _quatZ)
    {

        int _Roll = atan2(2.0f * (_quatW * _quatX + _quatY * _quatZ), _quatW * _quatW - _quatX * _quatX - _quatY * _quatY + _quatZ * _quatZ);

        debug("Roll= ");
        debugln(_Roll);

        return _Roll;
    }

    // imu::Vector<3> eul = quat.toEuler();

    // double roll = eul.x();
    // double pitch = eul.y();
    // double yaw = eul.z();

}