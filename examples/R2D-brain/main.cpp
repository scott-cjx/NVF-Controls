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
NVF_CanBus NVFCan0(&NVFCanI0, CommsDef::VCU_NETWORK::R2D_BRAIN);
can_frame txBuf0;
can_frame rxBuf0;

MCP_CAN NVFCanI1(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan1(&NVFCanI1, CommsDef::R2D_NETWORK::R2D_BRAIN);
can_frame txBuf1;
can_frame rxBuf1;

void setup() 
{
  NVFCan0.setup();
  commsHandler = CommsHandler();
}

void loop() 
{
    if(NVFCan0.taskLoopRecv(&txBuf0))
    {
        
    }

    if(NVFCan1.taskLoopRecv(&txBuf1))
    {

    }

}
