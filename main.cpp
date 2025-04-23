/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Phoebe Messiha                                            */
/*    Created:      Sat Jul 10 2021                                           */
/*    Description:  Code Assignment                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Ldrive               motor         1               
// Rdrive               motor         2               
// Lintake              motor         3               
// Rintake              motor         4               
// Conv                 motor         5               
// moGo                 motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

void drive(int Ls, int Rs, int wt) {
  Ldrive.spin(forward);
  Rdrive.spin(forward);
  wait(wt, msec);
  Ldrive.stop(brake);
  Rdrive.stop(brake);
}

void DriveStop() {
  Ldrive.stop(brake);
  Rdrive.stop(brake);
}
void intake(int Ls, int Rs, int wt) {
  Lintake.spin(forward);
  Rintake.spin(forward);
  wait(wt, msec);
}

void IntakeStop(){
  Lintake.stop(brake);
  Rintake.stop(brake);
}

void ConvRun(int speed, int wt){
  Conv.spin(forward, speed, pct);
  wait(wt, msec);
}

void MoGoal(int MoGospeed, int wt){
  moGo.spin(forward, MoGospeed, pct);
  wait(wt, msec);
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  intake(50, 50, 200);
  IntakeStop();
  drive(50, 50, 500);
  DriveStop();
  drive(-50, -50, 100);
  DriveStop();
  intake(-50,-50,50);
  ConvRun(50, 500);
}
