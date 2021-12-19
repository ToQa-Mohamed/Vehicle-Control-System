/*
 ============================================================================
 Name        : miniproject-1.c
 Author      : toka mohamed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1

enum state {
	off = 0, on = 1
};
enum state engine = off;
enum state AC = off;
enum state engine_temp_controller = off;

typedef struct vehicle {
	char traffic_light;
	float room_temp;
	float engine_temp;
	float speed;
} vehicle;
vehicle v;

void req1(char *x) {   //Ask the user to turn on, turn off or quit the system
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	scanf(" %c", x);
	if (*x == 'a')
		printf("Turn on the vehicle engine\n");
	else if (*x == 'b')
		printf("Turn off the vehicle engine\n");
	else if (*x == 'c')
		printf("Quit the system\n");
}

void set_menu(char *y) { //choose from sensors set menu
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER==1
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	scanf(" %c", y);
}

void display(void) { //display the current vehicle state

	if (v.speed == 30) {  // special case if speed is 30
		AC = on;
		v.room_temp = (v.room_temp * (1.25)) + 1;
#if WITH_ENGINE_TEMP_CONTROLLER==1
		engine_temp_controller = on;
		v.engine_temp = (v.engine_temp * (1.25)) + 1;
#endif
	}

	if (engine == on)
		printf("Engine is on\n");
	else
		printf("Engine is off\n");
	if (AC == on)
		printf("AC is on\n");
	else
		printf("AC is off\n");
	printf("vehicle speed: %f km/hr \n", v.speed);
	printf("Room temperature: %f C \n", v.room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER==1
	if (engine_temp_controller == off)
		printf("engine temperature controller is off\n");
	else
		printf("engine temperature controller is on\n");
	printf("engine temperature: %f C \n", v.engine_temp);
#endif
}

void trafficlight(void) { //speed value based on traffic light
	printf("Enter the required color:\n");
	scanf(" %c", &v.traffic_light);
	if (v.traffic_light == 'G' || v.traffic_light == 'g')
		v.speed = 100;
	else if (v.traffic_light == 'O' || v.traffic_light == 'o')
		v.speed = 30;
	else if (v.traffic_light == 'R' || v.traffic_light == 'r')
		v.speed = 0;
	display();
}
void roomtemp(void) {  //AC state and room temperature based on the current room temperature
	printf("Enter the room temperature:\n");
	scanf(" %f", &v.room_temp);
	if (v.room_temp < 10) {
		AC = on;
		v.room_temp = 20;
	} else if (v.room_temp > 30) {
		AC = on;
		v.room_temp = 20;
	} else
		AC = off;
	display();
}
#if WITH_ENGINE_TEMP_CONTROLLER==1
void enginetemp(void) {//engine controller state and engine temperature based on the current engine temperature
	printf("Enter the engine temperature:\n");
	scanf(" %f", &v.engine_temp);
	if (v.engine_temp < 100) {
		engine_temp_controller = on;
		v.engine_temp = 125;
	} else if (v.engine_temp > 150) {
		engine_temp_controller = on;
		v.engine_temp = 125;
	} else
		engine_temp_controller = off;
	display();
}
#endif

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char choice; //to choose from turn on the engine/turn off the engine/quit the system
	char set; //to choose from sensors set menu

	//initialization
	v.traffic_light = 'G';
	v.room_temp = 35;
	v.engine_temp = 90;
	v.speed = 100;

	while (1) {
		req1(&choice);             //select from the menu
		while (choice == 'b') {    //if the user choose to turn off the engine
			engine = off;          //turn off the engine
			req1(&choice);         //select from the menu again
		}                          //while he/she chooses to turn off the engine he/she will select again
		if (choice == 'c') {       //if the user chooses to quit the system
			return 0;              //terminate the main function by return 0
		}
		if (choice == 'a') {       //if the user chooses to turn on the engine
			engine = on;           //turn on the engine
			while (engine == on) { //while the engine is on the set menu must be always displayed
				set_menu(&set);    //display the sensors set menu and select from it
				if (set == 'a') {  //if the user selected to turn off the engine
					engine = off;  //turn off the engine
					break;         //display the main menu again
				}
				if (set == 'b') {  //if the user selected the traffic light color
					trafficlight();//the function that change the speed based on traffic light color
				}
				if (set == 'c') { //if the user selected the room temperature
					roomtemp();   //the function that turn ac on/off and adjust the temperature
				}
#if WITH_ENGINE_TEMP_CONTROLLER==1
				if (set == 'd') { //if the user selected the engine temperature
					enginetemp(); //the function that turn engine temp controller on/off and adjust it's temp
				}
#endif
			}
		}
	}
	return 0;
}
