using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftMotor;
extern controller Controller1;
extern motor RightMotor;
extern digital_out dig1;
extern digital_out dig2;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit(void);