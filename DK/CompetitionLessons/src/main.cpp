/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*    Update:  DK  6-11-2021                                                  */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global Variables here
float pi=3.14;


// Custom Functions



void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting initial positions, ...
}


void auton() {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}


void driver() {
  // User control code here, inside the loop
  while (true) {
    
    wait(10, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(auton);
  Competition.drivercontrol(driver);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
