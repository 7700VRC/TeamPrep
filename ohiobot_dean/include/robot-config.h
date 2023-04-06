using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LF;
extern motor LM;
extern motor LB;
extern motor RF;
extern motor RM;
extern motor RB;
extern motor Shooter;
extern motor Intake;
extern digital_out Indexer;
extern inertial Gyro;
extern controller Controller1;
extern optical Color;
extern distance Dist;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );