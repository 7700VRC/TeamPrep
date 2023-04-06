#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RMmotor = motor(PORT2, ratio18_1, true);
motor LMmotor = motor(PORT1, ratio18_1, false);
motor RFmotor = motor(PORT17, ratio18_1, true);
motor LBmotor = motor(PORT16, ratio18_1, true);
motor RBmotor = motor(PORT15, ratio18_1, false);
motor LFmotor = motor(PORT19, ratio18_1, false);
inertial Gyro = inertial(PORT3);
optical Color = optical(PORT4);
distance Dist = distance(PORT5);
motor Intake = motor(PORT13, ratio6_1, false);

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