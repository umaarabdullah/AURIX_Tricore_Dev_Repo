/*
 * rplidar_protocol.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Umaar
 */

#ifndef RPLIDAR_INCLUDES_RPLIDAR_PROTOCOL_H_
#define RPLIDAR_INCLUDES_RPLIDAR_PROTOCOL_H_

#include "Ifx_Types.h"

// RP-Lidar Input Packets
#define RPLIDAR_CMD_SYNC_BYTE        0xA5
#define RPLIDAR_CMDFLAG_HAS_PAYLOAD  0x80

#define RPLIDAR_ANS_SYNC_BYTE1       0xA5
#define RPLIDAR_ANS_SYNC_BYTE2       0x5A

#define RPLIDAR_ANS_PKTFLAG_LOOP     0x1

typedef struct _rplidar_cmd_packet {
        uint8 syncByte; //must be RPLIDAR_CMD_SYNC_BYTE
        uint8 cmd_flag;
        uint8 size;
        uint8 data[];
} rplidar_cmd_packet;

typedef struct _rplidar_ans_header {
        uint8   syncByte1; // must be RPLIDAR_ANS_SYNC_BYTE1
        uint8   syncByte2; // must be RPLIDAR_ANS_SYNC_BYTE2
        uint32  size:30;
        uint32  subType:2;
        uint8   type;
} rplidar_ans_header;


#endif /* RPLIDAR_INCLUDES_RPLIDAR_PROTOCOL_H_ */