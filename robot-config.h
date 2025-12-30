using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Ldrive;
extern motor Rdrive;
extern motor Lintake;
extern motor Rintake;
extern motor Conv;
extern motor moGo;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );