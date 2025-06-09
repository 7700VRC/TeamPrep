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
    motor  rf = motor(PORT20);
    motor  rb = motor(PORT17);
    motor  lf = motor(PORT13,true);
    motor  lb = motor(PORT14,true);
    controller controller1;
// define your global instances of motors and other devices here
      void drive(int lspeed, int rspeed, int wt){
     lf.spin(fwd,lspeed,pct);
     lb.spin(fwd,lspeed,pct);
     rf.spin(fwd,rspeed,pct);
     rb.spin(fwd,rspeed,pct);
     wait(wt,msec);
void brakeDrive(brakeType type)
    lf.stop(type);
    lb.stop(type);
    rf.stop(type);
    rb.stop(type);
void inchDrive(double inches){
    float pi = 3.1415926;
    float dia = 4;
    lf resetPosition();
    rf resetPosition();
    float target = dia * pi 
    float distanceTraveled = rf.position(rev)
    float avgRev = (rf.position(rev)+lf.position(rev))/2;
    float distanceTraveled = avgRev * dia*pi;
    while(distanceTraveled<inches){
        drive(25,25,10);
            avgRev = (rf.position(rev) + lf.position(rev))/2
            distanceTraveled = avgrev * dia * pi;




}}
     
      int main() { 
        

        while(1) {
        int lstick = controller1.Axis3.position();
        int rstick = controller1.Axis2.position();
        drive(lstick,rstick, 15);
        this_thread::sleep_for(10);



        }




   







}
