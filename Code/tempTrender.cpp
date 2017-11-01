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
	TH1F *h1 = new TH1F("h1","x distr", 100, 0, 400);
	Int_t dayCount = 12;
	Int_t daysWeek = 7;
	Int_t year, sYear = 0;
	Int_t month, sMonth = 0;
	Int_t day, sDay = 0;
	Int_t id;
	Double_t temp;
	Double_t temp_urban;
	bool foundSpring = false;
	tempVec.clear();
	cout << "Reading file " << dataFile << " ...\n";
	ifstream file(dataFile.c_str()); //Open file
	string line;
	//Loop for reading file
	while(file.good())
	{
		//Iterate till next year if spring found
		if(foundSpring == true)
		{
			dayCount = 0;
			foundSpring = false;
			Int_t nextYear = year+1;
			while(nextYear != year)
			{
				if(getline(file,line, '\n'))
				{
					stringstream ssNextYear(line);
					ssNextYear >> year >> month >> day >> temp >> temp_urban >> id;
				}
				else
					break;
			}
		}
		//Find first day of spring each year
		if(foundSpring == false)
			for(Int_t i=0; i < daysWeek; i++)
			{
				Double_t tmp;
				getline(file,line, '\n');
				stringstream ss(line);
				if(ss >> year >> month >> day >> temp >> temp_urban >> id) //check output can is eligible
				{
					dayCount++;
					if(id==1)//Take data from Uppsala
					{
						//dayCount>=46 represent 15 feb (minimum date for spring), month<8 remove missing data (otherwise autumn is classified as spring)
						if(temp_urban >= 0 && temp_urban <= 10 && dayCount >= 46 && month < 8) //Check if temp fulfill definition of spring
						{
							if(i==0){
								sYear=year; sMonth=month; sDay=day;
							}
							if(i == daysWeek-1) //Save temp of first day
							{
								foundSpring = true;
								tempVec.push_back(dayCount - (daysWeek+1)); //(daysWeek+1), dayCount incremented by 1 previously
								h1->Fill(dayCount - (daysWeek+1));
								//Print date of spring
								cout << "Spring found:\t" << sYear << "\t" << sMonth << "\t" << sDay << "\t" << endl;
							}
						}
						else //If temperature is not in interval, start new iteration
							break;
					}
				}
			}
	}
	file.close();
	h1->Draw();
}

