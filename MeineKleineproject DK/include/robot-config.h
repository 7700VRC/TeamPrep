using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor RMmotor;
extern motor LMmotor;
extern motor RFmotor;
extern motor LBmotor;
extern motor RBmotor;
extern motor LFmotor;
extern inertial Gyro;
extern optical Color;
extern distance Dist;
extern motor Intake;
extern signature Vision21__SNAIL;
extern signature Vision21__SENSOR;
extern signature Vision21__SIG_3;
extern signature Vision21__SIG_4;
extern signature Vision21__SIG_5;
extern signature Vision21__SIG_6;
extern signature Vision21__SIG_7;
extern vision Vision21;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );