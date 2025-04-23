using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LIntake;
extern motor RIntake;
extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;
extern motor Tray;
extern motor Lift;
extern inertial IMU;
extern encoder EncoderA;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );