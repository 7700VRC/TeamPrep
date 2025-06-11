/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Kieran Paramasivum                                        */
/*    Created:      4/14/2025, 4:47:20 PM                                     */
/*    Description:  7700F practice coding                                     */
/*    I am using 7700F robot.                                                 */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;

motor LF (PORT20, ratio18_1, true);
motor LB (PORT19, ratio18_1, true);
motor RF (PORT11, ratio18_1, false);
motor RB (PORT12, ratio18_1, false);

inertial gyrosense (PORT15);

float dia = 4.00;
float gear_Rtio = 1.00;

// formula for gear ratio, driven gear divided by driving gear = ratio 
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
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
    float kp = 3;
    float speed = kp * error;

    LF.setPosition(0, rev);

    while (fabs(error) > 0.5) {
      moveRobot(speed, speed, 10);
      x = LF.position(rev) * M_PI * dia * gear_Rtio; //distance robot has moved
      error = inches - x;
      speed = kp * error;
    }
    stopRobot();
    Brain.Screen.printAt(10, 20, "distance = %0.1f", x);
  }

  void gyroPrint() {
    float heading = gyrosense.heading(deg);
    float rotation = gyrosense.rotation(deg);
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10,20,"Heading = %0.1f", heading);
    Brain.Screen.printAt(10,40,"Rotation = %0.1f", rotation);
    Brain.Screen.printAt(10,60,"Pitch  =  %0.1f", gyrosense.pitch());
  }


  void gyroTurn(float degrees){
    while(gyrosense.rotation()<degrees) {
      moveRobot(-50, 50, 30);

    }
    stopRobot();

  }

  void Pturn(float degrees){
    float heading = gyrosense.rotation(deg);
    float error = degrees - heading;
    float Kp = 2.0;
    float speed = error * Kp;
    gyrosense.resetRotation();
   
    while(fabs(error)>=2){ 
      moveRobot(speed, -speed, 30);
      heading = gyrosense.rotation(deg);
      error = heading - degrees;
      speed = error * Kp;
    

    }
  
    stopRobot();
  }
/*---------------------------------------------------------------------------*/

//Part of Pre-Auton
void pre_auton(void) {

  while(gyrosense.isCalibrating()) wait(200, msec);


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
  wait(1, sec);
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
  while (1) {

   gyroPrint(); 
   wait(200, msec); 

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
