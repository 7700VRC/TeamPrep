using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RMmotor;
extern motor LMmotor;
extern motor RFmotor;
extern motor LBmotor;
extern motor RBmotor;
extern motor LFmotor;
extern inertial Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );