/* Noah Klein */

#include "include.hpp"

uint8_t autonIndex = AUTO_COUNT;

/* Define the controller */
pros::Controller controller(CONTROLLER_MASTER);

/* Define drive motors and motor groups */
pros::Motor frontLeft(12, true);
pros::Motor midLeft(13, false);
pros::Motor backLeft(11, true);
pros::MotorGroup leftDtMotors({19, 18, 20});

pros::Motor frontRight(19 ,false);
pros::Motor midRight(18, true);
pros::Motor backRight(20, false);
pros::MotorGroup rightDtMotors({19, 18, 20});

/* Declare other motors */
pros::Motor lift(1, true);
pros::Motor conveyor(14, false);

/* Define V5 sensors */
pros::Rotation rightEncoder(10);
pros::Rotation backEncoder(9);
pros::Imu imu(2);


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
lemlib::OdomSensors sensors(&rightTrackingWheel, nullptr, &backTrackingWheel, nullptr, &imu);


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

