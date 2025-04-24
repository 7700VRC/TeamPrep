/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      4/14/2025, 4:47:05 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
                                    
// A global instance of competition                                                
competition Competition;                                                          

// define your global instances of motors and other devices here
brain Brain;           
motor LF (PORT11, ratio6_1, true);
motor LB (PORT4, ratio6_1, true);
motor RF (PORT10, ratio6_1, false);
motor RB (PORT19, ratio6_1, false);   


 float dia = 4.00;
 float gear_Ratio = 0.4; 

/*---------------------------------------------------------------------------*/    
/*                          Pre-Autonomous Functions                         */  
void screenPrinting (int x1, int x2, int y1, int y2) {          
Brain.Screen.printAt(x1, y1, "The tonk is a reincarnation of a M60");  
Brain.Screen.setPenColor(cyan);
Brain.Screen.setFillColor(white);
Brain.Screen.drawRectangle(x2, y2, 190, 50.01, 50 ); 


}


void moveRobot(int rspeed, int lspeed, int duration){

 LF.spin(forward, lspeed, pct );
 LB.spin(forward, lspeed, pct );
 RF.spin(forward, rspeed, pct );
 RB.spin(forward, rspeed, pct );

 wait(duration, msec);
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
  float kp = 2;
  float speed = kp * error;

  LF.setPosition(0, rev);

  while (fabs(error) > 0.5) {
    moveRobot(speed, speed,10 );
    x = LF.position(rev)*M_PI*dia*gear_Ratio; //distance robot has moved
    error = inches - x;
    speed = kp * error; 
  }
  stopRobot();
  Brain.Screen.printAt(10, 20, "distance= %0.1f", x);
}
 


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
 
 inchDrive(12);
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
  screenPrinting(242,400 ,135,10); //these numbers represent x1 x2 y1 y2
  wait(2, sec);
  Brain.Screen.clearScreen();
  screenPrinting(42,250, 100,50);
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
