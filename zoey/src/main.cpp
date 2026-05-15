/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      3/5/2026, 4:33:39 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// jryf ryfrhthtre
/*
rgrg
gukt
tgtg
*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Controller;
motor LB(PORT12, ratio18_1, true);
motor RB(PORT14, ratio18_1, false);
motor LF(PORT11, ratio18_1, true);
motor RF(PORT19, ratio18_1, false);
motor Intake(PORT13, ratio18_1, false);
motor Outtakem(PORT15, ratio18_1, false);
motor Conveyor(PORT18, ratio18_1, false);

// define your global instances of motors and other devices here

void drive(int left, int right)
{

  LB.spin(fwd, left, pct);
  LF.spin(fwd, left, pct);
  RB.spin(fwd, right, pct);
  RF.spin(fwd, right, pct);
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drive(int Lspeed, int Rspeed, int WT)
{

  LF.spin(fwd, 100, pct);
  RF.spin(fwd, 100, pct);
  LB.spin(fwd, 100, pct);
  RB.spin(fwd, 100, pct);
  wait(WT, msec);
  LF.stop(brake); // coast //brake //hold
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}

void intake(int IntakeSpeed)
{

  Intake.spin(fwd, 100, pct);
}

void Outtake(int OuttakeSpeed)
{

  Outtakem.spin(fwd, 100, pct);
}

/*---------------------------------------------------------------------------*/

void pre_auton(void)
{

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
void drive(int lspeed, int rspeed, int time)
{
  LF.spin(fwd, lspeed, pct);
  LB.spin(fwd, lspeed, pct);
  RF.spin(fwd, lspeed, pct);
  RB.spin(fwd, lspeed, pct);
  wait(time, msec);
  LF.stop();
  RF.stop();
  LB.stop();
  RB.stop();
}

int sign(int a)
{
  if (a < 0)
  {
    return -1;
  }
  return 1;
}

void inchDrive(int inches)
{
  LF.resetPosition();
  float c = M_PI * 4;

  float distance = LF.position(turns) * c * 7.0 / 4;
  while (fabs(distance) < fabs(inches))
  {
    distance = LF.position(turns) * c * 7.0 / 4;
    drive(50 * sign(inches), 50 * sign(inches), 10);
  }
}

void autonomous(void)
{
  // ..........................................................................

  drive(100, 100, 400);
  drive(50, 100, 400);
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

void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    int lspeed = Controller.Axis3.position(pct);
    int rspeed = Controller.Axis2.position();
    drive(lspeed, rspeed, 10);

    if (Controller.ButtonL1.pressing())
    {
      Brain.Screen.printAt(10, 10, "hi");
      intake(100);
    }

    else if (Controller.ButtonL2.pressing())
    {

      Brain.Screen.printAt(10, 35, "Screw");
      intake(-100);
    }
    else
    {
      Brain.Screen.printAt(10, 45, "Hi there");
      intake(0);
    }
  }
  // ........................................................................

  wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
