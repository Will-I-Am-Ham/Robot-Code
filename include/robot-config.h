using namespace vex;

extern brain Brain;

// VEXcode devices
extern smartdrive Drivetrain;
extern controller Controller1;
extern motor Intake;
extern motor Flywheel;
extern motor Lift;
extern digital_out Left_Intake;
extern digital_out Right_Intake;
extern digital_out Left_Wing;
extern digital_out Right_Wing;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );