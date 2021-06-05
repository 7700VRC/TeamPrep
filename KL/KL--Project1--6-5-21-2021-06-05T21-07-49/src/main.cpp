/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       KL                                                       */
/*    Created:      May 8 2021                                          */
/*    Description:  Competition Lesson 1                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         11              
// RightMotor           motor         20              
// Controller1          controller                    
// MyGyro               inertial      7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex; //methods in this namespace enables us to type less stuff

// A global instance of competition
competition Competition; //setting up competition mode
float d=3.25; //diameter of wheel in inches
float pi=3.14;
// define your global instances of motors and other devices here

void drive(int lspeed, int rspeed, int wt) // Function
{
  LeftMotor.spin(forward, lspeed, percent);
  RightMotor.spin(forward, rspeed, percent);
  wait(wt, msec);
}


void inchDrive(float target)
{
  float kp=20.0;
  float speed=100.0;
  float inches=0.0;
  RightMotor.setPosition(0, rev);
  while(inches<=target)
  {
    speed=kp*(target-inches);
    drive(speed,speed,10);
    inches=RightMotor.position(rev)*pi*d;
  }
  drive(0,0,0);
}

// Turn to the right
void gyroTurn(float target)
{
  float kp=12.0;
  float kd=10.0;
  float heading=0.0;
  float speed=100.0;
  float error=target;
  float oldError=error;
  MyGyro.setRotation(0.0, degrees);
  error=target-heading;
  while (true)
  {
    speed=kp*(error)+kd*(error-oldError);
    drive(speed,-speed, 10);
    heading=MyGyro.rotation();
    oldError=error;
    error=target-heading;
    Brain.Screen.printAt(0, 120, "heading = %.3f deg",heading);
  }
  drive(0,0,0);
}

void inchTurn(float target)
{
  float theta=0.0;
  RightMotor.setPosition(0, rev);
  while(theta<=target)
  {
    drive(-50,50,10);
    theta=24*RightMotor.position(rev)*pi*d/pi;
  }
  drive(0,0,0);
}
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
    float turns=0.0;
    Brain.Screen.printAt(0, 20, "Pre auton is running"); // Left hand coord
    turns=LeftMotor.position(rev);
    Brain.Screen.printAt(0, 40, "Turns = %0.3f", turns);
    drive(100, 100, 1000);
    drive(0,0,0);
    turns=LeftMotor.position(rev);
    Brain.Screen.printAt(0, 60, "Turns = %0.3f", turns);
    wait(2000, msec);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
// classes -- thing of same caracteristic. Object -- in class. 
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
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Running Auton");
  while(MyGyro.isCalibrating())
  {
    wait(10,msec);
  }
  RightMotor.setBrake(brake);
  LeftMotor.setBrake(brake);
  wait(1000, msec);
  inchDrive(72.0);
 
  inchTurn(0.0);
  gyroTurn(90.0);
  Brain.Screen.printAt(0,40, "Auton completed"); 

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
  RightMotor.setBrake(coast);
  LeftMotor.setBrake(coast);
  int lspeed=0;
  int rspeed=0;
  // User control code here, inside the loop
  while (1) { // 1 = true; 0 = false. Or while (true), or while (2==2).

  //usercontrol, need to repeatedly check
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    lspeed=Controller1.Axis3.position()+Controller1.Axis1.position();
    rspeed=Controller1.Axis3.position()-Controller1.Axis1.position();
    drive(lspeed, rspeed, 10);
  
    /*drive(Controller1.Axis3.position(), Controller1.Axis2.position(), 10);*/


    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
                    // vex brain very fast, nano seconds.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() { 
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous); // If autonomous, runs the function inside ()
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton(); 
Brain.Screen.clearScreen();
Brain.Screen.printAt(0, 20, "Back to main");
  // Prevent main from exiting with an infinite loop.
  while (true) { // While loop -- if false, skip over the bracket.
    wait(100, msec);
  }
}
//function = block of code in brackets that can be reused