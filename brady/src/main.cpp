/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      6/9/2025, 1:08:53 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
motor rf = motor(PORT20);
motor rb = motor(PORT17);
motor lf = motor(PORT13, true);
motor lb = motor(PORT14, true);
controller controller1;
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, double wt)
{
    lf.spin(fwd, lspeed, pct);
    lb.spin(fwd, lspeed, pct);
    rf.spin(fwd, rspeed, pct);
    rb.spin(fwd, rspeed, pct);
    wait(wt, msec);
}
void brakeDrive(brakeType type)
{
    lf.stop(type);
    lb.stop(type);
    rf.stop(type);
    rb.stop(type);
}
void inchDrive(double inches)
{
    float pi = 3.1415926;
    float dia = 4;
    lf.resetPosition();
    rf.resetPosition();
    float target = dia * pi;
    float avgRev = (rf.position(rev) + lf.position(rev)) / 2;
    float distanceTraveled = avgRev * dia * pi;
    while (distanceTraveled < inches)
    {
        avgRev = (rf.position(rev) + lf.position(rev)) / 2;
        drive(10, 10, 10);
        distanceTraveled = avgRev * dia * pi * 1.5;
    }
    brakeDrive(brake);
}
void turn(float degrees)
{
    float time = 8.333 * fabs(degrees);
    if (degrees > 0)
    {
        drive(20, -20, time);
    }
    else
    {
        drive(-20, 20, time);
    }
    brakeDrive(brake);
}

void obstaclecourse()
{

    inchDrive(45);
    wait(1, sec);
    turn(90);
    wait(1, sec);
    inchDrive(33.5);
    wait(1, sec);
    turn(-45);
    inchDrive(32);
    turn(110);
    inchDrive(31);
    turn(-45);
    inchDrive(14);
    turn(90);
    inchDrive(26);
    turn(-95);
    inchDrive(23.5);
    turn(35);
    inchDrive(28);
    turn(-35);
    inchDrive(27.5);
    turn(-95);
    inchDrive(45);
}
int main()
{
    // turn(90);
    int maxSpeed = 100;
    while (true)
    {
        controller1.Screen.setCursor(1, 1);
        controller1.Screen.print("%d    ", maxSpeed);
        if (controller1.ButtonL1.pressing())
        maxSpeed--;
        if (controller1.ButtonR1.pressing())
        {
            maxSpeed++;
        }
        int lstick = controller1.Axis3.position() / 100 * maxSpeed;
        int rstick = controller1.Axis2.position() / 100 * maxSpeed;
        drive(lstick, rstick, 15);
        this_thread::sleep_for(10);
    } // 45, 90 deg, 33.5, 45 deg, 34, 45 deg, 31, 45 deg, 14 in, 90 deg, 26, 90 deg, 23.5, 45 deg, 28, 45 deg, 27.5 in, 90 deg, 45 in
}
