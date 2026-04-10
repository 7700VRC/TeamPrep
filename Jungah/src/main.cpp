/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/9/2026, 4:01:03 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor LFM (PORT20,ratio18_1, true);
motor LBM (PORT15,ratio18_1, true);
motor RFM (PORT11,ratio18_1, false);
motor RBM (PORT5,ratio18_1, false);

motor Intake (PORT5,ratio18_1, true);
motor Outake (PORT6,ratio18_1, true);
motor Conveyor (PORT7,ratio18_1, true);

controller Controller;
brain Brain;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */

void drive (int Lspeed, int Rspeed, int Wt) {

LFM.spin(fwd, Lspeed, pct);
LBM.spin(fwd, Lspeed, pct);
RFM.spin(fwd, Rspeed, pct);
RBM.spin(fwd, Rspeed, pct);

wait(Wt, msec);
LFM.stop(brake);
LBM.stop(brake);
RFM.stop(brake);
RBM.stop(brake);






}


void intake (int ISpeed){



}

void Scoring(int Sspeed){


}








                            
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
  
drive(100, 100, 400);
drive(50, 100, 400); // curved turn
drive(100,100, 500);
drive(100,-100, 300);




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
   
  int Lspeed = Controller.Axis3.position(pct);
  int Rspeed = Controller.Axis2.position(pct);
  drive(Lspeed, Rspeed, 10);

  if(Controller.ButtonL1.pressing()){
  Brain.Screen.printAt(10, 10, "I pressed the Left 1 button");
  intake(100);


  }
  else if (Controller.ButtonL2.pressing()) {

    Brain.Screen.printAt(10,30, "I am pressing Left 2 button");
    intake(-100);
  }

  else {
    Brain.Screen.printAt(10,50, "I am not pressing anything");
  }

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
