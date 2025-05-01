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
motor LF (PORT4, ratio6_1, true);
motor LB (PORT3, ratio6_1, true);
motor RF (PORT20, ratio6_1, false);
motor RB (PORT21, ratio6_1, false);
inertial imu (PORT10);

float dia = 3.25;
float gear_Ratio = 0.6;
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

void gyroPrint() {

  float heading = imu.heading(deg);
  float rotation = imu.rotation(deg);
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(10, 20, "Heading = %0.1f", heading);
  Brain.Screen.printAt(10, 40, "Rotation = %0.1f", rotation);
  Brain.Screen.printAt(10, 60, "Pitch = %0.1f", imu.pitch(deg));
  Brain.Screen.printAt(10, 80, "Yaw = 0.1f", imu.yaw(deg));
  Brain.Screen.printAt(10, 80, "Roll = 0.1f", imu.roll(deg));
}

void gyroTurn(float degrees) {

  while (imu.rotation()<degrees) {
   //moveRobot(-30, 30, 50);
  LF.spin(forward, 30, pct );
  LB.spin(forward, 30, pct);
  RF.spin(reverse, 30, pct);
  RB.spin(reverse, 30, pct); 
  }
  stopRobot();
}

void Pturn(float degrees) {
  float heading = imu.rotation(deg);
  float error = degrees - heading;
  float Kp = 0.5;
  float speed = error * Kp;

  if(degrees > 0) {

  while(fabs(error)>2){
  LF.spin(forward, speed, pct );
  LB.spin(forward, speed, pct);
  RF.spin(reverse, speed, pct);
  RB.spin(reverse, speed, pct); 
  wait(30, msec);
  heading = imu.rotation(deg);
  error = heading - degrees;
  speed = error * Kp;
  }
  }
  

  LF.stop();
  LB.stop();
  RF.stop();
  RB.stop();
    
}
                                                    
/*                                                                           */
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
 Pturn(90);
 wait(2000, msec);
 Pturn(-90);
 gyroPrint(); 
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

    gyroPrint();

   // Brain.Screen.printAt(242, 136, "A murder case");
    // Brain.Screen.printAt(450, 20, "Blood");
    // Brain.Screen.drawRectangle(10, 140, 5, 5); 
  

    wait(200, msec); // Sleep the task for a short amount of time to
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
