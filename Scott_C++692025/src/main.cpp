/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/9/2025, 1:09:22 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
    motor lf = motor(PORT15, true);
    motor rf = motor(PORT12);
    motor lb = motor(PORT8, true);
    motor rb = motor(PORT14);
    controller Conteroler1;
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt){
    lf.spin(fwd,lspeed,pct);
    rf.spin(fwd,rspeed,pct);
    lb.spin(fwd,lspeed,pct);
    rb.spin(fwd,rspeed,pct);

    wait(wt, msec);
}
void breakDrive(breakType type = brake){
    lf.stop(type);
    rf.stop(type);
    lb.stop(type);
    rb.stop(type);
}
void inchDrive(double inches){
    float pi = 3.1415926;
    float dia = 4;
    lf.resetPosition;
    rf.resetPosition;
    float avgRev = (rf.position(rev)+lf.position(rev))/2
    float distanceTraveled = avgRev * (dia*pi);
    while (distanceTravled<inches){
        angRev = (rf.position(rev) + lf.position(rev)) / 2
        distaneTraveled = avgRev * dia * pi;
    }
    {
        /* code */
    }
    
}

int main() {


    while(1) {
        
        int lstick = Conteroler1.Axis3.position();
        int rstick = Conteroler1.Axis1.position();
        drive(lstick+rstick,lstick-rstick,10);


    }
}

