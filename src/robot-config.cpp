#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT13, ratio6_1, true); 
motor leftMotorB = motor(PORT14, ratio6_1, true);
motor leftMotorC = motor(PORT16, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT11, ratio6_1, false);
motor rightMotorB = motor(PORT5, ratio6_1, false);
motor rightMotorC = motor(PORT18, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
inertial DrivetrainInertial = inertial(PORT1);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 299.24, 320, 40, mm, 0.6);
controller Controller1 = controller(primary);
motor Intake = motor(PORT17, ratio18_1, false);
motor Flywheel = motor(PORT2, ratio6_1, false);
motor Lift = motor(PORT10, ratio18_1, false);
digital_out Left_Intake = digital_out(Brain.ThreeWirePort.A);
digital_out Right_Intake = digital_out(Brain.ThreeWirePort.C);
digital_out Left_Wing = digital_out(Brain.ThreeWirePort.D);
digital_out Right_Wing = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool Flywheelfwd = false;
bool Flywheelrev = false;
void TogglePistonIntake() 
{
  if(Left_Intake.value() && Right_Intake.value())
  {
    Left_Intake.set(false);
    Right_Intake.set(false);
  }
  else
  {
    Left_Intake.set(true);
    Right_Intake.set(true);
  }
}

void ToggleFlywheelFwd() 
{
  if(!Flywheelfwd)
  {
  Flywheel.spin(forward) ; 
  Flywheelfwd = true; 
  }
  else if(Flywheelfwd)
  {
    Flywheel.stop();
    Flywheelfwd = false; 
    Flywheelrev = false; 
  }
}

void ToggleFlywheelRev() 
{
  if(!Flywheelfwd)
  {
  Flywheel.spin(reverse) ; 
  Flywheelfwd = true; 
  }
  else if(Flywheelfwd)
  {
    Flywheel.stop();
    Flywheelfwd = false; 
    Flywheelrev = false; 
  }
}
//Drivetrain.setturnconstant start with small value
void ToggleLeftWing() 
{
  if(Left_Wing.value())
  {
   Left_Wing.set(false);
  }
  else
  {
    Left_Wing.set(true);
  }
}

void ToggleRightWing() 
{
  if(Left_Wing.value())
  {
   Right_Wing.set(false);
  }
  else
  {
    Right_Wing.set(true);
  }
}





// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      Flywheel.setVelocity(100, pct);
      Intake.setVelocity(100, pct);
      Lift.setVelocity(100, pct);
      Controller1.ButtonRight.pressed(TogglePistonIntake);
      Controller1.ButtonX.pressed(ToggleFlywheelRev);
      Controller1.ButtonB.pressed(ToggleFlywheelFwd);
      Controller1.ButtonY.pressed(ToggleLeftWing);
      Controller1.ButtonA.pressed(ToggleRightWing);


      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonL1/ButtonL2 status to control Lift
      if (Controller1.ButtonL1.pressing()) {
        Lift.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Lift.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Lift.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control Intake
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        Intake.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}