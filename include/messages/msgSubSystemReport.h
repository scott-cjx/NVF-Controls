/**
 * @file msgSubSystemReport.h
 * @author Scott CJX (scottcjx.w@gmail.com)
 * @brief
 * @version 0.1
 * @date 08-11-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MSGSUBSYSTEMREPORT_H_
#define MSGSUBSYSTEMREPORT_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct MsgSubSystemReport_t
{
  uint8_t numNodes;
  bool *nodesActive;

  uint8_t dlc;

  MsgSubSystemReport_t(uint8_t numNodes_)
  {
    numNodes = numNodes_;
    nodesActive = (bool *)malloc(sizeof(bool) * numNodes);
    memset(&nodesActive, 0, numNodes);
  }

  MsgSubSystemReport_t()
  {
    MsgSubSystemReport_t(1);
  }

  bool struct_to_msg(uint8_t *dst, uint8_t *dlc)
  {
    int index = 0;
    for (int i = 0; i < numNodes; i++)
    {
      if (nodesActive[i])
      {
        dst[index] |= 1 << (i % 8);
      }

      if (i % 8 == 7)
      {
        index++;
      }
    }
    *dlc = index;
    return 1;
  }

  bool msg_to_struct(uint8_t *from, uint8_t *dlc)
  {
    int index = 0;

    for (int i = 0; i < *dlc; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        if ((from[i] & (1 << j)) != 0)
        {
          nodesActive[index] = true;
        }
        else
        {
          nodesActive[index] = false;
        }
        index++;
      }
    }
  }
};

#endif /* !MSGSUBSYSTEMREPORT_H_ */
