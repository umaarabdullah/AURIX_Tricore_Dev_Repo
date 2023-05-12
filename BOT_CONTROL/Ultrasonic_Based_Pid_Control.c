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


#define WAIT_TIME   700


void steer(int direction);
double calculate_error(void);

/*
 * Steering Functions
 * Function to actuate the steering mechanism
 * based on the desired direction (-1 for left, 0 for straight, 1 for right)
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
        default:
            stop();
            break;
    }
}

/*
 * Calculates the error based on the desired path and current position
 * Return the calculated error value
*/
double calculate_error() {

//    // Get sensor readings or other relevant data
//    double current_position = getCurrentPosition();  // Get the current lateral position of the car
//
//    // Calculate the error as the lateral deviation from the desired straight path
//    double error = current_position;

    return 0.0;
}

void vehicle_control(void){

    // Read the distance from the ultrasonic sensor
    double distance = read_distance_sonar();



    if(distance <= OBSTACLE_DISTANCE_THRESHOLD){
        // Get ticks for waitTime
        Ifx_TickTime timeout = IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, WAIT_TIME);
        // if obstacle detected make a left turn in a right angle
        // then go forward for 2 seconds
        // then again a right turn in a right angle
        steer(-1);
        waitTime(timeout);
        steer(0);
        waitTime(timeout);
        steer(1);
        waitTime(timeout);
    }
    else{
        steer(0);   // forward
    }

}

//// Main PID Control
//int pid_control(void) {
//
//    // Read the distance from the ultrasonic sensor
//    double distance = read_distance_sonar();
//
//    // Perform obstacle avoidance
//    if (distance <= OBSTACLE_DISTANCE_THRESHOLD) {
//        strayedFromStraightPath = 1;
//        steer(-1);  // Steer left to avoid the obstacle
//        steer(5);   // stop
//    }
//    else {
//        // Calculate the error based on the desired path (e.g., center of the lane)
//        double error = calculate_error();
//
//        // Calculate the control output using PID control
//        double proportional = Kp * error;
//        integral += Ki * error;
//        double derivative = Kd * (error - previous_error);
//        double control_output = proportional + integral + derivative;
//
//        // Update the previous error
//        previous_error = error;
//
//        // Steer the vehicle based on the control output
//        steer(control_output);
//    }
//
//    return 0;
//}



