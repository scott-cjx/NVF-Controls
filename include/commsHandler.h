/*
** NANYANG VENTURE FORMULA RACING, 2023
** Untitled (Workspace)
** File description:
** commsHandler
*/

#ifndef COMMSHANDLER_H_
#define COMMSHANDLER_H_

#include <Arduino.h>
#include <stdint.h>
#include <time.h>

#include "boardDef.h"
#include "commsDef.h"
#include "stateMachine.h"

#include <NVF_CanBus.h>

#define numberCommsInterfaces 5
#define tAcceptableHeartbeatLossMs 10.0

struct systemComms_t
{
    bool initiated = 0;
    static uint32_t comms_id;
    time_t tValidHeartbeat;
    double tSinceValidHeartbeatMs;
    can_frame frame;
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
    void taskImplausiblyCheck(systemComms_t *, systemComms_t *, CAR_STOP_CONDITIONS);
};

#endif /* !COMMSHANDLER_H_ */
