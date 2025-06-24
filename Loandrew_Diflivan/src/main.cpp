/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      6/16/2025, 1:09:55 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller;
motor LM (PORT10, ratio18_1, false);
motor RM (PORT1, ratio18_1, true);
motor intake (PORT7, ratio18_1, false);
float pi = 3.14;
float dia = 4.00;
inertial Gyro = inertial(PORT5);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void drive(float time, double speed ){
  LM.spin(forward, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, sec);
  LM.stop();
  RM.stop();
  
}
void inchDrive(float target){
  float x = 0;
  LM.setPosition(0, rev);
  x = LM.position(rev)*dia*pi;
  while (x<= target) {
    drive(.05, 50);
    x = LM.position(rev)*dia*pi;
    Brain.Screen.printAt(10, 20, "inches = %0.2f", x);

  }
  LM.setBrake(hold);
  RM.setBrake(hold);
  LM.stop();
  RM.stop();
}

void gyroturn(int target){
float heading =0;
Gyro.setRotation(0, deg);
while (heading<target) {
  LM.spin(forward, 50, pct);
  RM.spin(reverse, 50, pct);
  wait(5, msec);
  heading = Gyro.rotation(deg);
}
LM.stop();
RM.stop();
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

inchDrive(25);

intake.spin(reverse, 60, pct);
inchDrive(30);
intake.stop();
gyroturn(-63);
inchDrive(40);
gyroturn(-71);
wait(150, msec);
inchDrive(15);
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

Brain.Screen.printAt(10,10, "Logan ");
Brain.Screen.printAt(9,60, "Hates");
Brain.Screen.setFillColor(tan);
Brain.Screen.drawCircle(240,136,20);
double Lspeed = Controller.Axis3.position(pct);
int Rspeed = Controller.Axis2.position(pct);
LM.spin(fwd, (Lspeed), pct);
RM.spin(fwd, (Rspeed/1.2), pct);

if(Controller.ButtonR1.pressing()){
  intake.spin(reverse, 75, pct);
}
else if(Controller.ButtonR2.pressing()){
  intake.spin(fwd, 75, pct);

}

else{
  intake.stop();
}


    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    
  }
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
