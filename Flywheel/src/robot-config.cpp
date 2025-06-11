#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
<<<<<<< HEAD
motor F1 = motor(PORT2, ratio6_1, false);
motor F2 = motor(PORT20, ratio6_1, true);
=======
motor F1 = motor(PORT1, ratio18_1, false);
motor F2 = motor(PORT2, ratio18_1, true);
>>>>>>> 73474b82654e2e927fa359541e03f9b8b9b80751

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