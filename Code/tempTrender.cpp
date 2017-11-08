#include "tempTrender.h"


tempTrender::tempTrender(string filePath) {
	setFilePath(filePath);
}


//Determine at what date the average temperature is above 0 and below 10
//Function for reading temperature values to vector temp_vec
//Only work for "uppsala_tm_1722_2013.dat" file
void tempTrender::springArrive(int dataset){
	//Check input
	if(dataset < 1 || dataset > 6)
	{
		cout << "Incorrect call of springArrive\n";
		exit(1);
	}
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
	//Histograms
	TH1I *hDays = new TH1I("h1","Spring hist;Day;Entries", 365, 1, 365); //Histogram of days
	TH1D *hTemp = new TH1D("Entry", "Temperature on first day of spring;Temperature[#circC];Entries", 10, 0, 10); //Histogram of temps
	//Variables for reading and storing data
	Int_t dayCount = 12; //Starting point in Uppsala data set
	Int_t daysWeek = 7;
	Int_t year, sYear = 0;
	Int_t month, sMonth = 0;
	Int_t day, sDay = 0;
	Int_t id;
	Double_t temp, temp_urban, sTemp = 0;
	bool foundSpring = false;
	//**************************************
	//Read file "dataFile", write file "found_spring_date.dat"
	string dataFile = getFilePath();
	cout << "Reading file " << dataFile << " ...\n";
	ifstream file(dataFile.c_str()); //Open file
	ofstream springDate("found_spring_date.dat");
	springDate << "YYYY\t" << "MM\t" << "D\t" << "\t-\t" << "Temp(C)" << endl;
	springDate << "============================" << endl;
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
					if(id==dataset)//Take data from dataset
					{
						//dayCount>=46 represent 15 feb (minimum date for spring), month<8 remove missing data (otherwise autumn is classified as spring)
						if(temp_urban >= 0 && temp_urban <= 10 && dayCount >= 46 && month < 8) //Check if temp fulfill definition of spring
						{
							if(i==0)
							{
								sYear=year; sMonth=month; sDay=day;
								sTemp=temp_urban;
							}
							if(i == daysWeek-1) //Save temp of first day
							{
								foundSpring = true;
								hDays->Fill(dayCount - (daysWeek+1)); //(daysWeek+1), +1 because dayCount incremented by 1 previously
								hTemp->Fill(sTemp);
								//Print date of spring
								cout << "Spring found:\t" << sYear << "\t" << sMonth << "\t" << sDay << "\t" << sTemp << endl;
								springDate << sYear << "\t" << sMonth << "\t" << sDay << "\t-\t" << sTemp << endl;
							}
						}
						else //If temperature is not in interval, start new iteration
							break;
					}
				}
			}
	}
	springDate.close();
	file.close();
	//Draw extracted data
	TCanvas* can = new TCanvas("canSpringDay", "Spring day", 900, 600);
	hDays->SetFillColor(kRed +1);
	hDays->SetMinimum(0);
	hDays->Draw();
	TCanvas* can2 = new TCanvas("canSpringDayTemp", "Temperature on first spring day", 900, 600);
	hTemp->SetFillColor(kBlue+1);
	hTemp->SetMinimum(0);
	hTemp->Draw();
	//Define and fit exponential function to temperature histogram
	TF1* fitExp = new TF1("Exponential", "[0]*exp(-[1]*x)", 0, 10);
	fitExp->SetParameters(0,100);
	fitExp->SetParameters(1,1);
	hTemp->Fit(fitExp);
	//Save figures
	can->SaveAs("springArrive_dayHist.jpg");
	can2->SaveAs("springArrive_tempHist.jpg");
}

