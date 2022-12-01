using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FR;
extern motor BL;
extern motor BR;
extern motor FL;
extern controller Controller1;
extern motor intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );