/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      6/16/2025, 1:10:06 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*--------------------------;l///--------------------------------------------------*/

#include "vex.h";

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here 
brain Brain;
controller Controller; 
float pi = 3.14;
float dia = 4.00;
motor LM (PORT19, ratio18_1, false);
motor RM (PORT18, ratio18_1, true);
motor intake (PORT20, ratio6_1, true);
motor outake (PORT17, ratio18_1, true);



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
 
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

  int Lspeed = Controller.Axis3.position(pct);
  int Rspeed = Controller.Axis3.position(pct);

  Lspeed = Lspeed + Controller.Axis1.position(pct);
  Rspeed = Rspeed - Controller.Axis1.position(pct);

  
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  }
}*/
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.*/

void fTurn(float time, float speed) {
  LM.spin(forward, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}

void bTurn(float time, float speed) {
  LM.spin(reverse, speed, pct);
  RM.spin(reverse, speed, pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}

void rTurn(float time, float speed) {
  LM.spin(forward, speed, pct);
  RM.spin(reverse, speed, pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}

void lTurn(float time, float speed) {
  LM.spin(reverse, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
}

void outTurn(float time) {
  outake.spin(forward, 75, pct);
  wait(time, sec);
  outake.stop();
}

void inTurn(float time) {
  intake.spin(forward, 100, pct);
  wait(time, sec);
  intake.stop();
}


void inchDrive(float target) {
  float x = 0;
  LM.setPosition(0, rev);
  x = LM.position(rev) * dia * pi;
  while (x <= target) {
    fTurn(.1, 25);
    x = LM.position(rev) * dia * pi;
    Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
  }
  LM.stop();
  RM.stop();
  }

/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  bTurn(1, 80);
  rTurn(0.5, 30);
  bTurn(0.5, 40);
  outTurn(3);
  fTurn(1, 80);
  inTurn(1);
  outTurn(0.5);
  bTurn(1, 80);
  outTurn(0.5);
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

  int Lspeed = Controller.Axis3.position(pct);
  int Rspeed = Controller.Axis3.position(pct);

  if (Controller.ButtonR1.pressing()) {
    intake.spin(forward, 100, pct);
  }
else if (Controller.ButtonR2.pressing()) {
    intake.spin(reverse, 100, pct);
  }
  else {
    intake.stop();
  }

  if (Controller.ButtonUp.pressing()) {
    outake.spin(forward, 100, pct);
  }
  else if (Controller.ButtonDown.pressing()) {
    outake.spin(reverse, 100, pct);
  }
  else {
    outake.stop();
  }

  Lspeed = Lspeed + Controller.Axis1.position(pct);
  Rspeed = Rspeed - Controller.Axis1.position(pct);

  
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.



}
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.


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
