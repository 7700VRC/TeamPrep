
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
// F1                   motor         12              
// F2                   motor         21              
// Injector             digital_out   A               
// LF                   motor         18              
// LB                   motor         19              
// RF                   motor         16              
// RB                   motor         17              
// Intake1              motor         9               
// turret               motor         10              
// gyro1                inertial      1               
// RotationL            rotation      2               
// RotationB            rotation      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <math.h>
double targetSpeed = 0.0;
using namespace vex;
//100 digits of pi because I like Pi𝝿
long double pi=3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
// A global instance of competition
competition Competition;
void flywheelMonitor();
void spinFlywheel(double);
// define your global instances of motors and other devices here
double OldError = 0.0;
double TBHval = 0.0;
double FWDrive = 0.0;

void controlFlywheel1(double target) {
  double speed = F1.velocity(percent);

  spinFlywheel((target - speed) + target);
  Brain.Screen.printAt(180, 40, "fwdrive %.1f   ", target);

  Brain.Screen.printAt(1, 40, " speed = %.2f    ", speed);
}
//ODOMETERY
//global odom variables
double x,y;
double headingDeg = gyro1.heading();
double headingRad = headingDeg*pi/180;

int odometery (){
double lRad = 1.375; //radius of tracking wheel
double bRad = 1.375; //radius of tracking wheel
double Sr = 4.5; //disatnce of right wheel to tracking center
double Sb=3;
double lEncoder=0;
double bEncoder=0;
x=0;
y=0;

while(1){
headingDeg = gyro1.heading();
headingRad = headingDeg*pi/180;
double prevLE=lEncoder;
double prevBE=bEncoder;
lEncoder=RotationL.angle();
bEncoder=RotationB.angle();

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
    Controller1.Screen.print("speed=%.2f   ", speed);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("targetSpeed=%.2f  ", targetSpeed);
    if(Brain.timer(sec)==15){Controller1.rumble(".");}//2 minute mark
    if(Brain.timer(sec)==45){Controller1.rumble("..");}//1:30 mark
    if(Brain.timer(sec)==75){Controller1.rumble("...");}//1 minute mark
    if(Brain.timer(sec)==105){Controller1.rumble("....");}//30 second mark
   this_thread::sleep_for(25);
   
  }
  return(0);
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

void autonomous(void) {
thread odometeryTracking =thread(odometery);
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
thread ControllerPrinting = thread(ControllerPrint);
  bool alg = true;
  bool flag = true;

  while (true) {


    if (Controller1.ButtonA.pressing())
      targetSpeed = 0;

    if (Controller1.ButtonB.pressing()) {
      intakeOn = !intakeOn;
      wait(100, msec);
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
    if(Controller1.ButtonR1.pressing()){
      targetSpeed++;
    }
     if(Controller1.ButtonL1.pressing()){
      targetSpeed--;
    }
    if (alg) {
      controlFlywheelSpeed(targetSpeed);
      Brain.Screen.printAt(1, 120, "controlled speed    ");
    } else {
      controlFlywheel1(targetSpeed);
      Brain.Screen.printAt(1, 120, "not controlled     ");
    }

    if (intakeOn) {
      Intake1.spin(forward, 100, percent);

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
    LF.spin(forward,Controller1.Axis3.position(), percent);
    RF.spin(forward,Controller1.Axis2.position(), percent);
    LB.spin(forward,Controller1.Axis3.position(), percent);
    RB.spin(forward,Controller1.Axis2.position(), percent);
    if (Controller1.Axis2.position()==0 &&Controller1.Axis3.position() == 0) {
      LF.stop(hold);
      RF.stop(hold);
      LB.stop(hold);
      RB.stop(hold);
    }
    

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
