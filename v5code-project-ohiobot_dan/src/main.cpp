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
// LM                   motor         1               
// RM                   motor         2               
// Controller1          controller                    
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
int autonToRun = 0;

void drawScreen(std::string screen) {
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
              drawScreen("redRoller");
              autonToRun = 1;
              break;
            } else {
              drawScreen("redUnprotected");
              autonToRun = 2;
              wait(0.25, seconds);
              break;
            }
          } else {
            if (Brain.Screen.yPosition() <= 138) {
              drawScreen("blueRoller");
              autonToRun = 3;
              break;
            } else {
              drawScreen("blueUnprotected");
              autonToRun = 4;
              break;
            }
          }
        }
        else if (Controller1.ButtonUp.pressing()){
          drawScreen("redRoller");
          autonToRun = 1;
          break;
        }
        else if (Controller1.ButtonDown.pressing()){
          drawScreen("redUnprotected");
          autonToRun = 2;
          break;
        }
        else if (Controller1.ButtonX.pressing()){
          drawScreen("blueRoller");
          autonToRun = 3;
          break;
        }
        else if (Controller1.ButtonB.pressing()){
          drawScreen("blueUnprotected");
          autonToRun = 4;
          break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "redRoller") {
    autonRoutine = "redRoller";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Red - Protected");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(red);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Red (Protected)");
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
            drawScreen("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawScreen("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "redUnprotected") {
    autonRoutine = "redUnprotected";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Red - Unprotect.");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(red);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Red (Unprotected)");
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
            drawScreen("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawScreen("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "blueRoller") {
    autonRoutine = "blueRoller";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Blue - Protected");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(blue);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Blue (Protected)");
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
            drawScreen("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawScreen("menu");
            break;
        }
        wait(0.025, seconds);
      }
    }
  } else if (screen == "blueUnprotected") {
    autonRoutine = "blueUnprotected";

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Blue - Unprotect.");
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("(Left) Go Back");

    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(blue);

    Brain.Screen.setCursor(2, 3);
    Brain.Screen.setFont(propXL);
    Brain.Screen.print("Blue (Unprotected)");
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
            drawScreen("menu");
            break;
          }
        }
        if (Controller1.ButtonLeft.pressing()){
          drawScreen("menu");
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
    Brain.Screen.print("Driver Control in Progress");
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
  drawScreen("menu");
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
  inchDrive(24, 100);
  wait(1, seconds);
  inchDrive(-24, 100);
  /*
  drive(50, -20, 450);
  driveBrake();
  drive(100, 100, 4500);
  driveBrake();
  Brain.Screen.print("ohio bot has finished");
  */
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

  //Fun
  int list[1000][2] = {
    {103,122},
    {102,120},
    {100,118},
    {99,116},
    {97,114},
    {95,113},
    {94,111},
    {92,110},
    {90,108},
    {88,107},
    {86,106},
    {84,105},
    {82,104},
    {80,103},
    {77,102},
    {75,101},
    {76,99},
    {77,97},
    {78,95},
    {80,93},
    {82,92},
    {84,91},
    {85,89},
    {83,87},
    {81,87},
    {78,87},
    {76,87},
    {74,88},
    {72,89},
    {70,90},
    {68,92},
    {66,93},
    {64,95},
    {63,97},
    {62,99},
    {61,101},
    {58,101},
    {56,101},
    {54,102},
    {51,102},
    {50,102},
    {50,99},
    {51,97},
    {52,95},
    {52,93},
    {53,90},
    {54,88},
    {54,86},
    {55,84},
    {55,81},
    {56,79},
    {56,77},
    {57,74},
    {57,72},
    {57,70},
    {57,67},
    {57,65},
    {57,63},
    {58,60},
    {58,58},
    {58,55},
    {58,53},
    {58,51},
    {58,48},
    {58,46},
    {59,44},
    {59,41},
    {60,39},
    {61,37},
    {63,35},
    {64,34},
    {66,32},
    {67,30},
    {68,28},
    {69,26},
    {69,24},
    {69,21},
    {68,19},
    {67,17},
    {66,15},
    {65,13},
    {63,11},
    {62,9},
    {60,7},
    {58,6},
    {56,5},
    {54,4},
    {52,4},
    {49,3},
    {47,3},
    {45,2},
    {42,2},
    {40,2},
    {38,2},
    {35,2},
    {33,3},
    {30,3},
    {28,3},
    {26,4},
    {24,5},
    {22,6},
    {20,7},
    {18,8},
    {16,10},
    {14,12},
    {13,14},
    {12,16},
    {11,18},
    {10,20},
    {9,22},
    {9,25},
    {10,27},
    {11,29},
    {12,31},
    {13,33},
    {15,35},
    {16,36},
    {18,38},
    {19,40},
    {20,42},
    {21,45},
    {22,47},
    {22,49},
    {23,51},
    {23,54},
    {23,56},
    {23,58},
    {23,61},
    {23,63},
    {23,66},
    {23,68},
    {23,70},
    {23,73},
    {22,75},
    {21,77},
    {21,79},
    {20,81},
    {19,84},
    {18,86},
    {16,88},
    {15,90},
    {14,92},
    {13,94},
    {12,96},
    {11,98},
    {10,100},
    {9,102},
    {8,104},
    {7,107},
    {6,109},
    {5,111},
    {4,113},
    {4,115},
    {3,118},
    {3,120},
    {3,123},
    {3,125},
    {3,127},
    {4,130},
    {5,132},
    {6,134},
    {7,135},
    {9,137},
    {11,139},
    {12,141},
    {14,142},
    {16,144},
    {17,145},
    {19,147},
    {21,148},
    {23,149},
    {26,150},
    {28,151},
    {30,152},
    {32,152},
    {35,152},
    {37,153},
    {39,153},
    {42,153},
    {44,153},
    {46,153},
    {49,153},
    {51,153},
    {53,153},
    {56,153},
    {58,153},
    {60,153},
    {63,152},
    {65,152},
    {68,152},
    {70,152},
    {72,152},
    {75,152},
    {77,151},
    {79,151},
    {82,151},
    {84,151},
    {86,151},
    {89,151},
    {91,150},
    {93,150},
    {96,149},
    {98,148},
    {100,147},
    {101,145},
    {103,143},
    {104,142},
    {105,139},
    {106,137},
    {106,135},
    {106,133},
    {106,130},
    {106,128},
    {105,126},
    {104,123},
    {82,89},
    {81,91},
    {79,92},
    {77,94},
    {76,96},
    {75,98},
    {74,100},
    {72,101},
    {70,101},
    {71,99},
    {72,97},
    {74,95},
    {75,93},
    {77,92},
    {79,91},
    {81,90},
    {76,89},
    {79,89},
    {78,89},
    {76,90},
    {70,92},
    {72,91},
    {75,90},
    {75,92},
    {73,93},
    {71,94},
    {69,93},
    {70,94},
    {72,95},
    {70,97},
    {69,99},
    {67,99},
    {64,98},
    {65,97},
    {67,95},
    {66,100},
    {68,100},
    {67,101},
    {64,101},
    {63,100},
    {51,104},
    {53,103},
    {56,103},
    {58,103},
    {60,103},
    {63,102},
    {65,102},
    {67,102},
    {70,102},
    {72,103},
    {74,103},
    {77,104},
    {79,105},
    {81,105},
    {83,106},
    {85,107},
    {87,109},
    {89,110},
    {91,111},
    {93,113},
    {95,114},
    {96,116},
    {98,118},
    {100,120},
    {101,122},
    {101,124},
    {100,126},
    {99,128},
    {97,129},
    {95,130},
    {93,131},
    {90,132},
    {88,132},
    {86,133},
    {84,134},
    {81,134},
    {79,135},
    {77,135},
    {74,135},
    {72,135},
    {70,135},
    {67,135},
    {65,135},
    {63,135},
    {60,134},
    {58,133},
    {56,133},
    {54,132},
    {51,131},
    {49,130},
    {48,128},
    {46,126},
    {45,124},
    {44,122},
    {44,120},
    {44,117},
    {44,115},
    {44,113},
    {45,110},
    {45,108},
    {46,106},
    {47,105},
    {47,107},
    {46,109},
    {46,112},
    {46,114},
    {47,116},
    {47,119},
    {48,121},
    {50,122},
    {52,124},
    {52,122},
    {54,123},
    {57,123},
    {59,123},
    {61,123},
    {64,123},
    {66,123},
    {68,123},
    {71,122},
    {73,121},
    {75,120},
    {75,120},
    {72,120},
    {70,121},
    {68,121},
    {65,122},
    {63,122},
    {61,122},
    {58,121},
    {56,121},
    {54,121},
    {51,120},
    {50,119},
    {49,117},
    {48,115},
    {48,112},
    {48,110},
    {48,108},
    {49,106},
    {22,43},
    {21,41},
    {20,39},
    {19,37},
    {18,35},
    {16,33},
    {14,32},
    {13,30},
    {12,28},
    {11,26},
    {11,23},
    {11,21},
    {12,19},
    {13,17},
    {14,15},
    {16,13},
    {17,11},
    {19,10},
    {21,8},
    {23,7},
    {25,6},
    {28,5},
    {30,5},
    {32,4},
    {34,4},
    {37,4},
    {39,4},
    {42,4},
    {44,4},
    {46,4},
    {49,5},
    {51,5},
    {53,6},
    {55,7},
    {57,8},
    {59,9},
    {61,11},
    {63,13},
    {64,15},
    {65,17},
    {66,19},
    {67,21},
    {67,23},
    {67,26},
    {67,28},
    {66,30},
    {64,32},
    {63,33},
    {61,35},
    {59,37},
    {58,39},
    {58,41},
    {57,44},
    {57,46},
    {57,48},
    {56,51},
    {56,53},
    {56,55},
    {56,53},
    {55,51},
    {55,49},
    {54,47},
    {54,44},
    {53,42},
    {52,40},
    {53,38},
    {53,36},
    {51,37},
    {49,38},
    {47,38},
    {44,39},
    {42,39},
    {40,39},
    {37,39},
    {35,39},
    {33,39},
    {30,38},
    {28,38},
    {28,38},
    {30,40},
    {29,42},
    {29,44},
    {28,46},
    {27,49},
    {27,51},
    {26,53},
    {26,56},
    {25,58},
    {25,55},
    {25,53},
    {24,51},
    {24,48},
    {23,46},
    {22,44},
    {43,50},
    {45,50},
    {48,50},
    {50,49},
    {52,49},
    {54,49},
    {54,52},
    {55,54},
    {55,56},
    {55,59},
    {55,61},
    {53,62},
    {51,62},
    {49,63},
    {46,63},
    {44,64},
    {42,64},
    {39,64},
    {37,64},
    {35,64},
    {32,63},
    {30,63},
    {27,63},
    {25,63},
    {26,60},
    {26,58},
    {26,56},
    {27,53},
    {28,51},
    {28,49},
    {31,50},
    {33,50},
    {35,50},
    {38,50},
    {40,50},
    {29,47},
    {30,44},
    {31,42},
    {31,40},
    {34,40},
    {36,40},
    {38,41},
    {41,41},
    {43,40},
    {45,40},
    {48,40},
    {50,39},
    {51,39},
    {52,42},
    {53,44},
    {53,46},
    {52,48},
    {50,48},
    {47,49},
    {45,49},
    {43,49},
    {40,49},
    {38,49},
    {36,49},
    {33,49},
    {31,49},
    {29,48},
    {27,64},
    {29,64},
    {32,65},
    {34,65},
    {36,65},
    {39,65},
    {41,65},
    {44,65},
    {46,64},
    {48,64},
    {51,64},
    {53,63},
    {55,62},
    {56,64},
    {56,66},
    {55,69},
    {55,71},
    {55,74},
    {55,76},
    {54,78},
    {52,79},
    {50,79},
    {48,80},
    {45,80},
    {43,80},
    {41,80},
    {38,80},
    {36,80},
    {34,80},
    {31,79},
    {29,79},
    {27,78},
    {24,78},
    {23,76},
    {24,74},
    {24,72},
    {25,69},
    {25,67},
    {25,64},
    {24,79},
    {27,79},
    {29,80},
    {31,80},
    {33,81},
    {36,81},
    {38,81},
    {41,81},
    {43,81},
    {45,81},
    {48,81},
    {50,80},
    {52,80},
    {54,80},
    {54,82},
    {53,85},
    {52,87},
    {52,89},
    {51,91},
    {50,93},
    {48,94},
    {45,94},
    {43,94},
    {41,94},
    {38,94},
    {36,94},
    {34,94},
    {31,93},
    {29,93},
    {27,93},
    {24,92},
    {22,92},
    {20,91},
    {18,91},
    {18,89},
    {19,87},
    {20,85},
    {21,83},
    {22,80},
    {23,78},
    {13,97},
    {14,95},
    {16,93},
    {17,92},
    {20,92},
    {22,93},
    {24,93},
    {26,94},
    {29,94},
    {31,95},
    {33,95},
    {36,95},
    {38,95},
    {40,95},
    {43,95},
    {45,95},
    {47,95},
    {50,95},
    {49,97},
    {48,99},
    {47,101},
    {46,103},
    {45,105},
    {44,107},
    {42,108},
    {40,109},
    {37,109},
    {35,109},
    {32,109},
    {30,109},
    {28,109},
    {25,109},
    {23,109},
    {21,109},
    {18,108},
    {16,108},
    {14,107},
    {12,106},
    {9,105},
    {10,103},
    {11,101},
    {12,99},
    {5,117},
    {6,115},
    {6,112},
    {7,110},
    {8,108},
    {9,106},
    {11,107},
    {14,108},
    {16,109},
    {18,109},
    {21,109},
    {23,110},
    {25,110},
    {28,110},
    {30,110},
    {32,110},
    {35,110},
    {37,110},
    {39,110},
    {42,109},
    {43,109},
    {43,111},
    {42,114},
    {42,116},
    {42,118},
    {42,121},
    {40,122},
    {38,122},
    {36,123},
    {33,123},
    {31,124},
    {29,124},
    {26,124},
    {24,124},
    {21,124},
    {19,123},
    {17,123},
    {14,123},
    {12,122},
    {10,122},
    {8,121},
    {5,120},
    {8,134},
    {7,132},
    {6,130},
    {5,128},
    {5,126},
    {5,123},
    {5,121},
    {7,122},
    {9,123},
    {12,123},
    {14,124},
    {16,124},
    {19,124},
    {21,125},
    {23,125},
    {26,125},
    {28,125},
    {30,125},
    {33,124},
    {35,124},
    {37,123},
    {40,123},
    {42,122},
    {43,123},
    {44,125},
    {45,127},
    {47,129},
    {48,131},
    {47,132},
    {45,133},
    {43,134},
    {41,135},
    {39,136},
    {36,136},
    {34,137},
    {32,137},
    {29,137},
    {27,138},
    {25,138},
    {22,138},
    {20,138},
    {18,137},
    {15,137},
    {13,136},
    {11,136},
    {29,150},
    {27,149},
    {25,148},
    {23,147},
    {21,146},
    {19,145},
    {17,143},
    {15,142},
    {14,140},
    {12,138},
    {11,137},
    {13,138},
    {16,138},
    {18,138},
    {20,139},
    {23,139},
    {25,139},
    {27,139},
    {30,138},
    {32,138},
    {34,138},
    {37,137},
    {39,137},
    {41,136},
    {43,135},
    {45,134},
    {48,133},
    {50,132},
    {52,133},
    {54,134},
    {56,135},
    {55,136},
    {54,138},
    {52,140},
    {50,141},
    {48,143},
    {46,144},
    {44,145},
    {42,146},
    {40,147},
    {38,148},
    {36,149},
    {34,150},
    {31,150},
    {56,151},
    {53,151},
    {51,151},
    {49,151},
    {46,151},
    {44,151},
    {42,151},
    {39,151},
    {37,151},
    {35,151},
    {37,150},
    {39,149},
    {41,148},
    {43,147},
    {45,146},
    {47,144},
    {49,143},
    {51,142},
    {53,140},
    {55,139},
    {56,137},
    {58,135},
    {60,136},
    {62,136},
    {65,137},
    {65,139},
    {64,141},
    {63,143},
    {63,145},
    {61,147},
    {60,149},
    {58,151},
    {71,150},
    {69,150},
    {67,151},
    {64,151},
    {62,151},
    {59,151},
    {61,149},
    {62,148},
    {64,146},
    {65,143},
    {65,141},
    {66,139},
    {66,137},
    {69,137},
    {71,137},
    {74,137},
    {76,137},
    {78,137},
    {77,139},
    {77,142},
    {76,144},
    {75,146},
    {74,148},
    {72,150},
    {84,149},
    {81,149},
    {79,150},
    {77,150},
    {74,150},
    {75,149},
    {76,147},
    {77,145},
    {77,142},
    {78,140},
    {78,138},
    {80,136},
    {82,136},
    {85,135},
    {87,135},
    {89,134},
    {90,135},
    {90,137},
    {90,140},
    {89,142},
    {89,144},
    {88,146},
    {87,148},
    {95,148},
    {92,148},
    {90,149},
    {88,149},
    {88,147},
    {89,145},
    {90,143},
    {91,140},
    {91,138},
    {91,136},
    {91,133},
    {93,133},
    {95,132},
    {98,131},
    {99,129},
    {100,131},
    {100,134},
    {100,136},
    {100,138},
    {100,141},
    {99,143},
    {98,145},
    {96,147},
    {104,139},
    {103,141},
    {101,143},
    {100,145},
    {100,143},
    {101,141},
    {101,138},
    {101,136},
    {101,134},
    {101,131},
    {101,129},
    {102,127},
    {103,125},
    {104,126},
    {104,129},
    {105,131},
    {105,133},
    {105,136},
    {19,19},
    {21,20},
    {23,20},
    {25,20},
    {24,21},
    {22,22},
    {21,23},
    {23,22},
    {26,21},
    {28,20},
    {30,19},
    {31,17},
    {32,15},
    {32,13},
    {31,11},
    {29,9},
    {27,8},
    {25,8},
    {23,8},
    {21,10},
    {19,12},
    {18,14},
    {18,16},
    {19,18},
    {29,10},
    {30,11},
    {29,13},
    {26,13},
    {27,10},
    {25,11},
    {46,17},
    {48,18},
    {50,20},
    {52,21},
    {54,21},
    {57,22},
    {57,21},
    {54,20},
    {56,20},
    {59,20},
    {59,18},
    {60,16},
    {59,13},
    {58,11},
    {57,9},
    {55,8},
    {52,8},
    {50,8},
    {48,9},
    {47,11},
    {47,14},
    {46,16},
    {57,11},
    {58,13},
    {57,14},
    {55,13},
    {55,11},
    {53,11},
    {35,30},
    {37,30},
    {40,30},
    {42,30},
    {44,31},
    {46,32},
    {48,33},
    {51,34},
    {53,34},
    {55,33},
    {58,33},
    {60,31},
    {61,30},
    {63,28},
    {64,27},
    {65,26},
    {63,25},
    {61,27},
    {60,29},
    {58,30},
    {56,31},
    {54,32},
    {52,32},
    {49,32},
    {47,31},
    {45,30},
    {43,29},
    {41,28},
    {38,28},
    {36,28},
    {34,29},
    {32,30},
    {29,31},
    {27,32},
    {25,32},
    {22,32},
    {20,31},
    {18,29},
    {17,28},
    {15,26},
    {13,26},
    {14,27},
    {16,29},
    {18,31},
    {19,32},
    {21,33},
    {24,34},
    {26,34},
    {28,33},
    {31,32},
    {33,31},
    {43,26},
    {45,25},
    {44,24},
    {42,25},
    {33,26},
    {35,26},
    {35,25},
    {33,24},
  };

  for (int i = 0; i<= 1000; i++) {
    Brain.Screen.drawPixel(list[i] [0], list[i][1]);
  }

wait(2, seconds);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}