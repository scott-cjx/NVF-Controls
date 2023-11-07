/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** main_APPS
*/

#include <Arduino.h>
#include "boardDef.h"
#include "commsDef.h"
#include "commsHandler.h"
#include "stateMachine.h"

#include <NVF_Can.h>

#include "NVF2/APPS/apps.h"

#define APPS        1
#define DELAY_MS    1

#ifdef APPS
    #if APPS == 1
        const uint32_t this_can_id = CommsDef::APPS1_CAN_ID;
    #elif APPS == 2
        const uint32_t this_can_id = CommsDef::APPS2_CAN_ID;
    #endif
#endif
MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_Can NVFCan0(&NVFCanI0, this_can_id);
can_frame txBuf;

apps appsHandler(BoardDef::PIN_SYNC_PIN, BoardDef::PIN_ADC_1_0);
StateMachine stateMachine;
CommsHandler commsHandler;

void setup()
{
    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    commsHandler.begin();

    // todo make this dynamic
    // commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);

    // nvfcan setup
    NVFCan0.setup();

    // define buffers for comms that i want to interact with
    // TIComms = systemComms_t();
    // TIComms.comms_id = CommsDef::THROTTLEINTERLOCK_CAN_ID;
    // APPSComms = systemComms_t();
    analogSensor_t appsSensorCfg;
    // get values from eeprom
    appsSensorCfg.sensorMin = 0;
    appsSensorCfg.sensorMax = 0;
    appsHandler.begin(appsSensorCfg, PinModeType::ANALOG);

    Serial.begin(115200);

    if(appsHandler.calibrateIfRequested(&commsHandler))
    {
        // meaning sensor did calibrate, restart
        // restart node
        // inform system node restarting.
    }
    // commsHandler.CAN_begin(this_can_id, BoardDef::PIN_CANSPI_CSN);

}

void loop()
{
    uint8_t mappedValue = appsHandler.readSensorVal();
    if(appsHandler.getMappedSensorVal(&mappedValue)){
        txBuf.data[0] = (uint8_t) mappedValue;
        txBuf.data[2] = (uint8_t) mappedValue & 0xFF; 
        txBuf.data[1] = (uint8_t) (mappedValue >> 8) & 0xFF; 

        txBuf.can_dlc = 3;
    }

    // might possible problems because of loss of data bits (msb/lsb??)
    // adc res -> 1023, uint8_t max = 255;
    // adc res > max data in a byte; sol: split data into 2 bytes
    // data[0] = val && 0xFF;
    // data[1] = val << 8;
    // check this
    
    if (NVFCan0.tx(&txBuf)){
        Serial.println("message delivered successfully");
    }

    else{
        Serial.println("message delivered fail.");
    }
    delay(DELAY_MS);
}

