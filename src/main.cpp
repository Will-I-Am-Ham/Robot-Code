/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4, 6   
// Controller1          controller                    
// Intake               motor         5               
// Flywheel             motor         7               
// Lift                 motor         8               
// Left_Intake          digital_out   A               
// Right_Intake         digital_out   B               
// Left_Wing            digital_out   C               
// Right_Wing           digital_out   D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
//left is neg
void autonomous(void) {
  // Drivetrain.setTurnVelocity(100, pct);
  // Drivetrain.setTurnConstant(0.45);
  // Drivetrain.setDriveVelocity(100, pct);
  // Left_Wing.set(true);
  // wait(1000, msec);
  // Left_Wing.set(false);
  // Intake.spin(reverse, 100, pct);
  // Drivetrain.driveFor(forward, 24, inches);
  // Intake.stop();
  // Drivetrain.driveFor(reverse, 33, inches);
  // Drivetrain.turnFor(-60, degrees);
  // Drivetrain.driveFor(reverse, 19, inches);
  // Drivetrain.turnFor(-45, degrees);
  // Left_Wing.set(true);
  // Right_Wing.set(true);
  // Drivetrain.driveFor(reverse, 10, inches);
  // Right_Wing.set(false);
  // Left_Wing.set(false);
  // Drivetrain.driveFor(forward, 5, inches);
  // Drivetrain.turnFor(180, degrees);
  // Drivetrain.driveFor(forward, 10, inches);
  // Intake.spinFor(forward,1000,degrees);


// //winpoint auton simple
//   Drivetrain.setTurnVelocity(100, pct);
//   Drivetrain.setTurnConstant(0.45);
//   Drivetrain.setDriveVelocity(100, pct);
//   Drivetrain.driveFor(forward, 20, inches);
//   //idk that wing
//   wait(200,msec);
//   Drivetrain.driveFor(reverse, 18, inches);
//   Drvietrain.spin(reverse, 100);
//   Drivetrain.turnFor(-45, degrees);
//   Drivetrain.stop();
//   Lift.turnFor(-2160, degrees);
//   Drvietrain.spin(reverse, 100);

//winpoint auton hard
  Drivetrain.setTurnVelocity(100, pct);
  Drivetrain.setTurnConstant(0.45);
  Drivetrain.setDriveVelocity(100, pct);

  Intake.spin(reverse, 100, pct);
  Drivetrain.driveFor(forward, 60, inches);
  wait(300,msec);
  Intake.stop();
  Drivetrain.driveFor(reverse, 60, inches);
  Drivetrain.turnFor(-70,degrees);
  Drivetrain.driveFor(forward, 20, inches);
  //idk that wing
  wait(200,msec);
  Drivetrain.driveFor(reverse, 18, inches);
  Drvietrain.spin(reverse, 100);
  Drivetrain.turnFor(-45, degrees);
  Drivetrain.stop();
  Lift.turnFor(-2160, degrees);
  Drvietrain.spin(reverse, 100);

  /*
  Intake.spinFor(forward,1000,degrees);
  //First ball done
  Drivetrain.driveFor(reverse, 22, inches);
  Drivetrain.turnFor(-75, degrees);
  Intake.spin(reverse, 100, pct);
  Drivetrain.driveFor(forward, 24, inches);
  Intake.stop();
  //Done with second ball
  Drivetrain.driveFor(reverse, 7, inches);
  Drivetrain.turnFor(90, degrees);
  Drivetrain.driveFor(forward, 24, inches);
  Intake.spinFor(forward,1000,degrees);
  Drivetrain.driveFor(reverse, 7, inches);
  Drivetrain.turnFor(-100, degrees); //change for perfect midle ball
  Intake.spin(reverse, 100, pct);
  Drivetrain.driveFor(forward, 10, inches);
  Intake.stop();
  //Second Ball Done 
  Drivetrain.driveFor(reverse, 3, inches);
  Drivetrain.turnFor(-45, degrees);
  */
  


  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
