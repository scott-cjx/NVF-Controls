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
#include "boardDef.h"
#include "commsDef.h"
#include "commsHandler.h"
#include "stateMachine.h"
#include "throttleInterlock.h"

#include <NVF_CanBus.h>

StateMachine stateMachine;
CommsHandler commsHandler;
ThrottleInterlock throttleInterlock;

//FIRST CAN Network
MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan0(&NVFCanI0, CommsDef::VCU_NETWORK::VCU1);
can_frame rxBuf0;
can_frame txBuf0;

//Second CAN Network
MCP_CAN NVFCanI1(BoardDef::PIN_CANSPI_CSN2);
NVF_CanBus NVFCan1(&NVFCanI1, CommsDef::R2D_NETWORK::VCU1);
can_frame rxBuf1;
can_frame txBuf1;

void setup()
{
    stateMachine = StateMachine();
    commsHandler = CommsHandler(&stateMachine);
    throttleInterlock = ThrottleInterlock(&stateMachine);

    NVFCan0.setup();
    NVFCan1.setup();

bool initiated = 0;
    static uint32_t comms_id;
    time_t tValidHeartbeat;
    double tSinceValidHeartbeatMs;
    can_frame frame;
    
    // // define buffers for comms that i want to interact with
    // APPS1Comms = (systemComms_t) {0, CommsDef::APPS1_CAN_ID, -1, -1, (can_frame)}{});
    // APPS2Comms = (systemComms_t) {0, CommsDef::APPS2_CAN_ID, -1, -1, (can_frame)}{});
    // BPPC1Comms = (systemComms_t) {0, CommsDef::BPPC1_CAN_ID, -1, -1, (can_frame)}{});
    // BPPC2Comms = (systemComms_t) {0, CommsDef::BPPC2_CAN_ID, -1, -1, (can_frame)}{});

}


void loop()
{   
    // // get can frame
    // if (NVFCan0.taskLoopRecv(&rxBuf0))
    // {
    //     if (commsHandler.trnsBuf(&APPS1Comms, &rxBuf0)){}
    //     else if (commsHandler.trnsBuf(&APPS2Comms, &rxBuf0)){}
    //     else if (commsHandler.trnsBuf(&BPPC1Comms, &rxBuf0)){}
    //     else if (commsHandler.trnsBuf(&BPPC2Comms, &rxBuf0)){}
    //     else if (commsHandler.trnsBuf(&R2DComms, &rxBuf0)){}
    //     else {/*message not for target*/}
    // }

    // // get statuses
    // commsHandler.taskHeartbeatCheck(&APPS1Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    // commsHandler.taskHeartbeatCheck(&APPS2Comms, CAR_STOP_CONDITIONS::APPS_HEARTBEAT_LOSS);
    // commsHandler.taskImplausiblyCheck(&APPS1Comms, &APPS2Comms, CAR_STOP_CONDITIONS::APPS_INVALID);

    // commsHandler.taskHeartbeatCheck(&BPPC1Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    // commsHandler.taskHeartbeatCheck(&BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_HEARTBEAT_LOSS);
    // commsHandler.taskImplausiblyCheck(&BPPC1Comms, &BPPC2Comms, CAR_STOP_CONDITIONS::BPPC_INVALID);

    // commsHandler.taskHeartbeatCheck(&R2DComms, CAR_STOP_CONDITIONS::R2D_HEARTBEAT_LOSS);

    // //check for R2D state 
    // if (R2DComms.frame.data[0] == 0xEE && stateMachine.getCarState() == (uint8_t) 3){
    //     stateMachine.setCarStateReady();
    // }

    // throttleInterlock.taskThrottleInterlock();

    // // aggregate throttle values
    // {
    //     /***
    //      * perform checks ie.
    //      * if brake pressed, throttle = 0
    //      * if implausible, throttle = 0
    //      * ...
    //     */
    //     // 
    //     // throttle = avg(APPS1Comms.%, APPS2Comms.%)
    // }

    // txBuf0.data[0] = (uint8_t) stateMachine.getCarState();
    // txBuf0.data[1] = (uint8_t) stateMachine.getCarStopReason();
    // // txBuf0.data[2] = throttle; ...
    // // txBuf0.dlc = ?
    // if (!NVFCan0.tx(&txBuf0)) { /* msg didnt send */ }

    // // rx and process rxbuf1 from network 2
    // // txBuf1.data[] ... = throttle ... 
    // // txBuf1.dlc = ?
    // if (!NVFCan1.tx(&txBuf1)) { /* msg didnt send */ }
    

    // NO_DELAY
}