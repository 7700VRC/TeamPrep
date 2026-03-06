/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       daniel bahng                                                   */
/*    Created:      4/14/2025, 4:44:34 PM                                     */
/*    Description:  V5 project training                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain; 
motor LFM (PORT16, ratio18_1, false);
motor LBM (PORT19, ratio18_1, false);

motor RFM (PORT12, ratio18_1, true);
motor RBM (PORT18, ratio18_1, true);

inertial imu (PORT21);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void screenPrinting () {
Brain.Screen.printAt(242, 136, "hey this took too long to print one line of code");

Brain.Screen.printAt(405, 30, "this took forever");

Brain.Screen.drawRectangle(35, 140, 41, 41);

}

void gyroprint() {

  float heading = imu.heading(deg);
  float rotation = imu.rotation(deg);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(10, 20, "Heading = %0.1f", heading);
  Brain.Screen.printAt(10, 40, "Rotation = %0.1f", rotation);
  Brain.Screen.printAt(10, 60, "Pitch = %0.1f", imu.pitch(deg));
  Brain.Screen.printAt(10, 80, "Yaw = %0.1f", imu.yaw(deg));
  Brain.Screen.printAt(10, 100, "Roll = %0.1f", imu.roll(deg));

}

void gyroTurn(float degrees) {

  while (imu.rotation()<degrees) {
    RFM.spin(reverse, 25, pct);
    RBM.spin(reverse, 25, pct);
    LFM.spin(forward, 25, pct);
    LBM.spin(forward, 25, pct);
    wait(30, msec);
  }
  RFM.stop(brake);
  RBM.stop(brake);


  LFM.stop(brake);
  LBM.stop(brake);


}

void Pturn(float degrees) {
  float heading = imu.rotation(deg);
  float error = degrees - heading;
  float Kp = 0.5; //constant does not change
  float speed = error * Kp;

 while (fabs(error)>=5){  
   RFM.spin(reverse, speed, pct);
   RBM.spin(reverse, speed, pct);
   LFM.spin(forward, speed, pct);
   LBM.spin(forward, speed, pct);
   wait(30, msec);
   heading = imu.rotation(deg);
   error =  heading - degrees;
   speed = error * Kp;



  }
}


/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  while(imu.isCalibrating())wait(200, msec); 
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
  Pturn (90);
  wait(1, sec);
  Pturn(-90);
  gyroprint();

  
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


  while (1) {

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  screenPrinting();

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
