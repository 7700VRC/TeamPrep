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
vex::brain Brain;
inertial gyro1 = inertial(PORT9);
motor lf = motor(PORT15, true);
motor rf = motor(PORT12);
motor lb = motor(PORT8, true);
motor rb = motor(PORT14);
controller Conteroler1;

void gyroPrint(){
    Brain.Screen.printAt(10, 60, "angle = %.3f", gyro1.rotation());
}

void drive(int lspeed, int rspeed, int wt)
{
    lf.spin(fwd, lspeed, pct);
    rf.spin(fwd, rspeed, pct);
    lb.spin(fwd, lspeed, pct);
    rb.spin(fwd, rspeed, pct);

    wait(wt, msec);
}
void breakDrive(brakeType type = brake)
{
    lf.stop(type);
    rf.stop(type);
    lb.stop(type);
    rb.stop(type);
}
void gyroturn (float degrees ){
    float target = degrees;
    float degrees_right_now = gyro1.rotation();
    if(target > 0 and degrees_right_now < target ){
        drive(+1, -1, 760);
}
    if (target < 0 and degrees_right_now > target ){
        drive(-1, +1, 760);

    }
}
void pgyroturn(float target){
    float kp = 0.7;
    float error = target - gyro1.yaw();
    float accuracy = 3;
    while (fabs(error)>accuracy){
        error = target - gyro1.rotation();
        float speed = kp * error;
        drive(speed, -speed,10);
    }
    breakDrive();
    
}

void pinchdrive(float target2){
    float pi = 3.1415926;
    float dia = 4;
    float avgRev = (rf.position(rev) + lf.position(rev)) / 2;
    float dist = avgRev * (dia * pi);
    float error = target2 - dist;


} 

























        
    


    


    


// define your global instances of motors and other devices here

void inchDrive(double inches)
{
    float pi = 3.1415926;
    float dia = 4;
    lf.resetPosition();
    rf.resetPosition();
    float avgRev = (rf.position(rev) + lf.position(rev)) / 2;
    float dist = avgRev * (dia * pi);
    while (dist < inches)
    {
        avgRev = (rf.position(rev) + lf.position(rev)) / 2;
        dist = avgRev * dia * pi * 1.5;
        drive(10, 10, 10);
    }
    breakDrive();
}
void turn_left(){
    drive(-10, +10, 1500);
    breakDrive();
}
void turn_right(){
    drive(+10, -10, 1500);
    breakDrive();
}
void turn_qur_left(){
    drive(-10, +10, 760);
    breakDrive();
}



void obstaclecourse(){


    inchDrive(23);
    turn_right();
    inchDrive(15.5);
    turn_qur_left();
    inchDrive(16.5);
    inchDrive(15.5);
    turn_qur_left();
    turn_right();
    inchDrive(13);
    turn_left();
    inchDrive(24.5);
    turn_qur_left();
    inchDrive(13);
    turn_qur_left();
    inchDrive(13);
    turn_left();
    inchDrive(22);


}
/* code */

int main()
{

    int max_speed = 100;
    gyro1.calibrate();
    
    breakDrive();
        while (gyro1.isCalibrating() == true){
        wait(10,msec);
        }
        pgyroturn(90);
    while(1) {
    
            
    
        

        Conteroler1.Screen.setCursor(1,1);
        Conteroler1.Screen.print("%d ", max_speed);

        if(Conteroler1.ButtonL1.pressing() and Conteroler1.ButtonR2.pressing()){
            max_speed--;
        }

        if(Conteroler1.ButtonL1.pressing() and Conteroler1.ButtonR1.pressing()){
                max_speed++;
            }

        int lstick = Conteroler1.Axis3.position();
        int rstick = Conteroler1.Axis1.position();

        lstick = Conteroler1.Axis3.position() / 100 * max_speed;
        rstick = Conteroler1.Axis1.position() / 100 * max_speed;

        drive(lstick+rstick,lstick-rstick,10);
       

    }
}

//45, 90deg, 30.5, 45deg, 34, 45deg, 31, 45deg, 14, 90deg
