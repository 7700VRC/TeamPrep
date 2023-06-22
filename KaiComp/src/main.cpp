/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftFront            motor         4
// RightFront           motor         5
// LeftBack             motor         7
// RightBack            motor         6
// Gyro                 inertial      2
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <algorithm>
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;

float D = 4.0;       // Wheel diameter
float G = 7.0 / 5.0; // Gear ratio
float Pi = 3.14;

void drive(int lspeed, int rspeed, int wt) {
  LeftFront.spin(forward, lspeed, pct);
  RightFront.spin(forward, rspeed, pct);
  LeftBack.spin(forward, lspeed, pct);
  RightBack.spin(forward, rspeed, pct);
  wait(wt, msec);
}
void driveBrake() {
  LeftFront.stop(brake);
  RightFront.stop(brake);
  LeftBack.stop(brake);
  RightBack.stop(brake);
}
void drivecoast() {
  LeftFront.stop(coast);
  RightFront.stop(coast);
  LeftBack.stop(coast);
  RightBack.stop(coast);
}

void inchDrive(float target) {
  float avgSpeed[100] = {0};
  int i = 0;
  float x = 0.0;
  float error = target - x;
  float oldError = error;
  int dog = 0;
  float accuracy = 0.2;
  float kp = 3.0;
  float ks = 1.0;
  float speed = kp * error;
  float steer = Gyro.yaw(degrees);
  float lspeed = kp * error + steer;
  float rspeed = kp * error - steer;

  LeftFront.setRotation(0, rev);
  RightFront.setRotation(0, rev);
  while (fabs(error) > accuracy) {
    steer = ks * Gyro.yaw(degrees);
    speed = kp * error;

    speed = std::min(speed, float(80.0));
    speed = std::max(speed, float(-80.0));

    if (i > 99)
      i = 0;
    avgSpeed[i] = speed;
    speed = 0.0;
    for (int j = 0; j < 100; j++) {
      speed = speed + avgSpeed[j];
    }

    speed = speed / 100;
    std::cout << speed << std::endl;

    i++;

    lspeed = speed - steer;
    rspeed = speed + steer;
    drive(lspeed, rspeed, 10);

    x = LeftFront.rotation(rev) * Pi * D * G;
    oldError = error;
    error = target - x;

    if (fabs(error - oldError) < 0.08)
      dog++;
    else
      dog = 0;
    if (dog > 100)
      break;
  }
  driveBrake();
}
void gyroTurn(float target) {
  Gyro.setRotation(0.0, degrees);
  float heading = 0.0;
  float error = target - heading;
  float oldError = error;
  float accuracy = 2.0;
  float kp = 1;
  float kd = 0.1;

  while (fabs(error) > accuracy) {
    drive(kp * error + kd * (error - oldError),
          -(kp * error + kd * (error - oldError)), 10);
    heading = Gyro.rotation(degrees);
    oldError = error;
    error = target - heading;
    std::cout << heading << std::endl;
  }
  driveBrake();
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

/*---------------------------------------------------------------------------*/
/*                            Autonomous Functions                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  float avglSpeed[10] = {0};
  float avgrSpeed[10] = {0};
  float speed = 0.0;
  int i = 0;
  float lspeed;
  float rspeed;

  while (true) {
    speed = Controller1.Axis3.position();

    if (i > 9) i = 0;
    avglSpeed[i] = speed;
    speed = 0.0;
    for (int j = 0; j < 10; j++) {
      speed = speed + avglSpeed[j];
    }

    speed = speed / 10;
    lspeed = speed;

    speed =Controller1.Axis2.position();

    if (i > 9) i = 0;
    avgrSpeed[i] = speed;
    speed = 0.0;
    for (int j = 0; j < 10; j++) {
      speed = speed + avgrSpeed[j];
    }

    speed = speed / 10;
    rspeed = speed;

    std::cout<<"lspeed: " << lspeed << "rspeed: " << rspeed <<std::endl;

    i++;

    drive(lspeed*0.8, rspeed*0.8, 10);
  }
}

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
