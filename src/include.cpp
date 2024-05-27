/* Noah Klein */

#include "lemlib/api.hpp"
#include "include.hpp"

uint8_t autonIndex = AUTO_COUNT;

/* Define the controller */
pros::Controller controller(E_CONTROLLER_MASTER);

/* Define drive motors and motor groups */
pros::Motor frontLeft(3);
pros::Motor backLeft(2);
pros::MotorGroup leftDtMotors({2, 3});

pros::Motor frontRight(-9);
pros::Motor backRight(-10);
pros::MotorGroup rightDtMotors({-9, -10});

/* Declare other motors */

/* Define V5 sensors */
pros::Rotation rightEncoder(11);
pros::Rotation backEncoder(12);
pros::Imu imu1(6);
pros::Imu imu2(5);


/* Define LemLib objects */
lemlib::Drivetrain drivetrain {
    &leftDtMotors, // left drivetrain motors
    &rightDtMotors, // right drivetrain motors
    12, // track width
    4.125, // wheel diameter
    280, // wheel rpm
    8 // chase power (should be tuned)
};

lemlib::TrackingWheel rightTrackingWheel(&rightEncoder, lemlib::Omniwheel::OLD_275, 4.3);
lemlib::TrackingWheel backTrackingWheel(&backEncoder, lemlib::Omniwheel::OLD_275, -4.5);

                        /*  Vertical tracking wheels      Horizontal tracking wheels   IMU */
lemlib::OdomSensors sensors(&rightTrackingWheel, nullptr, &backTrackingWheel, nullptr, &imu1);


lemlib::ControllerSettings linearController(
    10, // Kp: proportional constant for the chassis controller
    30, // kI: integral: constant for the chassis controller
    1,  // kD: derivative constant for the chassis controller
    1,  // antiWindup
    1,  // smallError: the error at which the chassis controller will switch to a slower control loop
    1,  // smallErrorTimeout: the time the chassis controller will wait before switching to a slower control loop
    1,  // largeError: the error at which the chassis controller will switch to a faster control loop
    1,  // largeErrorTimeout: the time the chassis controller will wait before switching to a faster control loop
    0   // slew: the maximum acceleration of the chassis controller
);

lemlib::ControllerSettings angularController(
    2, // Kp: proportional constant for the chassis controller
    10, // kI: integral: constant for the chassis controller
    1,  // kD: derivative constant for the chassis controller
    1,  // antiWindup
    1,  // smallError: the error at which the chassis controller will switch to a slower control loop
    100,  // smallErrorTimeout: the time the chassis controller will wait before switching to a slower control loop
    3,  // largeError: the error at which the chassis controller will switch to a faster control loop
    500,  // largeErrorTimeout: the time the chassis controller will wait before switching to a faster control loop
    0   // slew: the maximum acceleration of the chassis controller
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

