/* Noah Klein */

#include "include.hpp"
#include "robotFunctions.hpp"
#include "main.h"


void initialize() {
	chassis.calibrate();
}


void disabled() {}


void competition_initialize() {}


void autonomous() {}


void opcontrol() {
    while (true) {
		/* Get position of analog sticks */
		const int8_t leftX = controller.get_analog(ANALOG_LEFT_X);
		const int8_t leftY = controller.get_analog(ANALOG_LEFT_Y);
		const int8_t rightX = controller.get_analog(ANALOG_RIGHT_X);
		const int8_t rightY = controller.get_analog(ANALOG_RIGHT_Y);

        /* Move the robot */
        chassis.arcade(leftY, leftX);
		
		/* Maybe change auton value, and display current autonomous on the controller */
		if(controller.get_digital_new_press(DIGITAL_LEFT)) autonIndex--;
		if(controller.get_digital_new_press(DIGITAL_RIGHT)) autonIndex++;
		//controllerPrintAuto();

		/* Calibrate the IMU and chassis when UP is pressed */
		if(controller.get_digital_new_press(DIGITAL_UP)){
			controller.print(2,0,"Calibrating");
			chassis.calibrate();
		}

		/* Run the currently selected autonomous (or skills) when B is pressed */
		if(controller.get_digital_new_press(DIGITAL_DOWN)){
			#if SKILLS_ON_DOWN
				skills();
			#else
				autonomous();
			#endif
		}

        pros::delay(10);
    }
}
