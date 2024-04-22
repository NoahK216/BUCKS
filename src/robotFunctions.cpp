/* Noah Klein */

#include "include.hpp"
#include "robotFunctions.hpp"


/* Print the currently selected auto, and some other information, to the controller */
void controllerPrintAuto(){
	controller.print(2, 0, "%s, %.2f            ", autos[autonIndex%AUTO_COUNT].autoName, imu.get_heading());
}
