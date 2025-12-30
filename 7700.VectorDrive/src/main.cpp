/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:      DK                                                    */
/*    Created:      4/16/2020                                         */
/*    Description:  V5 VEXTOR Drive                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LIntake              motor         2               
// RIntake              motor         20              
// LF                   motor         11              
// RF                   motor         9               
// LB                   motor         12              
// RB                   motor         10              
// Tray                 motor         17              
// Lift                 motor         19              
// IMU                  inertial      5               
// EncoderA             encoder       A, B            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <math.h>
using namespace vex;
using std::cout;
using std::endl;

#define PI 3.14159265

// robot specifics
float dia = 4; // inches
float circ = PI * dia;

// starting positions:
float theta = 0; // current heading
float x = 0;     // current x and y
float y = 0;

float calcAngleTarget(float targetX, float targetY) {
  return atan2(targetY - y, targetX - x) * 180.0 / PI - theta;
}

float calcRadiusTarget(float targetX, float targetY) {
  return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}

void drive(int LS, int RS, int WT) {
  RB.spin(forward, RS, pct);
  RF.spin(forward, RS, pct);
  LB.spin(forward, LS, pct);
  LF.spin(forward, LS, pct);
  wait(WT, msec);
}

void driveStop()
{
  RB.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  LF.stop(brake);
}

void intake(int LS, int RS) {
  LIntake.spin(forward, LS, rpm);
  RIntake.spin(forward, RS, rpm);
}

void tray(float rotations) { Tray.spinFor(forward, rotations, rev); }

void vectorDrive(float xT, float yT, float thetaT) {
  // pid constants
  float rKp = 1.8;
  float rKangle = 0.4;
  float radiusError = calcRadiusTarget(xT, yT);
  float angleError = 0;
  float oldRr = RF.position(rev);
  float oldRl=LF.position(rev);
  float oldRp=EncoderA.position(rev);
float Rp;
  while (fabs(radiusError)> 5)  
  {
    // print and update display
    Brain.Screen.printAt(1, 20, "x: %3.2f , y: %3.2f ", x, y);

    // recalculate errors
    angleError = calcAngleTarget(xT, yT);
    radiusError = calcRadiusTarget(xT, yT);

    // print heading and pos:
    Brain.Screen.printAt(1, 35, "angle error: %f", angleError);
    Brain.Screen.printAt(1, 55, "radius error: %f", radiusError);
    Brain.Screen.printAt(10, 120, "RF   %3.2f     ", RF.position(rev));
    Brain.Screen.printAt(10, 140, "theta   %3.2f     ", -IMU.rotation(degrees));

    // values to send to motors
    float lPower = radiusError * rKp;
    float rPower = radiusError * rKp;
    float angularVel = angleError * rKangle;

    // limit values %
    if (fabs(lPower) > 80)
      lPower = 80 * lPower / fabs(lPower);
    if (fabs(rPower) > 80)
      rPower = 80 * rPower / fabs(rPower);
    if (fabs(angularVel) > 20)
      angularVel = 20 * lPower / fabs(lPower);
   /* cout << " lPower = ";
    cout << lPower;
    cout << " angVel = ";
    cout << angularVel << endl;
    */
    lPower = lPower - angularVel;
    rPower = rPower + angularVel;

    drive(lPower, rPower, 10);

    float Rr = (RF.position(rev) - oldRr) * circ;
    oldRr= RF.position(rev);

    float Rl = (LF.position(rev) - oldRl) * circ;
    oldRl = LF.position(rev);

    //float r=Rr;
    float r=(Rr+Rl)/2;

    float Rp = (EncoderA.position(rev) - oldRp) * circ;
    oldRp = EncoderA.position(rev);

    x += r * cos(theta * PI / 180)-Rp*sin(theta * PI / 180);
    y += r * sin(theta * PI / 180)+Rp*cos(theta * PI / 180);

    theta = -IMU.rotation(degrees);

    Rp=PI*dia*EncoderA.position(degrees)/360;

    cout << " x = ";
    cout << x;
    cout << " y = ";
    cout << y;
    cout << "    r  = ";
    cout << r;
    cout << " theta = ";
    cout << theta ;
             cout << " Rp = ";
    cout << Rp << endl;
  }
   cout << "done xxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
  cout << " " << endl;
  driveStop();
 /* while(fabs(thetaT-theta)>1)
  {
    int sp=(thetaT-theta)*50;
    drive(-sp,sp,10);
cout << " theta = ";
    cout << theta << endl;
     theta = -IMU.rotation(degrees);
  }
*/
  Brain.Screen.printAt(10, 200, "Vector Drive break");
  cout << "done xxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
  cout << " " << endl;

  drive(0, 0, 0);
}

void auton() 
{ 
vectorDrive(36,36,90); 
vectorDrive(36,60,90);
//vectorDrive(36,42);
//vectorDrive(24,24); 
  }

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  float Rp;
  Brain.Screen.printAt(10, 70, "Vector Drive Test");
  IMU.calibrate();
  while (IMU.isCalibrating()) {
    wait(100, msec);
  }
  auton();
  while(true)
  {
    Brain.Screen.clearScreen();
      Brain.Screen.printAt(10, 200, "Rp =  %f  ", PI*dia*EncoderA.position(degrees)/360);
      wait(50,msec);
      
      Rp=PI*dia*EncoderA.position(degrees)/360;
          cout << " Rp = ";
    cout << Rp << endl;
  }
}
