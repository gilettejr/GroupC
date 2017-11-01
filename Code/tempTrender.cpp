#include "tempTrender.h"


tempTrender::tempTrender(string filePath) {
	setFilePath(filePath);
	//cout << "The user supplied " << getFilePath() << " as the path to the data file." << endl;
}

//Determine at what date the average temperature is above 0 and below 10
void tempTrender::aveSpringArrive(){
	
}

//Function for reading temperature values to vector temp_vec
void tempTrender::readfile(string dataFile, vector<double> & tempVec){
	Int_t row = -1; // Counter
	Int_t year;
	Int_t month;
	Int_t day;
	Int_t id;
	Double_t temp = 0;
	Double_t temp_urban = 0;
	tempVec.clear();
	cout << "Reading file " << dataFile << " ...\n";
	ifstream file(dataFile.c_str());
	string line;
	//Loop for reading file
	while(getline(file,line, '\n'))
	{
		stringstream ss(line);
		row++;
		if(ss >> year >> month >> day >> temp >> temp_urban >> id)
		{
			tempVec.push_back(temp);
			cout << tempVec[row] << endl;
		}
	}
	file.close();
}

