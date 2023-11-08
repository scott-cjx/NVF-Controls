/**
 * @file commsHandler.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef COMMSHANDLER_H_
#define COMMSHANDLER_H_

#include <Arduino.h>
#include <stdint.h>
#include <time.h>

#include "messages/msgPedalReading.h"
#include "boardDef.h"
#include "commsDef.h"
#include "stateMachine.h"

#include <NVF_CanBus.h>

#define numberCommsInterfaces 5
#define tAcceptableHeartbeatLossMs 10.0

struct systemComms_t
{
    bool initiated = 0;
    uint32_t comms_id = 0xFFFFFFFF;
    time_t tValidHeartbeat = 0xFFFFFFFF;
    double tSinceValidHeartbeatMs = 0xFFFFFFFF;
    can_frame frame = can_frame();
};

class CommsHandler
{
private:
    StateMachine *pStateMachine;
    bool isInit = 0;

public:
    CommsHandler(StateMachine * = nullptr);

    bool begin();
    bool trnsBuf(systemComms_t *, can_frame*); 

    void taskHeartbeatCheck(systemComms_t *, CAR_STOP_CONDITIONS);
    bool taskHeartbeatCheck(systemComms_t *);
    void taskImplausiblyCheck(systemComms_t *, systemComms_t *, CAR_STOP_CONDITIONS);
};

#endif /* !COMMSHANDLER_H_ */
