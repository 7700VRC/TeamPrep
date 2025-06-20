/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/16/2025, 1:11:02 PM                                     */
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
motor LM(PORT14, ratio18_1, true);
motor RM(PORT19, ratio18_1, false);
motor SPINNER1(PORT17, ratio18_1, false);
float pi = 3.14;
float dia = 4.00;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

/// @brief 
/// @param time 
/// @param speed 
void drive(float time, double speed)
{
  LM.spin(forward, speed, pct);
  RM.spin(forward, speed, pct);
  wait(time, msec);
  LM.stop();
  RM.stop();
}


void turn(float time, int speed){
  LM.spin(forward, speed, pct);
  RM.spin(reverse, speed, percent);
  wait(time, msec);
}
void inchDrive(float target){
float x = 0;
LM.setPosition(0, rev);
x = LM.position(rev)*dia*pi;
while (x <= target ) {
drive(10, 50);
x = LM.position(rev)*pi*dia;
Brain.Screen.printAt(10, 20, "inches = %0.2f", x);

}







}

void pre_auton(void)
{

}



void autonomous(void)
{
inchDrive(-1.5);
turn(500, 100);
inchDrive(7.5);








}


/// @brief
/// @param
void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    Brain.Screen.printAt(10, 70, "I don't want to undo 600 nylocks.-Brady");
    Brain.Screen.printAt(10, 85, "Thats crazy.-Logan");
    int Lspeed1 = 0;
    int Rspeed1 = 0;
    Controller.Screen.setCursor(1, 1);
    if (Controller.ButtonY.pressing()){
      SPINNER1.spin(fwd, 100, pct);
    }
    else if (Controller.ButtonRight.pressing()){
      SPINNER1.spin(reverse, 100, pct);
    }
    else {
      SPINNER1.stop();
    }
    if (Controller.ButtonR2.pressing()){
      Lspeed1 = -40;
      Rspeed1 = -40;
      }
    else{
      Lspeed1 = Controller.Axis2.position(pct);
      Rspeed1 = Controller.Axis3.position(pct);
      }
    LM.spin(fwd, Lspeed1, pct);
    RM.spin(fwd, Rspeed1, pct);
    if (Controller.ButtonR2.pressing()){
      
      Controller.Screen.print("Low Speed Enabled");
     }
    else{
      Controller.Screen.print("Max Speed Enabled");}
      if (Controller.ButtonR1.pressing()){
      Lspeed1 = 40;
      Rspeed1 = 40;
      }
    else{
      Lspeed1 = Controller.Axis2.position(pct);
      Rspeed1 = Controller.Axis3.position(pct);
      }
    LM.spin(fwd, Lspeed1, pct);
    RM.spin(fwd, Rspeed1, pct);
    if (Controller.ButtonR1.pressing()){

      Controller.Screen.print("Low Speed Enabled");
     }
    else{
      Controller.Screen.print("Max Speed Enabled");}
    }


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
