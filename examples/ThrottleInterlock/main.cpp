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
#include "throttleInterlock.h"
#include "stateMachine.h"

#include "messages/msgStateMachine.h"

#ifndef TI_ID
#define TI_ID 0
#endif

bool chk_stateMachine(bool *);

CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;
StateMachine stateMachine;

// FIRST CAN Network
MCP_CAN NVFCanI(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan(&NVFCanI,
                  TI_ID ? CommsDef::PEDAL_NETWORK::THROTTLEINTERLOCK1 : CommsDef::PEDAL_NETWORK::THROTTLEINTERLOCK2);
can_frame rxBuf;
can_frame txBuf;

systemComms_t VCU1Comms;
systemComms_t VCU2Comms;
MsgStateMachine_t msgStateMachine1;
MsgStateMachine_t msgStateMachine2;

void setup()
{
    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    throttleInterlock = ThrottleInterlock(&stateMachine);

    NVFCan.setup();

    // define buffers for comms that i want to interact with
    VCU1Comms.comms_id = CommsDef::PEDAL_NETWORK::CAN_ID::VCU1;
    VCU2Comms.comms_id = CommsDef::PEDAL_NETWORK::CAN_ID::VCU1;
}

void loop()
{
    if (NVFCan.taskLoopRecv(&rxBuf))
    {
        if (commsHandler.trnsBuf(&VCU1Comms, &rxBuf))
        {
        }
        else if (commsHandler.trnsBuf(&VCU2Comms, &rxBuf))
        {
        }
        else
        { /*message not for target*/
        }
    }

    if(chk_stateMachine())
    {
    }

    // NO_DELAY
}

bool chk_stateMachine()
{
    msgStateMachine1.msg_to_struct(VCU1Comms.frame.data, &VCU1Comms.frame.can_dlc);
    msgStateMachine2.msg_to_struct(VCU2Comms.frame.data, &VCU2Comms.frame.can_dlc);
    
    bool stop1 = (msgStateMachine1.report_mode == STD_RPT) && (msgStateMachine1.carState == CAR_STATES::STOP);
    bool stop2 = (msgStateMachine2.report_mode == STD_RPT) && (msgStateMachine2.carState == CAR_STATES::STOP);
    return (stop1 || stop2);
}