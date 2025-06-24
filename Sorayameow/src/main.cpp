/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      5/1/2025, 4:09:20 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here



brain Brain;
motor LBM(PORT12, ratio6_1, false);
motor LFM(PORT2, ratio6_1, false );
motor RBM(PORT11, ratio6_1, true);
motor RFM(PORT5, ratio6_1, true);

inertial imu (PORT3);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
             


void printGyro(){
  Brain.Screen.printAt(10,20, "Heading = %0.1f", imu.heading(deg));
  Brain.Screen.printAt(10,40, "Rotation = %0.1f", imu.rotation(deg));
  Brain.Screen.printAt(10,60, "Yaw = %0.1f", imu.yaw(deg));
  Brain.Screen.printAt(10,80, "Roll = %0.1f", imu.roll(deg));
  Brain.Screen.printAt(10,100, "Pitch = %0.1f", imu.pitch(deg));
}


void gyroTurn(float degrees){
if  (degrees>0){

while (imu.rotation(deg)< degrees){

  RFM.spin(forward, -50, pct);
  RBM.spin(forward, -50, pct);
  LFM.spin(forward, 50, pct);
  LBM.spin(forward, 50, pct);
  wait(30, msec);

  //moverobot(-50, 50, 30);

}

}

else if (degrees>0){

while (imu.rotation(deg)> degrees){

  RFM.spin(forward, -50, pct);
  RBM.spin(forward, -50, pct);
  LFM.spin(forward, 50, pct);
  LBM.spin(forward, 50, pct);
  wait(30, msec);

  //moverobot(-50, 50, 30);
}
}

RFM.stop(brake);
RBM.stop(brake);
LFM.stop(brake);
LBM.stop(brake);
}


void Pturn(float targetDegrees){
  float heading = imu.rotation(deg);
  float error = targetDegrees - heading;
  float Kp = 0.5;
  float speed = Kp *error;
  
  while (fabs(error)> 5 ){ //tolerance
  RFM.spin(forward, speed, pct);
  RBM.spin(forward, speed, pct);
  LFM.spin(forward, speed, pct);
  LBM.spin(forward, speed, pct);
  wait(30, msec);

  heading = imu.rotation(deg);
  error = heading - targetDegrees;
  speed = error *Kp;

  }
RFM.stop(brake);
RBM.stop(brake);
LFM.stop(brake);
LBM.stop(brake);
}


void pre_auton(void) {

  while(imu.isCalibrating())wait(200, msec);
  gyroTurn(90);
  wait(1, sec);
  gyroTurn(-90);

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
 
  gyroTurn(90);
  wait(1, sec);
  gyroTurn(-90);
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

   printGyro();
    wait(200, msec); // Sleep the task for a short amount of time to
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
