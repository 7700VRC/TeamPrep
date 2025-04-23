#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LIntake = motor(PORT2, ratio18_1, false);
motor RIntake = motor(PORT20, ratio18_1, true);
motor LF = motor(PORT11, ratio18_1, false);
motor RF = motor(PORT9, ratio18_1, true);
motor LB = motor(PORT12, ratio18_1, false);
motor RB = motor(PORT10, ratio18_1, true);
motor Tray = motor(PORT17, ratio36_1, true);
motor Lift = motor(PORT19, ratio18_1, false);
inertial IMU = inertial(PORT5);
encoder EncoderA = encoder(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}