
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      9/11/2025, 4:08:40 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RFM(PORT10, ratio18_1, false);
motor RBM(PORT11, ratio18_1, false);
motor LFM(PORT1, ratio18_1, true);
motor LBM(PORT2, ratio18_1, true);
brain Brain;
controller Controller;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous And usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void driverobot(int Rspeed, int Lspeed, int waitTime){
RFM.spin(forward,Rspeed, pct);
RBM.spin(forward,Rspeed, pct);
LBM.spin(forward,Lspeed, pct);
LFM.spin(forward,Lspeed, pct);
wait(waitTime, msec);

}

void stopRobot(){

RFM.stop(brake);
RBM.stop(brake);
LFM.stop(brake);
LBM.stop(brake);




}


  void pre_auton(void){

  }
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


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

driverobot(50, 50, 1500); 

driverobot(50, -50, 650); 

driverobot(50, 50, 1500);

driverobot(50, -50, 733);


stopRobot();








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

int Lspeed = Controller.Axis3.position(pct);
int Rspeed = Controller.Axis2.position(pct);
driverobot(Rspeed, Lspeed, 10);





wait(20, msec);
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
