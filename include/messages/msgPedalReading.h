/**
 * @file msgPedalReading.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief 
 * @version 0.1
 * @date 08-11-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MSGPEDALREADING_H_
#define MSGPEDALREADING_H_

#include <stdint.h>

enum PEDAL_RPT_MODE : uint8_t
{
  // HEARTBEAT,
  RAW,
  MAPPED,
  CALIBRATING
};

struct MsgPedalReading_t
{
  uint8_t report_mode;
  uint16_t rawReading;
  uint16_t minRawReading;
  uint16_t maxRawReading;
  uint8_t mappedReading;

  bool struct_to_msg(uint8_t *dst[], uint8_t *dlc)
  {
    *dst[0] = report_mode;
    switch (report_mode)
    {
    case PEDAL_RPT_MODE::CALIBRATING:
      // raw reading
      *dst[1] = (uint8_t)rawReading & 0xFF;
      *dst[2] = (uint8_t)(rawReading >> 8);

      // min raw
      *dst[3] = (uint8_t)minRawReading & 0xFF;
      *dst[4] = (uint8_t)(minRawReading >> 8);

      // max raw
      *dst[5] = (uint8_t)maxRawReading & 0xFF;
      *dst[6] = (uint8_t)(maxRawReading >> 8);

      *dlc = 7;
      break;
    case PEDAL_RPT_MODE::MAPPED:
      *dst[1] = (uint8_t)mappedReading;
      *dlc = 2;
      break;
    case PEDAL_RPT_MODE::RAW:
      *dst[1] = (uint8_t)rawReading & 0xFF;
      *dst[2] = (uint8_t)(rawReading >> 8);
      *dlc = 3;
      break;
    // case PEDAL_RPT_MODE::HEARTBEAT:
    default:
      return 0;
      break;
    }

    return 1;
  }

  bool msg_to_struct(uint8_t *from, uint8_t *dlc)
  {
    if (*dlc < 1)
      return 0;
    report_mode = from[0];

    switch (report_mode)
    {
    case PEDAL_RPT_MODE::MAPPED:
      if (*dlc != 2)
        return 0;
      mappedReading = from[1];
      break;

    case PEDAL_RPT_MODE::RAW:
      if (*dlc != 3)
        return 0;
      rawReading = (uint16_t)(from[2] | (from[1] << 8));

    case PEDAL_RPT_MODE::CALIBRATING:
      if (*dlc != 7)
        return 0;
      rawReading = (uint16_t)(from[2] | (from[1] << 8));
      minRawReading = (uint16_t)(from[4] | (from[3] << 8));
      maxRawReading = (uint16_t)(from[6] | (from[5] << 8));

    case PEDAL_RPT_MODE::HEARTBEAT:
    default:
      break;
    }
  }
};

#endif /* !MSGPEDALREADING_H_ */
