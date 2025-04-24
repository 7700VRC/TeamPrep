/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Anthony Ng :3                                             */
/*    Created:      4/14/2025, 4:44:20 PM                                     */
/*    Description:  7700F Training Project                                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

brain Brain;
motor LF (PORT4, ratio6_1, false);
motor LB (PORT3, ratio6_1, false);
motor RF (PORT20, ratio6_1, true);
motor RB (PORT21, ratio6_1, true);

float dia = 3.25;
float gear_Ratio = 1.3;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
 void screenPrinting (int x1, int x2, int y1, int y2) {
Brain.Screen.printAt(x1, y1, "A murder case");

//pring something on the top right of the screen

Brain.Screen.printAt(x2, y2, "Blood");

//draw a small square in the bottom left corner
Brain.Screen.setPenColor(purple);
Brain.Screen.setFillColor(blue);
Brain.Screen.drawRectangle(10, 140, 5, 5);

 }

void moveRobot(int rspeed, int lspeed, int duration){

  LF.spin(forward, lspeed, pct );
  LB.spin(forward, lspeed, pct);
  RF.spin(forward, rspeed, pct);
  RB.spin(forward, rspeed, pct);

  wait(3000, msec);

}

  void stopRobot() {
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
  
}

void inchDrive(int inches){
float x = 0;
float error = inches - x;
float kp = 3.0;
float speed = kp * error;

LF.setPosition(0, rev);

  while (fabs(error) > 0.5) {
    moveRobot(speed, speed, 10);
    x = LF.position(rev)*M_PI*dia*gear_Ratio; //distance robot has moved
    error = inches - x;
    speed = kp * error;
  }
  stopRobot();
  Brain.Screen.printAt(10, 20, "distance = %0.1f", x);
}

                                                                        
/*                                                                           */
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

void autonomous(void) {
inchDrive(10);
moveRobot(35, 70, 1000);
inchDrive(10);
stopRobot();
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


    Brain.Screen.printAt(242, 136, "A murder case");
    Brain.Screen.printAt(450, 20, "Blood");
    Brain.Screen.drawRectangle(10, 140, 5, 5);
  

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  screenPrinting(242, 400 , 135, 10); //These numbers reoresent, x1, x2, y1, y2
  wait(2, sec);
  Brain.Screen.clearScreen();
  screenPrinting(42, 250, 100, 50);
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
