/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/17/2025, 4:14:18 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor LF(PORT10, ratio18_1, false );
motor LB(PORT20, ratio18_1, false );
motor RF(PORT1, ratio18_1, true );
motor RB(PORT3, ratio18_1, true );



float WD = 3.25;
float GR = 0.6

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*
     
/*  not every time that the robot is disabled*/

//return type: int, float,void                      */
void drawOnScreen  () {
  
  
  
  
  }

int drawShapes () {
  Brain.Screen.setPenColor(white);
Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(250, 100, 50, 50);
  
  


  return 0;
}

void moverobot (int rspeed, int lspeed, int duration) {

  LF.spin(forward, lspeed, pct );
  LB.spin(forward, lspeed, pct );
  RB.spin(forward, rspeed, pct );
  RF.spin(forward, rspeed, pct );

wait(duration, msec);
}

void stopRobot() {
  LF.stop(brake);
  LB.stop(brake);
LB.stop(brake);
LB.stop(brake);
}



void inchDrive(float inches){
 float x = 0;
float error = inches - x;
float Kp = 3.0;
float speed = error  *Kp

LF .resetpostion();
//LF.setPosition(o.rev);
while (fabs (error) > 0.5){

moveRobot(speed,speed, 10) ;
x = LF.position(rev)*WD*M_PI*GR;
error = inches - x;
speed = error * Kp;

}
stopRobot();

}


/*not every time the robot is disabled
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
   drawOnScreen();
  wait (1,sec);
Brain.Screen.clearScreen();
drawShapes();



moverobot(50,50, 500);
stopRobot();


}









//drive the robot straight for a certain amount of time


//make a sharp U turn


//go back to where you started from



//stop the robot


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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
