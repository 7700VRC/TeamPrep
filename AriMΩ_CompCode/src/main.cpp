/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      5/13/2025, 4:15:44 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
              //7700A Robot Tuesday 4-6
competition Competition;
brain Brain;
// define your global instances of motors and other devices here
motor leftFront(PORT4, ratio6_1, true);
motor leftBack(PORT2, ratio6_1, true);
motor rightFront(PORT19, ratio6_1, false);
motor rightBack(PORT21, ratio6_1, false);
controller Controller1;

inertial am (PORT3);

float dia = 3.25;
float gearRatio = 0.6;

void drive(int leftSpeed , int rightSpeed, int wt){
  leftFront.spin(forward , leftSpeed , pct);
  leftBack.spin(forward, leftSpeed, pct);
  rightFront.spin(forward, rightSpeed, pct);
  rightBack.spin(forward, rightSpeed, pct);
  wait(wt, msec);
}

void robotBrake(){
  leftFront.stop(brake);
  leftBack.stop(brake);
  rightFront.stop(brake);
  rightBack.stop(brake);
}

void inchDrive(float target){
  float error = 0;
  float Kp = 3.0;
  
  leftFront.resetPosition();
  float x = leftFront.position(rev)*dia*M_PI*gearRatio;
  error = target - x;




  while( fabs(error) > 0.5){
    float speed = error*Kp;

    drive(speed, speed,  50);
  float x = leftFront.position(rev)*dia*M_PI*gearRatio;
    error = target - x;
    speed = error*Kp;
  }
  robotBrake();
  Brain.Screen.printAt(10,20, "distance = %0.1f", x);

}

void Pturn(float targetDegrees){
  float heading = am.rotation(deg);
  float error = targetDegrees - heading;
  float kp = 0.5; // constant P gain
  float speed = kp * error;

  while(fabs(error) > 5){

    rightFront.spin(forward, -speed, pct); 
    rightBack.spin(forward, -speed, pct);
    leftFront.spin(forward, speed, pct);
    leftBack.spin(forward, speed, pct);
    wait(30, msec);

    heading = am.rotation(deg);
    error = heading - targetDegrees;
    speed = error * kp;

  }
  rightFront.stop(brake);
  rightBack.stop(brake);
  leftFront.stop(brake);
  leftBack.stop(brake);
}

void printGyro(){
  Brain.Screen.printAt(10, 20, "Heading= %0.1f", am.heading(deg));
  Brain.Screen.printAt(10, 40, "Rotation = %0.1f", am.rotation(deg));
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
 

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

  inchDrive(20);
  Pturn(45);
  inchDrive(10);
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    int leftSpeed = Controller1.Axis3.position();
    int rightSpeed = Controller1.Axis2.position();

    drive(leftSpeed, rightSpeed, 10);

    printGyro();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
