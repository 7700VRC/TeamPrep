using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RM;
extern motor LM;
extern motor RF;
extern motor LB;
extern motor RB;
extern motor LF;
extern motor Intake;
extern inertial Gyro;
extern optical Color;
extern distance Dist;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );