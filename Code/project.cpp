#include "tempTrender.h"


//void project();

void project() {
	string pathToFile = "../datasets/uppsala_tm_1722-2013.dat"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	t.springArrive(1); //Find average day of spring
	t.getSpring("2012"); //Get date of spring arrival for specific year
	t.tempOnDay(23, 8); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
	//t.aveSpringArrive();
}

