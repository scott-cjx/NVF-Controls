/**
 * @file stateMachine.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "stdint.h"
#include "time.h"

#include "messages/msgStateMachine.h"

class StateMachine
{
private:
    CAR_STATES carState;
    CAR_STOP_CONDITIONS carStopReason;

public:
    StateMachine();

    /** car states */
    CAR_STATES getCarState(void);
    void setCarState(CAR_STATES);
    void setCarStateStop(CAR_STOP_CONDITIONS);
    void setCarStateStopped(void);
    void setCarStateReady(void);
    void setCarStateGoing(void);
    /** car states */

    /** car stop reason */
    CAR_STOP_CONDITIONS getCarStopReason(void);
    void setCarStopReason(CAR_STOP_CONDITIONS);
    /** car stop reason */

    void getCarStatusCode(uint8_t *);
};

#endif /* !STATEMACHINE_H_ */
