/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      5/15/2025, 4:31:28 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

//Brain/Control
controller Controller1;
brain Brain;

//Drive Motors
motor RF (PORT17, ratio18_1 , true);
motor RB (PORT18, ratio18_1 , true);
motor LF (PORT16, ratio18_1 , false);
motor LB (PORT19, ratio18_1 , false);

//other motors
motor intake(PORT21, ratio6_1, true);
motor clamp (PORT11, ratio18_1, false);

//Gyro
inertial GYRO (PORT20);

 //Define Costants
 float WD = 4;
 float GR = 1;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//Function to stop robot
//Function to stop robot
void Robotstop() {
RF.stop (brake);
RB.stop (brake);
LF.stop (brake);
LB.stop (brake);
} 

//Function to drive robot
void Robotdrive (int Lspeed, int Rspeed, int duration) {
RF.spin (fwd, Rspeed, pct);
RB.spin (fwd, Rspeed, pct);
LF.spin (fwd, Lspeed, pct);
LB.spin (fwd, Lspeed, pct);
wait (duration, msec);
}


void inchDrive (float inches){
  float x = 0;
  float error = inches - x;
  float KP = 3.0;
  float speed =  error * KP;

LF.resetPosition();
LB.resetPosition();
RF.resetPosition();
RB.resetPosition();

while (fabs (error) > 0.5){
Robotdrive(speed, speed, 10);
x = LF.position(rev) * WD * M_PI * GR;
error = inches - x;
speed = error * KP;
}
Robotstop();

}


void Pturn (float targetDegrees) {
  float heading = GYRO.rotation (deg);
  float error = targetDegrees - heading;
  float Kp = 0.5;
  float speed = Kp * error;

  while (fabs (error) > 5){
    Robotdrive (-speed, speed, 30);
    wait (30, msec);

    heading = GYRO.rotation (deg);
    error = heading -targetDegrees;
    speed = error * Kp;

  }
  Robotstop();
}


void turntoAngle (float targetAngle){
float error = 0;
float lastError = 0;

float Kp = 2.0;

float Ki = 0.5;
float totalError = 0;

float Kd = 0.5;
float derivitive = 0;

float speed = 0;
float currentAngle = GYRO.heading();

while (true) {
  error = targetAngle - currentAngle;
  totalError = +error;
  derivitive = error - lastError;
  speed = (Kp * error) + (Ki * totalError) + (Kd * derivitive);  
  

  if (error > 180) error = error - 360;
  if (error < -180) error = error + 360;

  Robotdrive (speed, -speed, 10);

  if (fabs(error)<1.0) break; 
  lastError = error;
}
Robotstop ();
}


double YOFFSET = 20; //offset for the display
//Writes a line for the diagnostics of a motor on the Brain
void MotorDisplay(double y, double curr, double temp)
{
	Brain.Screen.setFillColor(transparent);
	Brain.Screen.printAt(5, YOFFSET + y, "Current: %.1fA", curr);
	
	if (curr < 1){
		Brain.Screen.setFillColor(green);
	} else if(curr >= 1 && curr  <= 2.5) {
		Brain.Screen.setFillColor(yellow);
	} else {
		Brain.Screen.setFillColor(red);
		Brain.Screen.drawRectangle(140, YOFFSET + y - 15, 15, 15);
	}

	
	Brain.Screen.setFillColor(transparent);
	Brain.Screen.printAt(160, YOFFSET + y, "Temp: %.1fC", temp);
	
	if (temp < 45){
		Brain.Screen.setFillColor(green);
	} else if(temp <= 50 && temp  >= 45){
		// TRUE and TRUE --> True
		// TRUE and FALSE --> False
		// FALSE and FALSE --> False
		Brain.Screen.setFillColor(yellow);
	} else {
		Brain.Screen.setFillColor(red);
		Brain.Screen.drawRectangle(275, YOFFSET + y - 15, 15, 15);
		Brain.Screen.setFillColor(transparent);
	}
}


//Displays information on the brain
void Display()
{
	double LFCurr = LF.current(amp);
	double LFTemp = LF.temperature(celsius);
	double LBCurr = LB.current(amp);
	double LBTemp = LB.temperature(celsius);
	double RFCurr = RF.current(amp);
	double RFTemp = RF.temperature(celsius);
	double RBCurr = RB.current(amp);
	double RBTemp = RB.temperature(celsius);


	if (LF.installed()){
		MotorDisplay(1, LFCurr, LFTemp);
		Brain.Screen.printAt(300, YOFFSET + 1, "LF");
	} else {
		Brain.Screen.printAt(5, YOFFSET + 1, "LF Problem");
	}
	
	
	if (LB.installed()){
		MotorDisplay(31, LBCurr, LBTemp);
		Brain.Screen.printAt(300, YOFFSET + 31, "LB");
	} else {
		Brain.Screen.printAt(5, YOFFSET + 31, "LB Problem");
	}


	if (RF.installed()) {
		MotorDisplay(61, RFCurr, RFTemp);
		Brain.Screen.printAt(300, YOFFSET + 61, "RF");
	} else {
		Brain.Screen.printAt(5, YOFFSET + 61, "RF Problem");
	}
	
	
	if (RB.installed()) {
		MotorDisplay(91, RBCurr, RBTemp);
		Brain.Screen.printAt(300, YOFFSET + 91, "RB");
	} else {
		Brain.Screen.printAt(5, YOFFSET + 91, "RB Problem");
	}

}


void pre_auton(void) {

 while (GYRO.isCalibrating()) wait (200, msec);
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
//motor stopping type
clamp.setStopping (hold);

  //Clamp Preset
clamp.spin (reverse, 50, pct);
wait(1000, msec);
clamp.stop (hold);
//start
wait(100, msec);
inchDrive (-29);
wait(100, msec);
clamp.spin (fwd, 50, pct);
wait(1000, msec);
clamp.stop (hold);
wait(100, msec);
Pturn (-85);
wait(100, msec);
intake.spin (fwd, 100, pct);
wait(100, msec);
inchDrive (17);
wait(100, msec);


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
    Display(); 
//motor stopping type
clamp.setStopping (hold);

      int lspeed = Controller1.Axis3.position(pct);

      int rspeed = Controller1.Axis2.position(pct);
      Robotdrive(rspeed, lspeed, 10);

      if (Controller1.ButtonR2.pressing()) {
       intake.spin(fwd, -85, pct);   
      }
      else if (Controller1.ButtonR1.pressing()){
     intake.spin(fwd, 85, pct);
      }
      else { (intake.stop()); } 

      if (Controller1.ButtonL2.pressing()) {
        clamp.spin(fwd, -85, pct);   
       }
       else if (Controller1.ButtonL1.pressing()){
      clamp.spin(fwd, 85, pct);
       }
       else { (clamp.stop()); } 

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
