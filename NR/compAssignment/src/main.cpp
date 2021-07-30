// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// RB                   motor         10              
// claw                 motor         2               
// Controller1          controller                    
// LF                   motor         3               
// RF                   motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// RB                   motor         10              
// claw                 motor         2               
// Controller1          controller                    
// LF                   motor         3               
// RF                   motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// RB                   motor         10              
// claw                 motor         2               
// Controller1          controller                    
// LF                   motor         3               
// RF                   motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// RB                   motor         10              
// claw                 motor         2               
// Controller1          controller                    
// LF                   motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// RB                   motor         10              
// claw                 motor         2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LB                   motor         1               
// rightMotor           motor         10              
// claw                 motor         2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         10              
// claw                 motor         2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nikhil Ramanuja                                           */
/*    Created:      Fri Jul 2 2021                                            */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor            motor         1               
// rightMotor           motor         10              
// claw                 motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

void drive(int lspeed, int rspeed, int waitTime)
{
RB.spin(forward, rspeed, percent);
RF.spin(forward, rspeed, percent);
LB.spin(forward, lspeed, percent);
LF.spin(forward, lspeed, percent);
wait(waitTime, msec);

}

void clawOpen(int speed, bool openClaw)
{
  claw.setVelocity(speed, percent);
   if (openClaw==true)
claw.spinFor(forward,.75, rev);
else
claw.spinFor(reverse,.75, rev);

}
// define your global instances of motors and other devices here

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Brain.Screen.printAt(1, 40, "Running Pre Auton");
  
}

/*                              Autonomous Task                              
  This task is used to control your robot during the autonomous phase of   
  a VEX Competition.                                                       
*/

void autonomous(void) {
  Brain.Screen.printAt(1, 40, "Running Auton                ");
  drive(50,50,25);
  
  drive(50,-50,25);
  drive(0, 0, 0);


}

/*                         User Control Task                                                                          
This task is used to control your robot during the user control phase of 
                            a VEX Competition.                                                                                                            
You must modify the code to add your own robot specific commands here.   
*/

void usercontrol(void) {
  Brain.Screen.printAt(1, 40, "Running Driver      ");
  while (1) {
    


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







































































