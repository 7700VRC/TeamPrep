#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Ldrive = motor(PORT1, ratio18_1, false);
motor Rdrive = motor(PORT2, ratio18_1, true);
motor Lintake = motor(PORT3, ratio18_1, false);
motor Rintake = motor(PORT4, ratio18_1, true);
motor Conv = motor(PORT5, ratio18_1, false);
motor moGo = motor(PORT6, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}