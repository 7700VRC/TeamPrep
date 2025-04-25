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
// LeftFront            motor         19
// LeftMiddle           motor         20
// RightFront           motor         17
// RightMiddle          motor         18
// LeftBack             motor         11
// RightBack            motor         12
// Slapper              motor         10
// Gyro                 inertial      15
// Controller1          controller
// LeftPlow             digital_out   A
// RightPlow            digital_out   H
// Intake               motor         16
// Hang                 digital_out   G
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Gyro.calibrate();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

bool Plow = false;
int Autonum = 2;
bool In = false;
bool Out = false;
bool Slap = false;
bool Reverse = false;
int waitTime = 80;

void slapper() {
  Slapper.spin(forward, 40, pct);
  if (Controller1.ButtonR2.pressing() == false)
    Slapper.spin(forward, 0, pct);
}
void intake() {
  Intake.spin(forward, 100, pct);
  if (Controller1.ButtonA.pressing() == false)
    Intake.spin(forward, 0, pct);
}
void intakeToggle(float speed) { Intake.spin(forward, speed, pct); }
void intakeToggleOff() {
  Intake.spin(forward, 0, pct);
  Intake.stop(brake);
}

void reverseIntake() {
  Intake.spin(forward, -100, pct);
  if (Controller1.ButtonB.pressing() == false)
    Intake.spin(forward, 0, pct);
}

void slapperToggle(float speed) { Slapper.spin(forward, speed, pct); }
void driveVolts(double lspeed, double rspeed, double multiplier, int wt) {
  lspeed = lspeed * 120 * multiplier;
  rspeed = rspeed * 120 * multiplier;
  LeftFront.spin(forward, lspeed, voltageUnits::mV);
  LeftMiddle.spin(forward, lspeed, voltageUnits::mV);
  LeftBack.spin(forward, lspeed, voltageUnits::mV);
  RightFront.spin(forward, rspeed, voltageUnits::mV);
  RightMiddle.spin(forward, rspeed, voltageUnits::mV);
  RightBack.spin(forward, rspeed, voltageUnits::mV);
  task::sleep(wt);
}
void drive(int power, int turn, int time) {
  LeftFront.spin(forward, power + turn, pct);
  LeftMiddle.spin(forward, power + turn, pct);
  LeftBack.spin(forward, power + turn, pct);
  RightFront.spin(forward, power - turn, pct);
  RightMiddle.spin(forward, power - turn, pct);
  RightBack.spin(forward, power - turn, pct);
  task::sleep(time);
}
void Brake1() {
  LeftFront.stop(brake);
  LeftMiddle.stop(brake);
  LeftBack.stop(brake);
  RightFront.stop(brake);
  RightMiddle.stop(brake);
  RightBack.stop(brake);
}
void inchDrive(float target, int timeout = 1500, float kp = 2.75) {
  timer t2;
  double pie = 3.14159;
  double dia = 4;
  double g = 3.0 / 6.0;
  float x = 0.0;
  float tolerance = 1;
  float accuracy = 1;
  float ki = 0;
  float error = target - x;
  float speed = error * kp;
  float integral = 0;
  float prevError = target;
  float derivative = 0;
  float kd = 0;
  RightFront.setRotation(0.0, rev);
  while (t2.time(msec) < timeout) {
    x = RightFront.position(rev) * pie * dia * g;
    error = target - x;

    if (fabs(error) < tolerance) {
      integral += error;
    }
    derivative = error - prevError;
    prevError = error;
    driveVolts(speed, speed, 1, 10);
    speed = error * kp + integral * ki + derivative * kd;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(error);
  }
  Brake1();
}

void gyroTurnBig(float target, int timeout = 1500) {
  timer t1;
  float kp = 0.3;
  float ki = 0.2;
  float kd = 0.4;
  float integral = 0;
  float integralTolerance = 3;
  float heading = 0.0;
  float error = target - heading;
  float prevError = 0;
  float derivative;
  float speed = kp * error;
  float accuracy = 1.0;
  float bias = 0;

  while (t1.time(msec) < timeout) {
    heading = Gyro.rotation(degrees);
    error = target - heading;
    derivative = error - prevError;
    prevError = error;
    if (fabs(error) < integralTolerance) {
      integral += error;
    }
    if (fabs(error) < accuracy) {
      integral = 0;
    }

    speed = kp * error + kd * derivative + ki * integral;
    driveVolts(speed, -speed, 1, 0);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(error);
  }
  Brake1();
  wait(10, msec);
}
void gyroTurnSmall(float target, int timeout = 450, float kp = 0.3) {
  timer t1;
  float ki = 0.2;
  float kd = 0.4;
  float integral = 0;
  float integralTolerance = 3;
  float heading = 0.0;
  float error = target - heading;
  float prevError = 0;
  float derivative;
  float speed = kp * error;
  float accuracy = 1.0;
  float bias = 0;

  while (t1.time(msec) < timeout) {
    heading = Gyro.rotation(degrees);
    error = target - heading;
    derivative = (error - prevError);
    prevError = error;
    if (fabs(error) < integralTolerance) {
      integral += error;
    }
    if (fabs(error) < accuracy) {
      integral = 0;
    }

    speed = kp * error + kd * derivative + ki * integral;
    driveVolts(speed, -speed, 1, 0);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(error);
  }
  Brake1();
  wait(10, msec);
}
void deployablePlow() {
  if (Plow == false) {
    Plow = true;
    LeftPlow.set(true);
    RightPlow.set(true);
  } else if (Plow == true) {
    Plow = false;
    LeftPlow.set(false);
    RightPlow.set(false);
  }
}

// void leftPlow(){
//   if ()
// }

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
  int shots = 0;
  switch (Autonum) {
  case 1:
    // NearSide
    // inchDrive(-40, 2000, 2);
    // wait(200, msec);
    // gyroTurnSmall(90, 500);
    // wait(200, msec);
    // inchDrive(22, 1200, 2);
    // wait(200, msec);
    // gyroTurnSmall(-150, 650);
    // wait(200, msec);
    // inchDrive(16, 1000, 2);
    // wait(200, msec);
    // gyroTurnSmall(50, 1200, 1.2);
    // wait(200, msec);
    // intakeToggle(100);
    // wait(200, msec);
    // inchDrive(28, 750, 4);
    // wait(200, msec);
    // gyroTurnSmall(130, 700, 1);
    // wait(200, msec);
    // intakeToggleOff();
    // wait(200, msec);
    // inchDrive(10, 400, 3);

    //NEARSIDE
    RightPlow.set(true);
    wait(1000,msec);
    RightPlow.set(false);
    wait(200,msec);
    inchDrive(-10, 400, 3);
    wait(200,msec);
    inchDrive(10, 400, 3);
    wait(200,msec);
    inchDrive(40, 3000, 1);
    wait(200,msec);
    gyroTurnSmall(-180, 1000, 2);
    wait(200,msec);
    intakeToggle(100);
    wait(200,msec);
    inchDrive(10, 1500, 3);
    wait(200,msec);
    gyroTurnSmall(-190, 960, 1);
    wait(200,msec);
    inchDrive(12.5, 1800, 3);
    break;

  case 2:
    // FarSide
    // 1. Face towards bar
    // 2. Drive forwardpick up ball under bar
    // 3. Drive back and use turn to push preload in
    // 4. Drive forward, turn around, push ball in intake in
    // 5. Back out, face triball
    //FARSIDE
    inchDrive(-40, 1500, 2);
    wait(waitTime, msec);
    inchDrive(8, 650, 4);
    wait(waitTime, msec);
    gyroTurnSmall(160, 500);
    wait(waitTime, msec);
    intakeToggle(-100);
    inchDrive(30, 1500, 2);
    wait(waitTime, msec);
    gyroTurnSmall(300, 710);
    wait(waitTime,msec);
    intakeToggle(100);
    inchDrive(30, 1000, 2);
    wait(waitTime, msec);
    inchDrive(-30, 1500, 1.5);
    wait(waitTime, msec);
    intakeToggle(-100);
    gyroTurnSmall(60, 600);
    wait(waitTime,msec);
    inchDrive(15, 500, 4);
    wait(waitTime,msec);
    gyroTurnSmall(310, 710);
    LeftPlow.set(true);
    RightPlow.set(true);
    wait(waitTime,msec);
    intakeToggle(100);
    inchDrive(30, 1000, 2);
    LeftPlow.set(false);
    RightPlow.set(false);
    wait(waitTime, msec);
    inchDrive(-30, 1500, 1.5);
    wait(waitTime, msec);
    gyroTurnSmall(430, 700);
    wait(waitTime, msec);
    inchDrive(30, 1000, 4);



    // wait(200, msec);
    // gyroTurnSmall(330, 710);
   
  //  inchDrive(35, 1750, 2);
  //   wait(200, msec);
  //   gyroTurnSmall(-90, 300);
    
    break;

  case 3:
    // Skills
    inchDrive(-12, 2000, 4);
    wait(5, msec);
    gyroTurnSmall(20, 600);
    wait(5, msec);
    slapperToggle(60);
    Slapper.setRotation(0, rev);
    while (shots < 48) {
      shots = Slapper.rotation(rev);
      wait(100, msec);
    }     
    slapperToggle(0);
    wait(5, msec);
    Intake.spin(forward, 100, pct);
    wait(5, msec);
    gyroTurnSmall(50, 800);
    wait(5, msec);
    gyroTurnSmall(30, 800);
    wait(5, msec);
    inchDrive(8, 2000, 8);
    wait(5, msec);
    gyroTurnSmall(-30, 800);
    wait(5, msec);
    inchDrive(26, 2750, 8);
    wait(5, msec);
    gyroTurnSmall(-60, 1000);
    wait(5,msec);
    inchDrive(6, 2000, 9);
    wait(5,msec);
    gyroTurnSmall(-130, 900);
    wait(5,msec);
    inchDrive(12, 1750, 9);
    wait(5,msec);
    inchDrive(-6, 1500, 9);
    wait(5,msec);
    inchDrive(12,1200,9);
    wait(5,msec);
    inchDrive(-6,1200, 9);
    gyroTurnSmall(-200, 500);
    wait(5, msec);
    inchDrive(20, 1500, 4);
    wait(5, msec);
    LeftPlow.set(true);
    RightPlow.set(true);
    gyroTurnSmall(90, 500);
    wait(5, msec);
    inchDrive(12, 1750, 8);
    wait(5, msec);
    inchDrive(-12, 1750, 8);
    wait(5, msec);
    gyroTurnSmall(-45, 750);
    wait(5, msec);
    inchDrive(12, 1750, 8);
    wait(5, msec);
    inchDrive(-12, 2000, 8);
    wait(5,msec);
    inchDrive(12, 1750, 8);
    wait(5, msec);
    inchDrive(-12, 2000, 8);
    wait(5,msec);

    break;
  }
  // gyroTurnSmall(-90, 500);
  // gyroTurnSmall(-45, 760);
  // gyroTurnSmall(-60,600);



  // inchDrive(12, 2000, 3);
  // wait(50,msec);
  // gyroTurnSmall(-90, 500);
  // wait(50, msec);
  // inchDrive(16, 2000, 2);
  // wait(50,msec);
  // gyroTurnSmall(-120, 700);
  // wait(50,msec);
  // inchDrive(12, 1500, 5);
  // wait(50, msec);
  // inchDrive(-30, 3000, 1.35);
  // wait(50, msec);
  // inchDrive(5, 1500, 2);
  // gyroTurnSmall(90, 500);
  // wait(50, msec);
  // inchDrive(-24, 2000, 4);

  // MATCH AUTON NEARSIDE 11/4/2023
  // inchDrive(40, 600, 4);
  // wait(2000,msec);
  // inchDrive(-30, 600, 1.5);

  // MATCH AUTON NEARSIDE 11/6/2023 WORKING
  // inchDrive(-40,2000,2);
  // wait(200, msec);
  // gyroTurnSmall(90, 500);
  // wait(200,msec);
  // inchDrive(22,  1200, 2);
  // wait(200,msec);
  // gyroTurnSmall(-150, 650);
  // wait(200,msec);
  // inchDrive(16, 1000, 2);
  // wait(200,msec);
  // gyroTurnSmall(50, 1200, 1.2);
  // wait(200,msec);
  // intakeToggle(100);
  // wait(200,msec);
  // inchDrive(28, 750, 4);
  // wait(200,msec);
  // gyroTurnSmall(130, 700, 1);
  // wait(200,msec);
  // intakeToggleOff();
  // wait(200,msec);
  // inchDrive(10, 400, 3);
  // MATCH AUTON FARSIDE 11/28/2023
  // inchDrive(-40,2000,2);
  // wait(200,msec);
  // inchDrive(9,750,4);
  // wait(200,msec);
  // gyroTurnSmall(120, 600);
  // wait(200,msec);
  // intakeToggle(-100);
  // wait(200,msec);
  // inchDrive(30, 1500, 2);
  // wait(200,msec);
  // gyroTurnSmall(330,500);
  // wait(200,msec);
  // intakeToggle(0);
  // inchDrive(30, 1500, 2);
  // wait(200,msec);
  // intakeToggle(100);
  // inchDrive(-15,750,3);
  // wait(200, msec);
  // gyroTurnSmall(-135, 300);

  // MATCH AUTON NEARSIDE 11/28/23 Not WORKING PORT  1
  // inchDrive(-40,2000,2);
  // wait(200, msec);
  // gyroTurnSmall(-90, 500);
  // wait(200,msec);
  // inchDrive(24,  1250, 2);
  // wait(200,msec);
  // gyroTurnSmall(150, 650);
  // wait(200,msec);
  // inchDrive(18, 1050, 2);
  // wait(200,msec);
  // gyroTurnSmall(-50, 1350, 1.2);
  // wait(200,msec);
  // intakeToggle(100);
  // wait(200,msec);
  // inchDrive(20, 1150, 4);
  // wait(200,msec);
  // gyroTurnSmall(-132, 650, 1);
  // wait(200,msec);
  // intakeToggleOff();
  // wait(200,msec);
  // inchDrive(10.5, 410, 3);
  // MATCH AUTON NEARSIDE 11/28/23 Working Port 5
  // LeftPlow.set(true);
  // wait(8000, msec);
  // inchDrive(-17.5,1500,2);
  //     wait(200, msec);
  //     gyroTurnSmall(-60, 500);
  //     wait(200,msec);
  //     inchDrive(19,  1100, 2);
  //     wait(200,msec);
  //     gyroTurnSmall(150, 650);
  //     wait(200,msec);
  //     inchDrive(18, 1050, 2);
  //     wait(200,msec);
  //     gyroTurnSmall(-45, 1150, 1.2);
  //     wait(200,msec);
  //     intakeToggle(100);
  //     wait(200,msec);
  //     inchDrive(20, 1150, 4);
  //     wait(200,msec);
  //     gyroTurnSmall(-132, 650, 1);
  //     wait(200,msec);
  //     intakeToggleOff();
  //     wait(200,msec);
  //     LeftPlow.set(true);
  //     inchDrive(10.5, 410, 3);

  // MATCH AUTON NEARSIDE 11/17/23
  //  inchDrive(-40,2000,2);
  //   wait(200, msec);
  //   // gyroTurnSmall(-90, 500);
  //   // wait(200,msec);
  //   inchDrive(12, 1500, 1);
  //   wait(200,msec);
  //   gyroTurnSmall(-135, 1400, 3);
  //    LeftPlow.set(true);
  //   inchDrive(-30,  3000, 2);
  //   wait(200,msec);
  //   gyroTurnSmall(45, 650, 1);
  //   LeftPlow.set(true);
  //   wait(200,msec);
  //   inchDrive(-18, 1100, 2);
  //   wait(200,msec);
  //   gyroTurnSmall(-135, 1400, 3);
  //   wait(200,msec);
  //   intakeToggle(100);
  //   wait(200,msec);
  //   inchDrive(-26, 725, 4);
  //   wait(200,msec);
  //   gyroTurnSmall(-120, 700, 1);
  //   wait(200,msec);
  //   intakeToggleOff();
  //   wait(200,msec);
  //   inchDrive(12, 450, 3);

  // MATCH AUTON FARSIDE 11/4/2023
  // Intake.spin(forward, -100, pct);
  // inchDrive(-4, 700, 5);
  // inchDrive(16, 2000, 4);
  // wait(50,msec);
  // gyroTurnSmall(-90, 500);
  // wait(50, msec);
  // inchDrive(16, 2000, 4);
  // wait(50,msec);
  // gyroTurnSmall(-145, 400);
  // wait(50,msec);
  // inchDrive(8, 1000, 8);
  // Intake.spin(forward, 100, pct);
  // wait(50,msec);
  // inchDrive(-4, 1500, 4);
  // wait(50, msec);
  // gyroTurnSmall(-235, 760);
  // wait(50, msec);
  // inchDrive(-5, 1500, 10);
  // wait(50,msec);
  // inchDrive(18.5, 2000, 4);
  // wait(50,msec);
  // gyroTurnSmall(-245, 760);

  // gyroTurnSmall(-275,500);
  // wait(50,msec);
  // inchDrive(12,2000, 4);
  // MATCH AUTON NEARSIDE
  // Intake.spin(forward, -100, pct);
  // inchDrive(20, 3600);
  // wait(50,msec);
  // inchDrive(-6,600);
  // wait(50,msec);
  // gyroTurnSmall(130, 400);
  // wait(50,msec);
  // inchDrive(12, 1200);
  // wait(50,msec);
  // gyroTurnSmall(50, 725);
  // wait(50,msec);
  // Intake.spin(forward, 100, pct);
  // inchDrive(12,1200);
  // Intake.spin(forward,0, pct);

  // SKILLS OLD
  // inchDrive(-12, 2000, 4);
  // wait(5,msec);
  // gyroTurnSmall(30, 600);
  //  wait(5,msec);
  // slapperToggle(40);
  // Slapper.setRotation(0, rev);
  // while (shots<2){
  //   shots = Slapper.rotation(rev);
  //   wait(100, msec);
  // }
  // slapperToggle(0);
  // wait(5, msec);
  // Intake.spin(forward, 100, pct);
  // gyroTurnSmall(50, 600);
  // wait(5, msec);

  // gyroTurnSmall(30,800);

  // wait(5, msec);
  // inchDrive(34, 3000, 6);
  //     wait(5, msec);
  // gyroTurnSmall(-165, 500);
  //     wait(5, msec);
  // inchDrive(20, 4000, 4);
  //     wait(5, msec);
  // LeftPlow.set(true);
  // RightPlow.set(true);
  // gyroTurnSmall(90, 500);
  // wait(5,msec);
  // inchDrive(8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(-8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(-12, 3000, 8);

  // SKILLS 11/20/23
  // inchDrive(-12, 2000, 4);
  // wait(5,msec);

  // gyroTurnSmall(20, 600);
  //  wait(5,msec);

  // slapperToggle(40);
  // Slapper.setRotation(0, rev);
  // while (shots<46){
  //   shots = Slapper.rotation(rev);
  //   wait(100, msec);
  // }
  // slapperToggle(0);
  // wait(5, msec);

  // Intake.spin(forward, 100, pct);
  // wait(5,msec);

  // gyroTurnSmall(50, 800);
  // wait(5, msec);

  // gyroTurnSmall(30,800);
  // wait(5, msec);

  // inchDrive(8, 2000, 8);
  // wait(5, msec);

  // gyroTurnSmall(-30, 800);
  // wait(5,msec);

  // inchDrive(28,3000,8);
  // wait(5,msec);

  // gyroTurnSmall(-200, 500);
  // wait(5, msec);

  // inchDrive(28, 4500, 4);
  // wait(5, msec);

  // LeftPlow.set(true);
  // RightPlow.set(true);
  // gyroTurnSmall(90, 500);
  // wait(5,msec);
  // inchDrive(8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(-8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(8, 3000, 8);
  //     wait(5, msec);
  // inchDrive(-12, 3000, 8);

  //  *IMPORTANT*
  //  GYROTURNSMALL; KP = 6.2
  //  gyroTurnSmall(-90, 249);
  //  gyroTurnSmall(-45, 350);
  //  gyroTurnSmall(-30, 450);

  // inchDrive(-12, 3000, 3.5);
  // gyroTurnSmall(70, 600, 0.7);
  // inchDrive(-1, 3000, 4);