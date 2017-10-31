#include <iostream>
#include "tempTrender.h"

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	setFilePath(filePath);
}

