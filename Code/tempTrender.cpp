#include "tempTrender.h"


tempTrender::tempTrender(string filePath) {
	setFilePath(filePath);
}

//Determine at what date the average temperature is above 0 and below 10
void tempTrender::aveSpringArrive(){
	
}

//Function for reading temperature values to vector temp_vec
//Only work for "uppsala_tm_1722_2013.dat" file
void tempTrender::readfileSA(string dataFile, vector<double> & tempVec){
	TH1F *h1 = new TH1F("h1","x distr", 52, 0, 365);
	Int_t dayCount = 12;
	Int_t daysWeek = 7;
	Int_t year;
	Int_t month;
	Int_t day;
	Int_t id;
	Double_t temp = 0;
	Double_t temp_urban = 0;
	bool foundSpring = false;
	tempVec.clear();
	cout << "Reading file " << dataFile << " ...\n";
	ifstream file(dataFile.c_str()); //Open file
	string line;
	//Loop for reading file
	while(file.good())
	{
		//Find first day of spring each year
		for(Int_t day=0; day < daysWeek; day++)
		{
			Double_t tmp;
			getline(file,line, '\n');
			stringstream ss(line);
			if(ss >> year >> month >> day >> temp >> temp_urban >> id) //check output can is eligible
			{
				dayCount++; //Increment
				if(id==1 && temp_urban >= 0 && temp_urban <= 10) //Take data from Uppsala, check if temp is in allowed interval
				{
					if(day == 0) //Save first entry
						tmp = dayCount;
					if(day == daysWeek-1) //Save temp of first day
					{
						foundSpring = true;
						tempVec.push_back(tmp);
						h1->Fill(tmp);
					}

				}
				else //If temp is not in interval, start new iteration
					break;
			}
		}
	}
	cout << foundSpring << endl;
	file.close();
	h1->Draw();
}

