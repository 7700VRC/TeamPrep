using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LM;
extern motor RM;
extern controller Controller1;
extern inertial Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );