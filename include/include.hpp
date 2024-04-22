/* Noah Klein */

#include "lemlib/api.hpp"
#include "main.h"

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

/* Constant Definitions */
#define AUTO_COUNT 3


struct autonTextTuple
{
    std::function<void()> autonomous;
    std::string autoName;
};


/* Global Variable Declaration */
extern uint8_t autonIndex;
extern autonTextTuple autos[];


/* Declare the controller */
extern pros::Controller controller;

/* Declare drive motors and motor groups */
extern pros::Motor frontRight;
extern pros::Motor midRight;
extern pros::Motor backRight;
extern pros::MotorGroup rightDtMotors;

extern pros::Motor frontLeft;
extern pros::Motor midLeft;
extern pros::Motor backLeft;
extern pros::MotorGroup leftDtMotors;

/* Declare other motors */
extern pros::Motor lift;
extern pros::Motor conveyor;

/* Declare V5 sensors */
extern pros::Rotation rightEncoder;
extern pros::Rotation backEncoder;
extern pros::Imu imu;

/* Define LemLib objects */
extern lemlib::Drivetrain drivetrain;
extern lemlib::TrackingWheel rightTrackingWheel;
extern lemlib::TrackingWheel backTrackingWheel;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::Chassis chassis;


#endif /* INCLUDE_HPP */
