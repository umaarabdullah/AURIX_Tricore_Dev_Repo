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

void vehicle_control_obstacle_avoidance_mode(void){

    // Read the distance from the ultrasonic sensor
    double distance_1 = read_distance_sonar_1();
    double distance_2 = read_distance_sonar_2();
    double distance_3 = read_distance_sonar_3();
    double distance_4 = read_distance_sonar_4();
//    IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_1 Distance: %lfCM\n\r",distance_2);

    // Leftmost sonar sensor
    if(distance_1 <= OBSTACLE_DISTANCE_THRESHOLD){
                IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_1 Obstacle Detected: \n\r");
        while(distance_1 <= OBSTACLE_DISTANCE_THRESHOLD){
            distance_1 = read_distance_sonar_1();
            steer(1);   // steer right
        }
    }

    // Right-Middle sonar sensor
    if(distance_2 <= OBSTACLE_DISTANCE_THRESHOLD){
                IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_2 Obstacle Detected: \n\r");
        while(distance_2 <= OBSTACLE_DISTANCE_THRESHOLD){
            distance_2 = read_distance_sonar_2();
            steer(-1);      // steer left
        }
    }
    // left-Middle sonar sensor
    if(distance_3 <= OBSTACLE_DISTANCE_THRESHOLD){
                IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_3 Obstacle Detected: \n\r");
        while(distance_3 <= OBSTACLE_DISTANCE_THRESHOLD){
            distance_3 = read_distance_sonar_3();
            steer(1);   // steer right
        }
    }

    // Rightmost sonar sensor
    if(distance_4 <= OBSTACLE_DISTANCE_THRESHOLD){
        IfxStdIf_DPipe_print(&g_ascStandardInterface, "\n\r Sonar_4 Obstacle Detected: \n\r");
        while(distance_4 <= OBSTACLE_DISTANCE_THRESHOLD){
            distance_4 = read_distance_sonar_4();
            steer(-1);      // steer left
        }
    }

    steer(0);       // forward

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




