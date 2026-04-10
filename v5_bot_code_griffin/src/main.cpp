/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      12/23/2025, 5:33:57 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor FL = motor(PORT10, ratio18_1, true);
motor BL = motor(PORT9,ratio18_1,true);
motor BR = motor(PORT6,ratio18_1,false );
motor FR = motor(PORT20,ratio18_1,false );
motor intake = motor(PORT15,ratio6_1,false);
motor outake = motor(PORT1,ratio6_1, false);
motor conveyor = motor (PORT3,ratio6_1, false);
controller Controller = controller();
brain Brain = brain();

/*---------------------------------------------------------------------------*/
/*                          
/*                                                                           */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void drive(int lspeed, int rspeed){
  FL.spin(fwd, lspeed, pct);
  BL.spin(fwd, lspeed, pct);
  FR.spin(fwd, rspeed, pct);
  BR.spin(fwd, rspeed, pct);
 
}

void driveRobot (int Lspeed, int Rspeed, int waitTtime) {
  
FL.spin(fwd, Lspeed, pct);
BL.spin(fwd, Lspeed, pct);
FR.spin(fwd, Lspeed, pct);
BR.spin(fwd, Lspeed, pct);
wait(waitTtime, msec);
FL.stop(brake); //coast //brake // hold 
BL.stop(brake);
FR.stop(brake);
BR.stop(brake);
}

void Intake(int IntakeSpeed){
  intake.spin(fwd, IntakeSpeed, pct);
  conveyor.spin(fwd,IntakeSpeed, pct ); 
}



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

  /*driveRobot(100, 100, 400);
  driveRobot(50, 100, 500);
  driveRobot(100, 100, 500);
  driveRobot(100, -100, 300);*/


  // ..........................................................................
  // Insert autonomous user code here.
  // ........................................................................
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
} 





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
    double forward = Controller.Axis3.position(pct); 
    double turn = Controller.Axis1.position(pct);  
    
    

    double left_power = forward + turn ; 
  
    double right_power =  forward - turn; 
    
    drive(left_power,right_power );

    if(Controller.ButtonL1.pressing()) {
    Intake(100);
    Brain.Screen.printAt(10, 10, "Hi ItsAme Mario");
    }
    else if (Controller.ButtonL2.pressing()){ 
      Intake(-100); 
    }

       else { 
        Intake(0); 
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
