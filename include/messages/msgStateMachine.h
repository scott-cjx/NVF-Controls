#include <stdint.h>

enum CAR_STATES: uint8_t
{
    READY_2_GO,
    GOING,
    STOP,
    STOPPED
};

enum CAR_STOP_CONDITIONS: uint16_t
{
    /**
     * @brief NA
     * @note
     * no reasons for stop;
     * CAR_STOP_CONDITIONS::NA is mutually exclusive with
     * CAR_STATES::READY_2_GO && CAR_STATES::GOING
     *
     * CAR_STOP_CONDITIONS should be cleared BEFORE
     * CAR_STATES::READY_2_GO set
     *
     * check these conditions to ensure no error on states
     */
    NA,

    /**
     * @brief STARTUP
     * @note
     * car just STARTUP, waiting for systems to react
     */
    STARTUP,

    /**
     * @brief APPS_INVALID
     * @note
     * APPS plasibility check failed:
     * >= 10% difference
     */
    APPS_INVALID,

    /**
     * @brief APPS_HEARTBEAT_LOSS
     * @note
     * no signal from APPS for > 10ms
     */
    APPS_HEARTBEAT_LOSS,

    /**
     * @brief BPPC_INVALID
     * @note
     * BPPC plasibility check failed:
     * //todo
     */
    BPPC_INVALID,

    /**
     * @brief BPPC_HEARTBEAT_LOSS
     * @note
     * no signal from APPS for > 10ms
     */
    BPPC_HEARTBEAT_LOSS,

    /**
     * @brief T_HEARTBEAT_LOSS
     * @note
     * Throttle Interlock (decision maker P1) heartbeat loss ->
     * fallback to failsafe (data collector (decision maker P2)) to initiate shutdown
     */
    T_HEARTBEAT_LOSS,


    /**
     * @brief R2D_HEARTBEAT_LOSS
     * @note
     * no signal from R2D for > 10ms
     */
    R2D_HEARTBEAT_LOSS,

    /**
     * @brief E_STOP
     * @note
     * E_STOP conditions met/ physical e-stop triggered
     */
    E_STOP
};

enum STATEMACHINE_RPT_MODE: uint8_t
{
    HEARTBEAT,
    STD_RPT
};

struct MsgStateMachine_t
{
    const uint8_t       msgDlc = 3;
    uint8_t             report_mode;
    CAR_STATES          carState;
    CAR_STOP_CONDITIONS carStopReason;

    bool struct_to_msg(uint8_t *dst[], uint8_t* dlc)
    {
        *dst[0] = (uint8_t) carState;
        *dst[1] = (uint8_t) carStopReason & 0xFF;
        *dst[2] = (uint8_t) (carStopReason >> 8);
        *dlc = msgDlc;
        return 1;
    }

    bool msg_to_struct(uint8_t *from, uint8_t* dlc)
    {
        if (*dlc != msgDlc) {return 0;}
        carState = (CAR_STATES) from[0];
        carStopReason = (CAR_STOP_CONDITIONS) (from[2] | (from[1] << 8));
        return 1;
    }
};