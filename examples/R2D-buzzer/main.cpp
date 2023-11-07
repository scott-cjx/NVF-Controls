/**
 * @file main.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include <NVF_CanBus.h>

#include "boardDef.h"
#include "commsDef.h"
#include "commsHandler.h"

CommsHandler commsHandler;

MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan0(&NVFCanI0, CommsDef::R2D_CAN_ID);
can_frame txBuf0;
can_frame rxBuf0;

systemComms_t R2D_BrainComms;

void setup()
{
    NVFCan0.setup();
    R2D_BrainComms = (systemComms_t){};
    pinMode(BoardDef::PIN_BUZ_PIN, OUTPUT);
}

void loop()
{
    if (NVFCan0.taskLoopRecv(&rxBuf0))
    {
        commsHandler.trnsBuf(&R2D_BrainComms, &rxBuf0);
    }

    // todo: make this be triggered from comms
    bool R2D_Buzzer_trigger = 0;
    digitalWrite(BoardDef::PIN_BUZ_PIN, R2D_Buzzer_trigger);
}
