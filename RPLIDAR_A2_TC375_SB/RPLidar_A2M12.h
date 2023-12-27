/*
 * RPLidar_A2M12.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Umaar
 */

#ifndef RPLIDAR_A2M12_H_
#define RPLIDAR_A2M12_H_

#include "RPLidar_Includes/rplidar_cmd.h"
#include "RPLidar_Includes/rptypes.h"
#include "Ifx_Types.h"
#include "stdbool.h"

typedef struct
{
        float distance;
        float angle;
        uint8 quality;
        bool startBit;
} RPLidarMeasurement;


enum RPLidarSettings
{
    RPLIDAR_SERIAL_BAUDRATE_9600    = 9600,
    RPLIDAR_SERIAL_BAUDRATE_115200  = 115200,
    RPLIDAR_SERIAL_BAUDRATE_256000  = 256000,
    RPLIDAR_DEFAULT_TIMEOUT = 500,
};


typedef struct RPLidar
{
        RPLidarMeasurement currentMeasurement;
} RPLidar;

OperationResult RPLidar_getHealth(RPLidar *self, rplidar_response_device_health *healthinfo, uint32 timeout);

OperationResult RPLidar_getDeviceInfo(RPLidar *self, rplidar_response_device_info_t *info, _u32 timeout);

OperationResult RPLidar_stop(RPLidar *self);

OperationResult RPLidar_startScan(RPLidar *self, bool force, _u32 timeout);

OperationResult RPLidar_waitPoint(RPLidar *self, _u32 timeout);

void RPLidar_getCurrentPoint(const RPLidar *self, RPLidarMeasurement *measurement);

OperationResult RPLidar_sendCommand(RPLidar *self, _u8 cmd, const void *payload, size_t payloadsize);

OperationResult RPLidar_waitResponseHeader(RPLidar *self, rplidar_ans_header_t *header, _u32 timeout);


#endif /* RPLIDAR_A2M12_H_ */
