/*
** NANYANG VENTURE FORMULA RACING, 2023
** NVF2-DA-Controls
** File description:
** comms_definitions
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
            R2D
        };

        enum MESSAGES: uint8_t
        {
            RPT_STATEMACHINE,
        };
    };
}

#endif /* !COMMS_DEF_H_ */
