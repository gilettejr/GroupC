#include "tempTrender.h"


//void project();

void project() {
	string pathToFile = "../datasets/smhi-opendata_Lund.csv"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	t.readfile(t.getFilePath(), t.getTempVec());
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
	//t.aveSpringArrive();
}

