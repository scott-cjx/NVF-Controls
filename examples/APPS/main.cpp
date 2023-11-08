/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_APPS
*/

#include <Arduino.h>
#include <NVF_CanBus.h>

#include "apps/apps.h"
#include "boardDef.h"
#include "commsDef.h"
#include "commsHandler.h"

#ifndef APPS
    #define APPS        1
#endif

#define DELAY_MS    1

void calibrate();

const uint32_t this_can_id = APPS ? CommsDef::PEDAL_NETWORK::CAN_ID::APPS1 : CommsDef::PEDAL_NETWORK::CAN_ID::APPS2;

MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan0(&NVFCanI0, this_can_id);
can_frame txBuf;
can_frame rxBuf;

apps appsHandler(BoardDef::PIN_SYNC_PIN, BoardDef::PIN_ADC_1_0);
uint16_t mappedValue;

void setup()
{
    NVFCan0.setup();

    analogSensor_t appsSensorCfg;
    appsSensorCfg.sensorMin = 0;
    appsSensorCfg.sensorMax = 0;
    appsHandler.begin(appsSensorCfg, PinModeType::ANALOG);

    attachInterrupt(digitalPinToInterrupt(BoardDef::PIN_SYNC_PIN), calibrate, HIGH);
}

void loop()
{
    mappedValue = appsHandler.readSensorVal();
    if(appsHandler.getMappedSensorVal(&mappedValue))
    {
        txBuf.data[1] = (uint8_t) mappedValue & 0xFF; 
        txBuf.data[0] = (uint8_t) (mappedValue >> 8) & 0xFF; 
        txBuf.can_dlc = 2;
        NVFCan0.tx(&txBuf);
    }
    delay(DELAY_MS);
}

void calibrate(void)
{
    // todo
    return;
}