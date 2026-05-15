/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Teacher                                                   */
/*    Created:      13/49/3578, 296215:25:236 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

motor LF = motor(PORT11, ratio18_1, true);
motor LB = motor(PORT16, ratio18_1, true);
motor RF = motor(PORT13, ratio18_1, false);
motor RB = motor(PORT20, ratio18_1, false);
//motor Intake = motor(PORT12, ratio6_1, false);
//motor Outake = motor(PORT2, ratio6_1, false);
//motor Conveyor = motor(PORT10, ratio6_1, false);
brain Brain;
controller Controller;



void drive(int time, int lspeed, int rspeed){
  LF.spin(fwd, lspeed, pct);
  LB.spin(fwd, lspeed, pct);
  RF.spin(fwd, rspeed, pct);
  RB.spin(fwd, rspeed, pct);
  wait(time, msec);
  LF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
  RF.stop(brake);
}

//void intake(int IntakeSpeed){
  //Intake.spin(fwd, IntakeSpeed, pct);
//}

void Scoring(int ScoringSpeed){
  
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
 drive(400, 100, 100);
 drive(400, 50, 100);
 drive(500, 100, 100);
 drive(300, 100, -100);
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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    int lspeed = Controller.Axis3.position(pct);
    int rspeed = Controller.Axis2.position(pct);

    drive(10, lspeed, rspeed);

    if(Controller.ButtonL1.pressing()){
      Brain.Screen.printAt(10, 10, "I pressed the Left 1 button    heheehhehehehehehe");
      //intake(100);
    }
    else if (Controller.ButtonL2.pressing()){
      Brain.Screen.printAt(10, 30, "I am pressing L2 Button this Time        HEHEHEHEHHEHEHEHEHHEHEHEHEHEHEHEHE");
      //intake(-100);
    }
    else{
      Brain.Screen.printAt(10, 50, "not pressing anything         HEhEhEhEHHEhHEHEhEHHEhheHhEhehheheHEhHEhHEhehEHe");
      //intake(0);
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
