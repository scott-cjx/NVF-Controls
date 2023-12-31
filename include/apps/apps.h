/**
 * @file apps.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef APPS_H_
#define APPS_H_

#include <Arduino.h>
#include <stdint.h>
#include "commsHandler.h"

enum PinModeType
{
    DIGITAL,
    ANALOG,
    ANALOG_I2C,
    ANALOG_SPI
};

struct analogSensor_t
{
    uint64_t sensorMax;
    uint64_t sensorMin;
};

class apps
{
private:
    
    uint8_t sensorPin = 0;
    PinModeType sensorModeType;
    uint8_t syncPin = 0;
    bool syncPinStatus = 0;

    analogSensor_t sensorConfig;
    uint64_t sensorCurrVal;

public:
    apps(uint8_t syncPin, uint8_t sensorPin);
    bool begin(analogSensor_t, PinModeType = PinModeType::ANALOG);
    uint8_t readSensorVal();
    void readSyncVal();

    void getRawSensorVal(uint64_t *);
    bool getMappedSensorVal(uint16_t *);

    bool calibrate(CommsHandler *);
    bool calibrateIfRequested(CommsHandler *);
};

#endif /* !APPS_H_ */
