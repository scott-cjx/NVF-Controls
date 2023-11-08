/**
 * @file commsDef.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef COMMS_DEF_H_
#define COMMS_DEF_H_

#include <stdint.h>
#include <NVF_CanBus.h>

namespace CommsDef
{
    const uint8_t CAN_SPEED = CAN_500KBPS;

    namespace  PEDAL_NETWORK
    {
        enum CAN_ID: uint32_t
        {
            VCU1, // Statemachine1
            VCU2, // Statemachine2
            APPS1,
            APPS2,
            BPPC1,
            BPPC2,
            THROTTLEINTERLOCK1,
            THROTTLEINTERLOCK2
        };
        enum MESSAGES: uint8_t
        {
            RPT_APPS,
            RPT_BPPC,
            RPT_STATEMACHINE,
            RPT_THROTTLE,
        };
    };

    namespace VCU_NETWORK
    {
        enum CAN_ID: uint32_t
        {
            VCU1, // Statemachine1
            VCU2, // Statemachine2
            R2D_BRAIN
        };

        enum MESSAGES: uint8_t
        {
            RPT_STATEMACHINE,
        };
    };

    namespace R2D_NETWORK
    {
        enum CAN_ID: uint32_t
        {
            VCU1, // Statemachine1
            VCU2, // Statemachine2
            R2D_BRAIN,
            R2D_STARTER,
            R2D_BUZZER
        };

        enum MESSAGES: uint8_t
        {
            RPT_STATEMACHINE,
        };
    };
}

#endif /* !COMMS_DEF_H_ */
