using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LM;
extern motor RM;
extern inertial Gyro;
extern motor Lift;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );