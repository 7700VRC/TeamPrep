/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      5/8/2026, 4:24:55 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RBM (PORT15, ratio18_1, true); 
motor LBM (PORT9, ratio18_1, false);
motor RFM (PORT8, ratio18_1, true);
motor LFM (PORT1, ratio18_1, false);
motor intakeM(PORT10, ratio6_1, true);
motor conveyorM(PORT4, ratio6_1, false);
motor outakeM(PORT17, ratio6_1, true);
brain Brain; 
controller Controller; 
pneumatics descore(Brain.ThreeWirePort.A);
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */

void driveRobot(int Rspeed, int Lspeed, int WaitTime){ 

  RBM.spin(forward, Rspeed, pct); 
  RFM.spin(forward, Rspeed, pct);
  LFM.spin(forward, Lspeed, pct);
  LBM.spin(forward, Lspeed, pct);
  wait(WaitTime, msec); 
  RBM.stop();
  RFM.stop();
  LFM.stop();
  LBM.stop();

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









int sign (int a){
  if (a<0){
    return -1;
  }
return 1;
}
void inchDrive (int inches){
float c= M_PI * 3.25;
float distance = LFM.position(turns) * c * 5.0/3;
while(fabs(distance)<fabs(inches)){
distance = LFM.position(turns) * c * 5.0/3;
driveRobot(50*sign(inches), 50*sign(inches),10);

}

}





void autonomous(void) {
inchDrive(5);

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
  // User control code here, inside the loop
  while (1) {

    Brain.Screen.printAt(10, 20, "Hi"); 
    
    int Rspeed = Controller.Axis3.position(pct); 
    int Lspeed = Controller.Axis2.position(pct); 

    driveRobot(Rspeed, Lspeed, 10); 

    if(Controller.ButtonR1.pressing()) { //taking blocks in to hold 
      intakeM.spin(fwd, 100, pct); 
      conveyorM.spin(fwd, 100, pct); 
      outakeM.spin(reverse, 5, pct);
    
    }
    else if (Controller.ButtonR2.pressing()) {           //score

      intakeM.spin(fwd, 100, pct);
      conveyorM.spin(fwd, 100, pct);
      outakeM.spin(fwd, 100, pct);

    }
    else if(Controller.ButtonL1.pressing()){
      intakeM.spin(reverse, 100, pct);
      conveyorM.spin(reverse, 100, pct);
      outakeM.spin(reverse, 100, pct);
    }
    else {         
             //stop motors
      intakeM.stop(); 
      conveyorM.stop(); 
      outakeM.stop();

    }
    if(Controller.ButtonA.PRESSED){
      descore.set(!descore.value());
    }


    // if (Controller.ButtonL1.pressing()){
    //   conveyorM.spin(fwd, 100, pct);
    //   outakeM.spin(fwd, 100, pct);



    // }
    
    // else { 

    //   conveyorM.stop();
    //   outakeM.stop();

    // }


    //wait(20, msec); // Sleep the task for a short amount of time to
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
