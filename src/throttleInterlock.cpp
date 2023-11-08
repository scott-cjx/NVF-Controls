/**
 * @file throttleInterlock.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "throttleInterlock.h"

/**
 * @brief Construct a new Throttle Interlock:: Throttle Interlock object
 *
 * @param pStateMachine
 */
ThrottleInterlock::ThrottleInterlock(StateMachine *pStateMachine)
{
    this->pStateMachine = pStateMachine;
    // this->pHardwareHandler = pHardwareHandler;
}


bool ThrottleInterlock::begin()
{
    pinMode(BoardDef::PIN_AIR_TRIGGER_OUT, OUTPUT);
    return 1;
}


void ThrottleInterlock::taskThrottleInterlock()
{
    CAR_STATES carState = pStateMachine->getCarState();
    switch (carState)
    {
    case CAR_STATES::GOING:
    {
    }
    case CAR_STATES::READY_2_GO:
    {
        // Activate AIR, close circuit, supply power to motors
        digitalWrite(BoardDef::PIN_AIR_TRIGGER_OUT, 1);
        break;
    }
    case CAR_STATES::STOP:
    {
    }
    case CAR_STATES::STOPPED:
    {
        digitalWrite(BoardDef::PIN_AIR_TRIGGER_OUT, 0);
        break;
    }
    }
}

