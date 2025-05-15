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
/*vex-vision-config:begin*/
signature Vision21__SNAIL = signature (1, -5827, -5397, -5612, -3855, -3413, -3634, 2.5, 0);
signature Vision21__SENSOR = signature (2, 4249, 5249, 4749, 917, 1555, 1236, 3, 0);
vision Vision21 = vision (PORT21, 50, Vision21__SNAIL, Vision21__SENSOR);
/*vex-vision-config:end*/

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