#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LDriveMotorA = motor(PORT1, ratio18_1, false);
motor LDriveMotorB = motor(PORT2, ratio18_1, false);
motor_group LDrive = motor_group(LDriveMotorA, LDriveMotorB);
motor RDriveMotorA = motor(PORT9, ratio18_1, true);
motor RDriveMotorB = motor(PORT10, ratio18_1, true);
motor_group RDrive = motor_group(RDriveMotorA, RDriveMotorB);
distance LDist = distance(PORT11);
distance CDist = distance(PORT12);
distance RDist = distance(PORT13);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}