
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       NR 7700                                                   */
/*    Created:      May 13, 2022                                              */
/*    Description:  code of Nikhil Ramanuja                                   */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// F1                   motor         2               
// F2                   motor         5               
// Injector             digital_out   A               
// LF                   motor         21              
// LB                   motor         12              
// RF                   motor         20              
// RB                   motor         4               
// Intake1              motor         1               
// turret               motor         10              
// gyro1                inertial      14              
// RotationL            rotation      9               
// RotationB            rotation      3               
// turretG              inertial      13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <math.h>

double absV(double input) { return (sqrt(input * input)); }
double targetSpeed = 0.0;
using namespace vex;
// 100 digits of pi because I like Pi𝝿
long double pi =
    3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
// A global instance of competition
competition Competition;
void flywheelMonitor();
void spinFlywheel(double);
// define your global instances of motors and other devices here
double OldError = 0.0;
double TBHval = 0.0;
double FWDrive = 0.0;
/*void inchDrive(double dist, double Speed = 1,double
  stopTime=99999999999999999, double accuracy = 0.5) { LeftBack.setRotation(0,
  rev); RightBack.setRotation(0, rev);

  dist = -dist;

  double currDist = 0;
  double speed;
  double error = dist;
  double prevError = error;
  double Kp = 16.667;   // Porportional
  double Ki = 0.5;      // Integral
  double Kd = 13.33336; // Derivative
  double sum = 0;
  Brain.Timer.reset();
  while ((abs(error) > accuracy ||
          abs(speed) > 10)) {
  float Time = Brain.timer(msec);
  // && !(wallStop && errors[0] == errors[1] &&
                               // errors[1] == errors[2] && errors[2] ==
                              //  errors[3] && errors[0] != dist)) {
    currDist = LeftBack.rotation(rev) * pi * diameter;
    error = dist - currDist;
    sum = sum * 0.8 + error;
    speed = Kp * error + Ki * sum + Kd * (error - prevError);

    drive(speed * Speed, speed * Speed, 10);

    prevError = error;
    if(Time>stopTime){
      break;
    }
  }
               }*/
void controlFlywheel1(double target) {
  double speed = F1.velocity(percent);

  spinFlywheel((target - speed) + target);
  Brain.Screen.printAt(180, 40, "fwdrive %.1f  ", target);

  Brain.Screen.printAt(1, 40, " speed = %.2f ", speed);
}
// ODOMETERY

double x = 0, y = 0; // declare global x and y

int odometery() {
  double prevHeading = gyro1.heading();
  double deltaHeading = 0; // change in heading
  double absoluteOrientation = pi;
  double localX;            // local x to use in loop
  double localY;            // local y to use in loop
  double lRad = 1.375;      // radius of tracking wheel
  double bRad = 1.375;      // radius of tracking wheel
  double Sl = 4.5;          // distance of left wheel to tracking center
  double Sb = 3;            // distance of back wheel to tracking center
  double lEncoder = 0;      // declaring encoder variable left
  double bEncoder = 0;      // declaring encoder variable back
  double distL = 0;         // distance left encoder has traveled
  double distB = 0;         // distance back encoder has traveled
  double prevLE = lEncoder; // create previous encoder value left
  double prevBE = bEncoder; // create previous encoder value back
  while (1) {

    lEncoder = RotationL.position(degrees);
    bEncoder = RotationB.position(degrees);

    distL = ((lEncoder - prevLE) * pi / 180) * lRad;
    // convert encoder distance into distance traveled
    distB = ((bEncoder - prevBE) * pi / 180) * bRad;
    // convert encoder distance into disntance traveled

    prevLE = lEncoder; // create previous encoder value left
    prevBE = bEncoder; // create previous encoder value back

    absoluteOrientation = (360 - gyro1.heading(degrees)) * pi / 180.0;
    deltaHeading =
        absoluteOrientation - prevHeading; // calculate change in heading
    double averageHeading = prevHeading + deltaHeading / 2;
    prevHeading = absoluteOrientation;

    if (deltaHeading == 0) {
      localX = distL;
      localY = distB;
    } else {
      localX = 2.0 * sin(deltaHeading / 2.0) * (distB / deltaHeading + Sb);
      localY = 2.0 * sin(deltaHeading / 2.0) * (distL / deltaHeading + Sl);
    }
    double globalDist = sqrt(localX * localX + localY * localY);

    double globalAngle =
        averageHeading +
        ((absV(localX) < .001) ? pi / 2 : atan(localY / localX)) +
        ((localX < 0) ? pi : 0);
    x = x + globalDist * cos(globalAngle);
    y = y + globalDist * sin(globalAngle);
    this_thread::sleep_for(5);
  }
  return 0;
}

// printstuff to controller
int ControllerPrint() {
  Brain.Timer.reset();

  while (1) {
    Controller1.Screen.setCursor(1, 1);
    double speed = F1.velocity(percent);
    Controller1.Screen.print("speed=.1%f   ", speed);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("tSpeed=.1%f  ", targetSpeed);
    if (Brain.timer(sec) == 15) {
      Controller1.rumble(".");
    } // 2 minute mark
    if (Brain.timer(sec) == 45) {
      Controller1.rumble("..");
    } // 1:30 mark
    if (Brain.timer(sec) == 75) {
      Controller1.rumble("...");
    } // 1 minute mark
    if (Brain.timer(sec) == 105) {
      Controller1.rumble("....");
    } // 30 second mark
    this_thread::sleep_for(25);
  }
  return (0);
}

void controlFlywheelSpeed(double target) {
  double kI = .025;
  double speed = F1.velocity(percent);
  double error = target - speed;
  double fwDrive = FWDrive + kI * error;
  // :D
  Brain.Screen.printAt(1, 40, " speed = %.2f ", speed);
  // Keep drive between 0 to 100%
  if (fwDrive > 100)
    fwDrive = 100;
  if (fwDrive < 0)
    fwDrive = 0;
  // Check for zero crossing
  if (error * OldError < 0) {
    fwDrive = 0.5 * (fwDrive + TBHval);
    TBHval = fwDrive;
  }

  Brain.Screen.printAt(180, 40, "fwdrive %.1f  ", fwDrive);
  spinFlywheel(fwDrive);

  FWDrive = fwDrive;
  OldError = error;
}

void spinFlywheel(double speed) {
  speed = speed * 120; // speed is in percentage so convert to mV 100% = 12000
                       // mV
  F1.spin(forward, speed, voltageUnits::mV);
  F2.spin(forward, speed, voltageUnits::mV);
}

void flywheelMonitor() {
  double current1 = F1.current();
  double current2 = F2.current();
  double t1 = F1.temperature(celsius);
  double t2 = F2.temperature(celsius);
  double b = Brain.Battery.capacity();
  Brain.Screen.setFillColor(white);
  Brain.Screen.printAt(1, 60, "F1 current = %.1f   Temp = %.1f   ", current1,
                       t1);
  Brain.Screen.printAt(1, 80, "F2 current = %.1f   Temp = %.1f   ", current2,
                       t2);
  Brain.Screen.printAt(1, 100, "Battery Capacity  = %.1f      ", b);
}
void turretSpinTo(int targetAngle) {
  double kp = 1;
  while (turretG.orientation(yaw, degrees) != targetAngle) {
    double error = targetAngle - turretG.orientation(yaw, degrees);
    turret.spin(forward, error * kp, percent);
  }
}

void pistonToggle() {

  Injector.set(true);
  wait(.5, sec);
  Injector.set(false);
}
void pistonToggleReady() {
  Brain.Screen.drawRectangle(120, 190, 60, 60, orange);
  waitUntil(F1.velocity(percent) < targetSpeed + .5 &&
            F1.velocity(percent) > targetSpeed - .5);
  Brain.Screen.drawRectangle(120, 190, 60, 60, black);

  Injector.set(true);
  wait(.5, sec);
  Injector.set(false);
  Brain.Screen.drawRectangle(120, 190, 60, 60, black);
}
bool intakeOn = false;
void toggleIntake() { intakeOn = !intakeOn; }

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

void autonomous(void) { thread odometeryTracking = thread(odometery); }

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
  thread ControllerPrinting = thread(ControllerPrint);
  bool alg = true;
  bool flag = true;
      
double offset=0;
  while (true) {

    if (Controller1.ButtonA.pressing())
      targetSpeed = 0;

    if (Controller1.ButtonB.pressing()) {
      intakeOn = !intakeOn;
      wait(10, msec);
    }
    
      if(Controller1.ButtonL2.pressing()){
        offset++;
        wait(10, msec);
      }
      if(Controller1.ButtonR2.pressing()){
        offset--;
        wait(10, msec);
      }

        
    
    if (Controller1.ButtonY.pressing())
      targetSpeed = 34;
    if (Controller1.ButtonX.pressing())
      targetSpeed = 70;
    if (Controller1.ButtonUp.pressing())
      targetSpeed = 90;
    Brain.Screen.printAt(1, 20, "target speed = %.2f ", targetSpeed);
    if (Controller1.ButtonDown.pressing() && flag) {
      flag = false;
      alg = !alg;
    }
    if (!Controller1.ButtonDown.pressing()) {
      flag = true;
    }
    if (alg) {
      controlFlywheelSpeed(targetSpeed);
      Brain.Screen.printAt(1, 120, "controlled speed    ");
    } else {
      controlFlywheel1(targetSpeed);
      Brain.Screen.printAt(1, 120, "not controlled     ");
    }

    if (intakeOn) {
      Intake1.spin(forward, 130, rpm);

    } else {
      Intake1.stop(coast);
    }
    if (F1.velocity(percent) < targetSpeed + 1 &&
        F1.velocity(percent) > targetSpeed - 1) {
      Brain.Screen.drawRectangle(60, 190, 60, 60, green);

    } else {
      Brain.Screen.drawRectangle(60, 190, 60, 60, red);
    }
    flywheelMonitor();
    // tank drive code
    LF.spin(forward, Controller1.Axis3.position(), percent);
    RF.spin(forward, Controller1.Axis2.position(), percent);
    LB.spin(forward, Controller1.Axis3.position(), percent);
    RB.spin(forward, Controller1.Axis2.position(), percent);
    if (Controller1.Axis2.position() == 0 &&
        Controller1.Axis3.position() == 0) {
      LF.stop(hold);
      RF.stop(hold);
      LB.stop(hold);
      RB.stop(hold);
    }
    double turretAngle = turretG.orientation(yaw, degrees);
    double targetAngle = (-1 * gyro1.orientation(yaw, degrees))+offset;
    if (targetAngle != turretAngle) {
      if (targetAngle > 95) {
        targetAngle = 95;
      }
      if (targetAngle < -75) {
        targetAngle = 75;
      }
      turretSpinTo(targetAngle);
    }
    turretG.orientation(yaw, degrees);

    wait(10, msec);
  }
}

// Main will set up the competition functions and callbacks.
//
int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  Controller1.ButtonL1.pressed(pistonToggle);
  Controller1.ButtonRight.pressed(pistonToggleReady);
  Controller1.ButtonL2.pressed(toggleIntake);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
