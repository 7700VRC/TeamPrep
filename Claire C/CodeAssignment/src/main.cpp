/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       clairecahill                                              */
/*    Created:      Wed Aug 18 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Rdrive               motor         1               
// Ldrive               motor         2               
// intake               motor         3               
// mogoalLift           motor         4               
// Conv                 motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void drive (int lspeed, int rspeed, int wt) 
  {
    Ldrive.spin(forward, lspeed, pct);
    Rdrive.spin(forward, rspeed, pct);
    wait(wt,msec);
  }

  void driveStop(){
    Ldrive.spin(reverse);
    Rdrive.spin(reverse);
  }

  void Intake (int intspeed, int wt){
    intake.spin(forward, intspeed, pct);
    wait(wt,msec);
  }

  void IntakeStop(){
    intake.spin(reverse);
  }

  void Lift (int MGLiftspeed, int wt){
    mogoalLift.spin(forward, MGLiftspeed, pct);
    wait(wt,msec);
  }

  void LiftStop(){
    mogoalLift.spin(reverse);
  }

  void conv (int convspeed, int wt){
    Conv.spin(forward);
    wait(wt,msec);
  }

  void ConvStop(){
    Conv.spin(reverse);
  }


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  drive(50, 50, 150);
  driveStop();
  drive(-50, 50, 100);
  driveStop();
  drive(50, 50, 200);
  Lift(50,50);
  LiftStop();
  Intake(50, 50);
  conv(50, 50);
  IntakeStop();
  ConvStop();
  
  

  
}
