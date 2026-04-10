/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      3/19/2026, 4:12:18 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

motor LF = motor(PORT2,ratio18_1,true);
motor LB = motor(PORT1,ratio18_1,true);
motor RF = motor(PORT9,ratio18_1,false);
motor RB = motor(PORT7,ratio18_1,false);
motor Intake = motor(PORT3,ratio6_1,true);
motor Conveyor = motor(PORT4,ratio6_1,true);
motor Outtake = motor(PORT5,ratio6_1,true);

brain Brain = brain();
controller Controller = controller();
// define your global instances of motors and other devices here


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */




/*---------------------------------------------------------------------------*/

void drive(int time, int lspeed, int rspeed){
  LF.spin(fwd, lspeed, pct);
  LB.spin(fwd, lspeed, pct);
  RF.spin(fwd, rspeed, pct);
  RB.spin(fwd, rspeed, pct);
  wait(time, msec);
  LF.stop(brake); //coast //brake //hold
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}

void pre_auton(void) {
  drive(2000, 100, 100);
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
  drive(50, 100, 400); //curve turn
  drive(100, 100, 500);
  drive(100, -100, 300);

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

void usercontrol(void){


  // User control code here, inside the loop
  

  while (1) {

    int lspeed = Controller.Axis3.position(pct);
    int rspeed = Controller.Axis2.position(pct);
    drive(lspeed,rspeed,10);

if(Controller.ButtonL1.pressing()){
  Brain.Screen.printAt(10, 10, "I pressed the Left 1 button");
 // intake(100);
}
else if (Controller.ButtonL2.pressing()) {

  Brain.Screen.printAt(10, 30, "I'm pressing L2 Botton this time");
  //intake(-100);
}

else {
  Brain.Screen.printAt(10, 50, "not pressing anything");
  //intake(0);
}






    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  
  }
   /*
LF.spin(fwd, Controller.Axis3.position(pct) - Controller.Axis1.position(pct), pct);
LB.spin(fwd, Controller.Axis3.position(pct) - Controller.Axis1.position(pct), pct);
RF.spin(fwd, Controller.Axis3.position(pct) + Controller.Axis1.position(pct), pct);
RB.spin(fwd, Controller.Axis3.position(pct) + Controller.Axis1.position(pct), pct);
  */
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
