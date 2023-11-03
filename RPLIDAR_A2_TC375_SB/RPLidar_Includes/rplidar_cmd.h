/*
 * rplidar_cmd.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Umaar
 */

#ifndef RPLIDAR_INCLUDES_RPLIDAR_CMD_H_
#define RPLIDAR_INCLUDES_RPLIDAR_CMD_H_

#include "rplidar_protocol.h"

/************************** Commands **************************/

// Commands without payload and response
#define RPLIDAR_CMD_STOP               0x25
#define RPLIDAR_CMD_SCAN               0x20
#define RPLIDAR_CMD_FORCE_SCAN         0x21
#define RPLIDAR_CMD_RESET              0x40

// Commands without payload but have response
#define RPLIDAR_CMD_GET_DEVICE_INFO      0x50
#define RPLIDAR_CMD_GET_DEVICE_HEALTH    0x52

/************************** Response **************************/
#define RPLIDAR_ANS_TYPE_MEASUREMENT      0x81

#define RPLIDAR_ANS_TYPE_DEVINFO          0x4
#define RPLIDAR_ANS_TYPE_DEVHEALTH        0x6

#define RPLIDAR_STATUS_OK                 0x0
#define RPLIDAR_STATUS_WARNING            0x1
#define RPLIDAR_STATUS_ERROR              0x2

#define RPLIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define RPLIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1

typedef struct {
    uint8   sync_quality;       // Bit 0: Sync bit, Bit 1: Inverse sync, Bits 2-7: Laser quality (6 bits)
    uint16  angle_q6_checkbit;  // Bit 0: Check bit, Bits 1-15: Heading angle in degrees [0-360) stored as fixed-point. Actual heading = angle_q6/64.0 Degree
    uint16  distance_q2;        // Measured distance from the rotation center in millimeters (mm) stored as fixed-point. 0 indicates an invalid measurement. Actual Distance = distance_q2 / 4.0 mm
} rplidar_response_measurement_node;

typedef struct {
    uint8   model;
    uint16  firmware_version;
    uint8   hardware_version;
    uint8   serialnum[16];
} rplidar_response_device_info;

typedef struct {
    uint8   status;
    uint16  error_code;
} rplidar_response_device_health;




#endif /* RPLIDAR_INCLUDES_RPLIDAR_CMD_H_ */
