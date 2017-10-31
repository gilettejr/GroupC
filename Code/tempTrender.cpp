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
	stringstream ss;
	Int_t line = -1; // Counter
	string date;
	string time;
	Double_t temp = 0;
	string quality;

	ifstream file(dataFile.c_str());
	Int_t eventNo = -1;
	//Loop for reading file
	while(getline(file, date))
	{
		line++;
		file >> date >> time >> temp >> quality;
	}
	file.close();
}

