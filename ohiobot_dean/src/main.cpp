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
// LM                   motor         19              
// RM                   motor         18              
// Controller1          controller                    
// Gyro                 inertial      3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances (variables) of motors and other devices here
float D = 4.0;
float G = 1.0;
float Pi = 3.14;

std::string autonRoutine;
int autonRunning;

#include "vex.h"

using namespace vex;

void drawGUI(std::string screen) {
  if (screen == "menu") {
    autonRoutine = "null";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("         Red  Blue   ");
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Left    (UP)   (X)");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Right  (DWN)  (B)");

    Brain.Screen.clearScreen();
    Brain.Screen.setPenWidth(3);
    Brain.Screen.setPenColor(white);

    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(20, 17, 210, 90);
    Brain.Screen.drawRectangle(20, 127, 210, 90);

    Brain.Screen.setFont(propL);
    Brain.Screen.setCursor(2, 3);
    Brain.Screen.print("Red Left");
    Brain.Screen.setCursor(6, 3);
    Brain.Screen.print("Red Right");

    Brain.Screen.setFont(propM);
    Brain.Screen.setCursor(4, 4);
    Brain.Screen.print("Goal Zone (Red)");
    Brain.Screen.setCursor(10, 4);
    Brain.Screen.print("Goal Zone (Red)");

    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(250, 17, 210, 90);
    Brain.Screen.drawRectangle(250, 127, 210, 90);

    Brain.Screen.setFont(propL);
    Brain.Screen.setCursor(2, 19);
    Brain.Screen.print("Blue Left");
    Brain.Screen.setCursor(6, 19);
    Brain.Screen.print("Blue Right");

    Brain.Screen.setFont(propM);
    Brain.Screen.setCursor(4, 28);
    Brain.Screen.print("Goal Zone (Blue)");
    Brain.Screen.setCursor(10, 28);
    Brain.Screen.print("Goal Zone (Blue)");

    wait(0.3, seconds);

    if (autonRunning == 0) {
      while (1 == 1) {
        if (Brain.Screen.pressing()) {
          if (Brain.Screen.xPosition() <= 240) {
            if (Brain.Screen.yPosition() <= 138) {
              drawGUI("redLeft");
              break;
            } else {
              drawGUI("redRight");
              wait(0.25, seconds);
              break;
            }
          } else {
            if (Brain.Screen.yPosition() <= 138) {
              drawGUI("blueLeft");
              break;
            } else {
              drawGUI("blueRight");
              break;
            }
          }
        }
        else if (Controller1.ButtonUp.pressing()){
          drawGUI("redLeft");
          break;
        }
        else if (Controller1.ButtonDown.pressing()){
          drawGUI("redRight");
          break;
        }
        else if (Controller1.ButtonX.pressing()){
          drawGUI("blueLeft");
          break;
        }
        else if (Controller1.ButtonB.pressing()){
          drawGUI("blueRight");
          break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "redLeft") {
    autonRoutine = "redLeft";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Red - Left");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(red);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Red (Left)");
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.setFont(propM);
    Brain.Screen.print("Auton Selected");

    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(43, 145, 102, 48);
    Brain.Screen.setCursor(9, 7);
    Brain.Screen.print("Go Back");

    if (autonRunning == 0) {
      while (1 == 1) {
        if (Brain.Screen.pressing()) {
          if (Brain.Screen.yPosition() >= 140) {
            drawGUI("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawGUI("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "redRight") {
    autonRoutine = "redRight";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Red - Right");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(red);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Red (Right)");
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.setFont(propM);
    Brain.Screen.print("Auton Selected");

    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(43, 145, 102, 48);
    Brain.Screen.setCursor(9, 7);
    Brain.Screen.print("Go Back");

    wait(0.5, seconds);

    if (autonRunning == 0) {
      while (1 == 1) {
        if (Brain.Screen.pressing()) {
          if (Brain.Screen.yPosition() >= 140) {
            drawGUI("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawGUI("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "blueLeft") {
    autonRoutine = "blueLeft";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Blue - Left");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(blue);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Blue (Left)");
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.setFont(propM);
    Brain.Screen.print("Auton Selected");

    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(43, 145, 102, 48);
    Brain.Screen.setCursor(9, 7);
    Brain.Screen.print("Go Back");

    wait(0.5, seconds);

    if (autonRunning == 0) {
      while (1 == 1) {
        if (Brain.Screen.pressing()) {
          if (Brain.Screen.yPosition() >= 140) {
            drawGUI("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawGUI("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "blueRight") {
    autonRoutine = "blueRight";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Blue - Right");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(blue);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Blue (Right)");
    Brain.Screen.setCursor(5, 5);
    Brain.Screen.setFont(propM);
    Brain.Screen.print("Auton Selected");

    Brain.Screen.setPenColor(white);
    Brain.Screen.drawRectangle(43, 145, 102, 48);
    Brain.Screen.setCursor(9, 7);
    Brain.Screen.print("Go Back");

    wait(0.5, seconds);

    if (autonRunning == 0) {
      while (1 == 1) {
        if (Brain.Screen.pressing()) {
          if (Brain.Screen.yPosition() >= 140) {
            drawGUI("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawGUI("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "autonRun") {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(propM);
    Brain.Screen.setCursor(2,3);
    Brain.Screen.print("Autonomous in Progress");
    Brain.Screen.setCursor(3,3);
  } else if (screen == "driverControlRun") {
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(propM);
    Brain.Screen.setCursor(2,3);
    Brain.Screen.print("Driver Control Started");
    wait(5, seconds);
    Brain.Screen.drawImageFromFile("logo.png", 0, 0);
  }
}

void drive(int lspeed, int rspeed, int wt) {
  LM.spin(forward, lspeed, percent);
  RM.spin(forward, rspeed, percent);
  wait(wt, msec);
}

void driveBrake() {
  LM.stop(brake);
  RM.stop(brake);
}

void inchDrive(float target, float speed = 50) {
  // Local variables
  float accuracy = 0.2;
  float x = 0.0;
  float error = target - x;

  LM.setRotation(0, rev);
  while (fabs(error) > accuracy) {
    speed = fabs(speed) * fabs(error) / error;
    drive(speed, speed, 10);
    x = G * LM.rotation(rev) * Pi * D;
    error = target - x;
  }
  driveBrake();
}

void gyroTurn(float target) {
  Gyro.setRotation(0.0, deg);
  float heading = 0.0;
  float error = target - heading;
  float accuracy = 1.0;
  float speed = 30;
  float kp = 1.0;
  float b = 5;
  while (fabs(error) > accuracy) {
    speed = kp * error + b * fabs(error) / error;
    drive(speed, -speed, 10);
    heading = Gyro.rotation(deg);
    error = target - heading;
  }
  driveBrake();
}
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
  Brain.Screen.drawImageFromFile("logo.png", 0, 0);
  wait(2, seconds);
  drawGUI("menu");
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

void autonomous() {
  drawGUI("autonRun");
    if(autonRoutine == "redLeft")
    {
        inchDrive(24, 30);
        inchDrive(-24, 30);
        gyroTurn(-90);
    }

    else if(autonRoutine == "redRight")
          {
        inchDrive(24, 100);
        inchDrive(-24, 100);
        gyroTurn(90);
    }

    else if(autonRoutine == "blueLeft")
          {
        inchDrive(24, 100);
        inchDrive(-24, 100);
        gyroTurn(-90);
    }

    else if(autonRoutine == "blueRight")
          {
        inchDrive(24, 100);
        inchDrive(-24, 100);
        gyroTurn(90);
    }

    else if(autonRoutine == "null")
          {
        inchDrive(5, 50);
        gyroTurn(45);
        inchDrive(100, 80);
        gyroTurn(-160);
        inchDrive(-15, 30);
    }
    
    //...
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
  while (true) {
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