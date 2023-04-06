#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LF = motor(PORT9, ratio18_1, true);
motor LM = motor(PORT2, ratio18_1, false);
motor LB = motor(PORT7, ratio18_1, true);
motor RF = motor(PORT10, ratio18_1, false);
motor RM = motor(PORT1, ratio18_1, true);
motor RB = motor(PORT8, ratio18_1, false);
motor Shooter = motor(PORT5, ratio18_1, false);
motor Intake = motor(PORT21, ratio18_1, true);
digital_out Indexer = digital_out(Brain.ThreeWirePort.A);
inertial Gyro = inertial(PORT11);
controller Controller1 = controller(primary);
optical Color = optical(PORT3);
distance Dist = distance(PORT4);

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