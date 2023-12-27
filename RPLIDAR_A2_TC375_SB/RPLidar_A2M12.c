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

OperationResult RPLidar_getHealth(RPLidar *self, rplidar_response_device_health *healthinfo, uint32 timeout){
    uint32 currentTs = millis();
    uint32 remainingtime;

    uint8 *infobuf = (uint8 *)&healthinfo;
    uint8 recvPos = 0;

    rplidar_ans_header response_header;
    u_result  ans;

    {
        if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_GET_DEVICE_HEALTH, NULL, 0))) {
            return ans;
        }

        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != RPLIDAR_ANS_TYPE_DEVHEALTH) {
            return RESULT_INVALID_DATA;
        }

        if ((response_header.size) < sizeof(rplidar_response_device_health)) {
            return RESULT_INVALID_DATA;
        }

        while ((remainingtime=millis() - currentTs) <= timeout) {
            int currentbyte = _bined_serialdev->read();
            if (currentbyte < 0) continue;

            infobuf[recvPos++] = currentbyte;

            if (recvPos == sizeof(rplidar_response_device_health)) {
                return RESULT_OK;
            }
        }
    }
    return RESULT_OPERATION_TIMEOUT;
}


