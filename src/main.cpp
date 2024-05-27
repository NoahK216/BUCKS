/* Noah Klein */

#include "include.hpp"
#include "robotFunctions.hpp"
#include "main.h"

double oldR1;

void initialize() {
	chassis.calibrate();
	oldR1 = imu1.get_rotation();
}


void disabled() {}


void competition_initialize() {}


void autonomous() {}

int counter = 0;
double emah = 0;
double corrected = 0;

void opcontrol() {
    while (true) {
		/* Get position of analog sticks */
		const int leftX = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
		const int leftY = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		const int rightX = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		const int rightY = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

        /* Move the robot */
        chassis.arcade(leftY, rightX, true);
		
		/* Maybe change auton value, and display current autonomous on the controller */
		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) autonIndex--;
		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) autonIndex++;
		controllerPrintAuto();

		/* Calibrate the IMU and chassis when UP is pressed */
		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
			controller.print(2,0,"Calibrating");
			chassis.calibrate();
		}

		/* Run the currently selected autonomous (or skills) when B is pressed */
		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){
			#if SKILLS_ON_DOWN
				skills();
			#else
				autonomous();
			#endif
		}

		const int n = 10;
		const double kR = 1.0095;

		const double r1 = imu1.get_rotation();

		const double rotationDelta = r1 - oldR1;
		oldR1 = r1;

		corrected += rotationDelta * kR;

		emah = (emah * (n - 1) + r1) / n;


		if(counter%5 == 0) std::cout << "Rotation: " << r1 << " \tCorrected: " << corrected << "\tDelta Rotation: " << rotationDelta << "\n";
		counter++;

        pros::delay(20);
    }
}
