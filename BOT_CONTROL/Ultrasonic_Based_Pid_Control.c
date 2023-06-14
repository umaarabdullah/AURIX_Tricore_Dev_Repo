/*
 * Ultrasonic_Based_Pid_Control.c
 *
 *  Created on: May 13, 2023
 *      Author: Umaar
 */

#include "Navigation.h"
#include "SONAR.h"
#include "STM_Interrupt.h"
#include "Bsp.h"
#include "UART.h"

// PID Controller Constants
#define Kp 0.5   // Proportional gain
#define Ki 0.2   // Integral gain
#define Kd 0.1   // Derivative gain

// PID Controller Variables
double previous_error = 0;
double integral = 0;

// Ultrasonic Sensor Constants
#define OBSTACLE_DISTANCE_THRESHOLD 30.0   // Threshold distance for obstacle detection in centimeters

#define WAIT_TIME   1000

void steer(int direction);
double calculate_error(void);
int lookRight(void);
int lookLeft(void);

/*
 * Steering Functions
 * Function to actuate the steering mechanism
 * based on the desired direction (-1 for left, 0 for straight, 1 for right, 2 for reverse, 10 for stop)
*/
void steer(int direction) {

    switch (direction){
        case -1:
            hard_left();
            break;
        case 0:
            forward();
            break;
        case 1:
            hard_right();
            break;
        case 2:
            backward();
            break;
        case 10:
            stop();
            break;
    }
}

/*
 * Calculates the error based on the desired path and current position
 * Return the calculated error value
*/

void vehicle_control(void){

    // Read the distance from the sonar sensor
    int distanceRight = 0;
    int distanceLeft = 0;

    double distance_1 = read_distance_sonar_1();        // leftmost sensor
    double distance_2 = read_distance_sonar_2();
    double distance_3 = read_distance_sonar_3();
    double distance_4 = read_distance_sonar_4();

    int ReverseFlag = 0;
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_1 Distance: %lfCM\n\r",distance_1);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_2 Distance: %lfCM\n\r",distance_2);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_3 Distance: %lfCM\n\r",distance_3);
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_4 Distance: %lfCM\n\r",distance_4);

    if (distance_1 <= OBSTACLE_DISTANCE_THRESHOLD ||
      distance_2 <= OBSTACLE_DISTANCE_THRESHOLD ||
      distance_3 <= OBSTACLE_DISTANCE_THRESHOLD ||
      distance_4 <= OBSTACLE_DISTANCE_THRESHOLD)
    {
        steer(10);        // stop
        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 300));
        if(!ReverseFlag){
            steer(2);         // reverse
            waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 200));
            ReverseFlag = 1;
        }
        steer(2);         // stop
        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 300));
        distanceRight = lookRight();
//        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 300));
        distanceLeft = lookLeft();
//        waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 300));
        if (distanceLeft <= OBSTACLE_DISTANCE_THRESHOLD){
            steer(1);       // turnRight
            steer(10);
        }
        else{
            steer(-1);      // turnLeft
            steer(10);
        }
    }
    else{
        ReverseFlag = 0;
        steer(0);           // forward
    }
}

int lookLeft(){

    int distance1, distance2;

    steer(-1);         // left
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 500));
    distance1 = read_distance_sonar_1();
    distance2 = read_distance_sonar_2();
    steer(1);          // right
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 500));
    // return the smaller distance
    if(distance1 > distance2)
        return distance2;
    else
        return distance1;
}

int lookRight(){

    int distance1, distance2;

    steer(1);         // right
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 500));
    distance1 = read_distance_sonar_3();
    distance2 = read_distance_sonar_4();
    steer(-1);        // left
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 500));

    // return the smaller distance
    if(distance1 > distance2)
        return distance2;
    else
        return distance1;
}

