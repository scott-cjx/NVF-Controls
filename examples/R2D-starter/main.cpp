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
#include <NVF_CanBus.h>

#include "boardDef.h"
#include "commsDef.h"
#include "commsHandler.h"

#define DELAY 1

CommsHandler commsHandler;

MCP_CAN NVFCanI0(BoardDef::PIN_CANSPI_CSN);
NVF_CanBus NVFCan0(&NVFCanI0, CommsDef::R2D_NETWORK::R2D_STARTER);
can_frame txBuf0;

void setup()
{
  NVFCan0.setup();

  pinMode(BoardDef::PIN_R2D_PIN, INPUT);
  pinMode(BoardDef::PIN_ADC_1_0, INPUT);
}

void loop()
{
  bool brakeState = digitalRead(BoardDef::PIN_R2D_PIN);
  bool controlState = digitalRead(BoardDef::PIN_ADC_1_0);
  txBuf0.data[0] = (0xF0 & brakeState ? 0: 0xF) | (0x0F & controlState ? 0: 0xF);
  txBuf0.can_dlc = 1;
  NVFCan0.tx(&txBuf0);

  if (! (brakeState && controlState))
  {
    delay(DELAY);
  }
}
