/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      9/11/2025, 4:04:06 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Controller;
// define your global instances of motors and other devices here
motor RFM(PORT6, ratio18_1, false );
motor LBM(PORT2, ratio18_1, true);
motor LFM(PORT3, ratio18_1, true) ;
motor RBM(PORT1, ratio18_1, false) ;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
void driverobot(int Rspeed, int Lspeed, int WT) {
RFM.spin(forward,Rspeed, pct);
RBM.spin(forward,Rspeed, pct);
LBM.spin(forward,Lspeed, pct);
LFM.spin(forward,Lspeed, pct);
wait(WT, msec);
}

void stoprobot(){
RFM.stop(brake);
RBM.stop(brake);
LBM.stop(brake);
LFM.stop(brake);



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
driverobot( 50, 50,2500 );
driverobot(-50, 50, 1500);
stoprobot();
}

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................


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
    
int Lspeed = Controller.Axis3.position(pct);
int Rspeed = Controller.Axis2.position(pct);
driverobot(Rspeed, Lspeed, 20);









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
