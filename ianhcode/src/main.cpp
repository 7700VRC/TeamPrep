/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      1/30/2026, 4:17:10 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller RC;
motor LB (PORT16, ratio18_1, true);
motor RB (PORT15, ratio18_1, false );
motor LF (PORT17, ratio18_1, true);
motor RF (PORT14, ratio18_1, false );

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
   

//retu

void drawOnBrain () {

Brain.Screen.printAt (20, 40, "hello world ");
 
Brain.Screen.setPenWidth(5);
Brain.Screen.setPenColor(purple);
Brain.Screen.setFillColor(yellow);
Brain.Screen.drawCircle(240, 135, 50);

}

void driveRobot (int Rspeed, int Lspeed, int waitTime){
LB.spin(fwd, Lspeed, pct);
LF.spin(fwd, Lspeed, pct);
RB.spin(fwd, Rspeed, pct);
RF.spin(fwd, Rspeed, pct);


wait(waitTime, msec );
}
void stopRobot(){
LF.stop();
LB.stop();
RB.stop();
RF.stop();

}



/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
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
  
  driveRobot(50, 50, 4250);

 driveRobot(50, -50, 475);

 driveRobot(50, 50, 3000);

driveRobot(50, -50, 475);

driveRobot(50, 50, 2350);

driveRobot(50, -50, 475);

driveRobot(50, 50, 4050);

driveRobot(50, -50, 475);

  stopRobot();




  // ..........................................................................
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
    drawOnBrain();


int Lspeed = RC.Axis2.position(pct);
int Rspeed = RC.Axis3.position(pct);

 driveRobot(Rspeed, Lspeed, 30);
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
