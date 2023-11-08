/**
 * @file throttleInterlock.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef THROTTLEINTERLOCK_H_
#define THROTTLEINTERLOCK_H_

#include <Arduino.h>
#include "boardDef.h"
#include "stateMachine.h"

class ThrottleInterlock
{
private:
    StateMachine *pStateMachine;

public:
    ThrottleInterlock(StateMachine * = nullptr);

    bool begin();

    void taskThrottleInterlock();
};

#endif /* !THROTTLEINTERLOCK_H_ */
