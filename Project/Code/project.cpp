#include "tempTrender.h"
#include <string>

#include <iostream>

using namespace std;

void project();

void project() {
	string pathToFile = "~/Project/datasets/"; //Put the path to your data file here
	tempTrender t(pathToFile); //Instantiate your analysis object
	cout << t.getFilePath() << endl;
	
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	//t.hotCold();
	//t.tempPerYear(2050);
}
