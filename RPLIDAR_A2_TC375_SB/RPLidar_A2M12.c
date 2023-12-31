/*
 * RPLidar_A2M12.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Umaar
 */

#include "RPLidar_A2M12.h"
#include "stdint.h"
#include "Ifx_Types.h"
#include "IfxAsclin_Asc.h"
#include "IfxPort.h"
#include "ASCLIN_UART.h"
#include "UART_SHELL.h"
#include "rptypes.h"
#include "SystemTimer.h"

void testFunction(void){

    rplidar_response_device_health healthInfo;

    // Call the getHealth function with a specified timeout
    OperationResult result = RPLidar_getHealth(&healthInfo, 1000);
    if(IS_OK(result)){
        println("Device Health: %x", healthInfo.status);
    }
    println("Lidar Response: %x", result);

}

OperationResult RPLidar_sendCommand(uint8 cmd, const void *payload, size_t payloadsize){

    rplidar_cmd_packet pkt_header;
    rplidar_cmd_packet * header = &pkt_header;
    uint8 checksum = 0;

    if (payloadsize && payload) {
        cmd |= RPLIDAR_CMDFLAG_HAS_PAYLOAD;
    }

    header->syncByte = RPLIDAR_CMD_SYNC_BYTE;
    header->cmd_flag = cmd;

    // send header first
    serialWrite((uint8 *) header);

    if (cmd & RPLIDAR_CMDFLAG_HAS_PAYLOAD) {

        checksum ^= RPLIDAR_CMD_SYNC_BYTE;      // Bitwise XOR Operation
        checksum ^= cmd;
        checksum ^= (payloadsize & 0xFF);

        // Calc checksum
        for (size_t pos = 0; pos < payloadsize; ++pos) {
            checksum ^= ((uint8 *)payload)[pos];
        }

        // send size
        uint8 sizebyte = (uint8) payloadsize;
        serialWrite((uint8 *) &sizebyte);

        // send payload
        serialWrite((uint8 *) &payload);

        // send checksum
        serialWrite((uint8 *) &checksum);

    }

    return RESULT_OK;
}


OperationResult RPLidar_waitResponseHeader(rplidar_ans_header *header, uint32 timeout){

    timeout = timeout*1000;     // convert to microsecond
    uint8  recvPos = 0;
    uint32 currentTs = (uint32)getTime();
    uint32 remainingtime;
    uint8 *headerbuf = (uint8*)header;
    while ((remainingtime= (uint32)getTime() - currentTs) <= timeout) {
        int currentbyte = serialRead();
        if (currentbyte<0) continue;
        switch (recvPos) {
        case 0:
            if (currentbyte != RPLIDAR_ANS_SYNC_BYTE1) {
                continue;
            }
            break;
        case 1:
            if (currentbyte != RPLIDAR_ANS_SYNC_BYTE2) {
                recvPos = 0;
                continue;
            }
            break;
        }
        headerbuf[recvPos++] = (uint8)currentbyte;

        if (recvPos == sizeof(rplidar_ans_header)) {
            return RESULT_OK;
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}

OperationResult RPLidar_getHealth(rplidar_response_device_health *healthinfo, uint32 timeout){

    timeout = timeout*1000;     // convert to microsecond
    uint32 currentTs = (uint32)getTime();
    uint32 remainingtime;

    uint8 *infobuf = (uint8 *)&healthinfo;
    uint8 recvPos = 0;

    rplidar_ans_header response_header;
    u_result ans;

    ans = RPLidar_sendCommand(RPLIDAR_CMD_GET_DEVICE_HEALTH, NULL, 0);
    if (IS_FAIL(ans)) {
        return ans;
    }

    ans = RPLidar_waitResponseHeader(&response_header, timeout);
    if (IS_FAIL(ans)) {
        return ans;
    }

    // verify whether we got a correct header
    if (response_header.type != RPLIDAR_ANS_TYPE_DEVHEALTH) {
        return RESULT_INVALID_DATA;
    }

    if ((response_header.size) < sizeof(rplidar_response_device_health)) {
        return RESULT_INVALID_DATA;
    }

    while ((remainingtime=(uint32)getTime() - currentTs) <= timeout) {
        int currentbyte = serialRead();
        if (currentbyte < 0) continue;

        infobuf[recvPos++] = (uint8)currentbyte;

        if (recvPos == sizeof(rplidar_response_device_health)) {
            return RESULT_OK;
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}

