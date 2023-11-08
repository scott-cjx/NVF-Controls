/**
 * @file commsHandler.cpp
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "commsHandler.h"
#include <time.h>

CommsHandler::CommsHandler(StateMachine *pStateMachine)
{
  this->pStateMachine = pStateMachine;
}

bool CommsHandler::begin()
{
  if (this->pStateMachine == nullptr)
  {
    return 0;
  }

  this->isInit = 1;
  return 1;
}

/**
 * @brief
 * @param comsInterface
 * @param CAN_frame
 * copy message from buf
 * return true if same id
 */
bool CommsHandler::trnsBuf(systemComms_t *pCommsInterface, can_frame *buf)
{
  if (buf->can_id == pCommsInterface->comms_id)
  {
    pCommsInterface->frame.can_id = buf->can_id;
    pCommsInterface->frame.can_dlc = buf->can_dlc;
    memcpy(pCommsInterface->frame.data, buf->data, sizeof(buf->data));

    pCommsInterface->tValidHeartbeat = millis();
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief
 *
 * @param commsInterface
 * @return 1 if failed
 */
bool CommsHandler::taskHeartbeatCheck(systemComms_t *pCommsInterface)
{
  pCommsInterface->tSinceValidHeartbeatMs = millis() - pCommsInterface->tValidHeartbeat;
  return !(tAcceptableHeartbeatLossMs <= pCommsInterface->tSinceValidHeartbeatMs);
}

void CommsHandler::taskHeartbeatCheck(
    systemComms_t *pCommsInterface,
    CAR_STOP_CONDITIONS stopReasonIfFailed
    // CAR_STOP_CONDITIONS stopReasonIfFailed = CAR_STOP_CONDITIONS::NA /* prep for pair testing */
)
{
  pCommsInterface->tSinceValidHeartbeatMs = millis() - pCommsInterface->tValidHeartbeat;

  if (this->pStateMachine->getCarStopReason() == CAR_STOP_CONDITIONS::STARTUP)
  {
    // car startup, need reboot
  }
  else if (tAcceptableHeartbeatLossMs <= pCommsInterface->tSinceValidHeartbeatMs)
  {
    this->pStateMachine->setCarStateStop(stopReasonIfFailed);
  }
}

/**
 * @brief
 *
 * @param pCommsInterface1
 * @param pCommsInterface2
 * @param stopReasonIfFailed
 *
 * @note
 * this function checks if APPS/BPPC pair value are valid
 * stopReasonIfFailed should only be APPS_INVALID OR BPPC_INVALID
 */
void CommsHandler::taskImplausiblyCheck(
    systemComms_t *pCommsInterface1,
    systemComms_t *pCommsInterface2,
    CAR_STOP_CONDITIONS stopReasonIfFailed)
{
  bool isValid = 0;

  MsgPedalReading_t msgPedalReading1;
  msgPedalReading1.msg_to_struct(pCommsInterface1->frame.data, &pCommsInterface1->frame.can_dlc);

  MsgPedalReading_t msgPedalReading2;
  msgPedalReading2.msg_to_struct(pCommsInterface2->frame.data, &pCommsInterface2->frame.can_dlc);

  if ((msgPedalReading1.report_mode != PEDAL_RPT_MODE::MAPPED) ||
      (msgPedalReading2.report_mode != PEDAL_RPT_MODE::MAPPED))
  {
    return;
  }

  uint8_t val1 = msgPedalReading1.mappedReading;
  uint8_t val2 = msgPedalReading2.mappedReading;
  uint8_t diff = abs(val1 - val2);

  isValid = (diff < 10);

  if (!isValid)
    this->pStateMachine->setCarStateStop(stopReasonIfFailed);
}
