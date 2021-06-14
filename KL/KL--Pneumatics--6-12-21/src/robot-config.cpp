#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT9, ratio18_1, false);
controller Controller1 = controller(primary);
motor RightMotor = motor(PORT1, ratio18_1, false);


digital_out dig1 = digital_out(Brain.ThreeWirePort.A);
digital_out dig2 = digital_out(Brain.ThreeWirePort.B);
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
// VEXcode generated functions
// define variable for remote controller enable/disable