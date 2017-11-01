#include "tempTrender.h"


tempTrender::tempTrender(string filePath) {
	setFilePath(filePath);
	//cout << "The user supplied " << getFilePath() << " as the path to the data file." << endl;
}

void tempTrender::aveSpringArrive(){
	
}

//Function for reading temperature values to vector temp_vec
void tempTrender::readfile(string dataFile, vector<double> & temp_vec){
	temp_vec.clear();
	cout << "Reading file " << dataFile << " ...\n";
	Int_t line = -1; // Counter
	Int_t year;
	Int_t month;
	Int_t day;
	Int_t id;
	Double_t temp = 0;
	Double_t temp_urban = 0;
	string quality;
	ifstream file(dataFile.c_str());
	//Loop for reading file
	while(file >> year >> month >> day >> temp >> temp_urban >> id)
	{
		line++;
		temp_vec.push_back(temp);
		cout << temp_vec[line] << endl;
		//ss >> year >> month >> day >> temp >> temp_urban >> id;
	}
	file.close();
}

