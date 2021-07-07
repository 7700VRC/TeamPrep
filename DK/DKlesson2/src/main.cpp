/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
<<<<<<< HEAD
/*    Author:       Rolling Robots                                                      */
/*    Created:      May 8 2021  Updated: May 15,2021                                        */
=======
/*    Author:       Rolling Robots */
/*    Created:      May 8 2021                                          */
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
/*    Description:  Competition Lesson1                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
<<<<<<< HEAD
// LeftMotor            motor         1               
// RightMotor           motor         2               
=======
// LeftMotor            motor         1
// RightMotor           motor         2
// Controller1          controller
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
<<<<<<< HEAD

// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt)
{
  LeftMotor.spin(forward, lspeed, percent);
   RightMotor.spin(forward, rspeed, percent); 
   wait(wt,msec);
}

// Add an inchDrive function to move the robot a specific number of inches
// --  need to know how far the robot will move for one turn of the wheel
// --  create global variable for wheel diameter or circumference
// --  monitor encoder on one or both wheels until they have moved a target number of inches
/////////////////


// Add a Rotate function that uses encoders to rotate the robot a set number of degrees.
//  -- robot will rotate when one side runs backwards and the other forward
//  -- use encoders to set how much the robot will rotate
//  -- need some math of basic geometry of circles
//  -- will need to know the track width of the drive base
//  -- save it in a global variable
///////////////
=======
float d=3.25;  // diameter of wheel in inches
float pi=3.14;
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt) {
  LeftMotor.spin(forward, lspeed, percent);
  RightMotor.spin(forward, rspeed, percent);
  wait(wt, msec);
}

void inchDrive(float target)
{
  float inches=0.0;
  RightMotor.setPosition(0, rev);

  while(inches<=target)
  {
drive(50,50,10);
inches=RightMotor.position(rev)*pi*d;
  }
  drive(0,0,0);
}
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30

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
<<<<<<< HEAD
float turns=0.0;
Brain.Screen.printAt(0, 20, "Pre auton is running");

/////////////  should move this to auton   /////////
turns=LeftMotor.position(rev);
Brain.Screen.printAt(0, 40, "Turns = %0.3f",turns);
drive(50, 50, 1000);
drive(0,0,0);
turns=LeftMotor.position(rev);
Brain.Screen.printAt(0, 60, "Turns = %f",turns);
=======
  float turns = 0.0;
  Brain.Screen.printAt(0, 20, "Pre auton is running");
  turns = LeftMotor.position(rev);
  Brain.Screen.printAt(0, 40, "Turns = %0.3f", turns);
  drive(50, 50, 1000);
  drive(0, 0, 0);
  turns = LeftMotor.position(rev);
  Brain.Screen.printAt(0, 60, "Turns = %f", turns);
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
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
<<<<<<< HEAD
=======
wait(1000, msec);
  inchDrive(27);
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
  // ..........................................................................
  // Insert autonomous user code here.
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
<<<<<<< HEAD
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
=======
  int lspeed = 0;
  int rspeed = 0;
  // User control code here, inside the loop
  while (1) {
    /*
    lspeed = Controller1.Axis3.position();
    rspeed = Controller1.Axis2.position();
    drive(lspeed, rspeed, 10);
    */
    drive(Controller1.Axis3.position(),Controller1.Axis2.position(),10);
    wait(10, msec); // Sleep the task for a short amount of time to
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
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
<<<<<<< HEAD
Brain.Screen.clearScreen();
Brain.Screen.printAt(0, 20, "Back to Main");
=======
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Back to Main");
>>>>>>> 3e2ee479cbd8328eabfe137719850b6b37220f30
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
