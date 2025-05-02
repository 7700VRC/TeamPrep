/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       TTHEGOAT                                                  */
/*    Created:      4/17/2025, 4:38:55 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
motor LF (PORT6, ratio6_1, true);
motor LB (PORT11, ratio6_1, true);
motor RF (PORT9, ratio6_1, false);
motor RB (PORT20, ratio6_1, false);
inertial Pneumonultramicroscopicsilicovolcanoconiosis (PORT8);

// define your global instances of motors and other devices here
float dia = 3.25;
float gr = 0.6;
float pi = M_PI;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
void drawOnScreen (){

Brain.Screen.print("The Champions have risen, ");
Brain.Screen.printAt (0, 240, "Henry has Fallen!");
Brain.Screen.printAt (260, 20, "Tianrui is King!!!");
Brain.Screen.printAt (260, 240, "Kingdom Shall Rise.");

}
int drawWithpen (){
Brain.Screen.setPenColor(red);
Brain.Screen.setPenWidth(10);
Brain.Screen.setFillColor(yellow);
Brain.Screen.drawRectangle(320, 60, 71, 71);
Brain.Screen.setPenColor(green);
Brain.Screen.setFillColor(blue);
Brain.Screen.drawCircle(357, 97, 28);
  return 0; 
}
void robotDrive(int rspeed, int lspeed, float wt){
  LF.spin(forward, lspeed, pct);
  RF.spin(forward, rspeed, pct);
  LB.spin(forward, lspeed, pct);
  RB.spin(forward, rspeed, pct);
  wait(wt, msec);
}
void robotStop(){
  LF.stop(brake);
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}
void inchDrive(float target){
  float x = 0;
  float error= target-x;
  float kp = 2;
  float speed = kp * error;
  LF.setPosition(0, rev);
  while(fabs (error)> 0.05){

    robotDrive(speed, speed, 10);
    x = LF.position(rev)*dia*pi*gr;
    error = target-x;
    speed = kp*error;
  }
  robotStop();
}
void gyroPrint(){
  Brain.Screen.printAt(10, 20, "Heading= %0.1f", Pneumonultramicroscopicsilicovolcanoconiosis.heading(deg));
  Brain.Screen.printAt(10, 40, "Rotation= %0.1f", Pneumonultramicroscopicsilicovolcanoconiosis.rotation(deg));
  Brain.Screen.printAt(10, 60, "Yaw= %0.1f", Pneumonultramicroscopicsilicovolcanoconiosis.yaw(deg));
  Brain.Screen.printAt(10, 80, "Roll= %0.1f", Pneumonultramicroscopicsilicovolcanoconiosis.roll(deg));
  Brain.Screen.printAt(10, 100, "Pitch= %0.1f", Pneumonultramicroscopicsilicovolcanoconiosis.pitch(deg));

}
void PneumonultramicroscopicsilicovolcanoconiosisTurn(float degr){
  if (degr<0){
  while(Pneumonultramicroscopicsilicovolcanoconiosis.rotation(deg)>degr){
    robotDrive(-50, 50, 30);
  }
  robotStop();
  }
  
  else if(degr<0){
  while(Pneumonultramicroscopicsilicovolcanoconiosis.rotation(deg)<degr){

    robotDrive(50, -50, 30);

  }
  
  }
  robotStop();
}
/*---------------------------------------------------------------------------*/
void Pturn(float tragderg){
  float heading = Pneumonultramicroscopicsilicovolcanoconiosis.rotation(deg);
  float error = tragderg-heading;
  float Kp = 1.5;
  float speed = Kp*error;
  while(fabs(error >0.5)){
    robotDrive(-speed, speed, 30);
    heading = Pneumonultramicroscopicsilicovolcanoconiosis.rotation(deg);
    error = tragderg-heading;
    speed = Kp*error;
  }
  robotStop();
}
void pre_auton(void) {
while(Pneumonultramicroscopicsilicovolcanoconiosis.isCalibrating())wait(200, msec);
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
  // ..........................................................................hdhdhdhdhddddhhdii dhdhdhdhdhdttht',.pyf      ..
Pturn(90);
wait(1, sec);
Pturn(-90); 

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
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
gyroPrint();
wait(200, msec);
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
