#include "tempTrender.h"


tempTrender::tempTrender(string filePath) {
	setFilePath(filePath);
}


//Determine at what date the average temperature is above 0 and below 10
//marking the beginning of spring acording to SMHI:s meterological definition
//Function writes found dates in file "found_spring_date.dat"
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
	hDays->Draw();
	TCanvas* can2 = new TCanvas("canSpringDayTemp", "Temperature on first spring day", 900, 600);
	hTemp->SetFillColor(kBlue+1);
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

//Get the date and temperature of the day spring started in year "year"
//If the supplied year is not found, a error message is given
void tempTrender::getSpring(string year){
	ifstream fp("found_spring_date.dat");
	string sYear, sMonth, sDay, sTemp, tmp;
	if(fp)
	{
		for(int i=0;i<2;i++) getline(fp,tmp);
		while(year.compare(sYear) != 0 && !fp.eof()){fp >> sYear >> sMonth >> sDay >> tmp >> sTemp;}
		if(year.compare(sYear) == 0)
			cout << "Spring in " << year << " arrived " << sDay << "/" 
				<< sMonth << " with a average temperature of " << sTemp << endl;
		else
			cout << "No data found for year " << year << endl;
		fp.close();
	}
	else
	{
		cout << "File " << "'found_spring_date.dat'" << " not found" << endl;
		exit(1);
	}
}

//void tempOnDay(int monthToCalculate, int dayToCalculate);
void tempTrender::tempOnDay(int inday, int inmonth)
{
if(inday>31)
cout << "Error, invalid day\n";
if(inmonth>12)
cout<<"Error, invalid month'n";
//opens necessary infile for streaming

ifstream myfile ("../datasets/uppsala_tm_1722-2013.dat");

//double variables declared for data in each column of original set

double year, month, day, untemp, temp, id;

//vectors created for holding each of these columns

vector<double> vtemps;
vector<int> vyear;
vector<int> vmonth;
vector<int> vday;
vector<int> vid;

//vector to fill the histogram

vector<double> vhist;
vector<double> vhist2;
vector<double> vhist3;

//conditional to prevent programming from continuing if instream fails

if(myfile) {

//vectors filled with appropriate column of data	

while (myfile >> year >> month >> day >> untemp >> temp >> id) {
	
	vyear.push_back(year);
	vmonth.push_back(month);
	vday.push_back(day);
	vtemps.push_back(temp);
	vid.push_back(id);
	
	
	
	
}

}

//input file closed

myfile.close();

//output file created
//ofstream outfile("templist3.dat");
//ofstream oufile("templist2.dat");
ofstream ofile("templist.dat");

//loop to pick out data for inputted month and day, for every year


for (UInt_t i=0;i<vtemps.size();i++) {
	
	if ((vday[i] == inday&& vmonth[i]==inmonth && vid[i]==1))
		ofile<<vtemps[i]<<endl;
	}
	
//for (int a=30000;a<60000;a++) {
	
	//if ((vday[a] == inday&& vmonth[a]==inmonth && vid[a]==1))
		//oufile<<vtemps[a]<<endl;
	//}

/*for  (int b=60000; b<vtemps.size();b++) 

if ((vday[b] == inday&& vmonth[b]==inmonth && vid[b]==1))
		outfile<<vtemps[b]<<endl;
		*/
	
	
//output file closed
	
	ofile.close();
	//oufile.close();
	//outfile.close();
	
//this file now used as input file
	
	ifstream ifile ("templist.dat");
	
//vector vtemp filled with values to fill the graph
	double ftemp;
	
	while (ifile >> ftemp) {
		
		vhist.push_back(ftemp);
		
	}
	
	//ifstream infile ("templist2.dat");
	
//vector vtemp filled with values to fill the graph
	/*double ftemp2;
	
	while (infile >> ftemp2) {
		
		vhist2.push_back(ftemp2);
		
	}
	
	ifstream innfile ("templist3.dat");
	
//vector vtemp filled with values to fill the graph
	double ftemp3;
	
	while (innfile >> ftemp3) {
		
		vhist3.push_back(ftemp3);
	}
	*/
	
	//cout<<vhist[23];//simple testing output
gStyle->SetOptStat(1111);
 gStyle->SetOptFit(1111);
TH1I* hist = new TH1I("day, month", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
hist->SetFillColor(kRed + 1);
for(UInt_t k=0;k<vhist.size();k++) {
hist->Fill(vhist[k]);
}
double mean = hist->GetMean();
double stdev = hist->GetRMS();
TCanvas* can = new TCanvas("tmp_canvas","Histogram of given day", 900,600);
hist->Draw();
can->SaveAs("one.jpg");
/*
gStyle->SetOptStat(1111);
 gStyle->SetOptFit(1111);
TH1I* hist2 = new TH1I("day, month", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
hist2->SetFillColor(kRed + 1);
for(int k=0;k<vhist2.size();k++) {
hist2->Fill(vhist2[k]);
}
double mean2 = hist2->GetMean();
double stdev2 = hist2->GetRMS();
TCanvas* can2 = new TCanvas();
hist2->Draw();
can2->SaveAs("two.jpg");

gStyle->SetOptStat(1111);
 gStyle->SetOptFit(1111);
TH1I* hist3 = new TH1I("day, month", "Temperature;Temperature[#circC];Entries", 300, -20, 40);
hist3->SetFillColor(kRed + 1);
for(int k=0;k<vhist3.size();k++) {
hist3->Fill(vhist3[k]);
}
double mean3 = hist3->GetMean();
double stdev3 = hist3->GetRMS();
TCanvas* can3 = new TCanvas();
hist3->Draw();
can3->SaveAs("three.jpg");
*/
}

void tempTrender::tempPerDay() {
	int year;
	int month;
	int day;
	float obsT;
	float corrT;
	int location;

	ifstream datafile("../datasets/uppsala_tm_1722-2013.dat");
	vector<int> vday;
	vector<int> vmonth;
	vector<int> vyear;
	vector<float> vtemp;
	vector<int> vloc;
	
	//reading the data from the file and putting each datatype in a separate vector
	while (datafile >> year >> month >> day >> obsT >> corrT >> location) {
		
		//excluding the 29th of february for leapyears
		if ((month == 2 && day == 29)) {
			continue;
		}
		//excluding the year 1722 where we don't have data for every day
		if (year == 1722){
			continue;
		}
		
		vyear.push_back(year);
		vmonth.push_back(month);
		vday.push_back(day);
		vtemp.push_back(corrT);
		vloc.push_back(location);
	}
	
	datafile.close();
	
	int daycounter = 0;
	int yr_it = 0;
	
	//creating a histogram
	TH1D* tempHist = new TH1D("tempHist", "Mean temperature for each day of the year;Day of the year;Temperature [#circC]",365,0,365);	
	
	//creating vectors which values will be put in the histogram
	vector<float> sumtempvec;
	vector<float> vStdDev;
	for (int p=0; p<365;p++){
		sumtempvec.push_back(0);
		vStdDev.push_back(0);
	}

	//loop for calculating the mean temperatures of each day
	for (UInt_t k=0; k < vyear.size(); k++){
		
		//if the location isn't Uppsala, update the daycounter but don't use the value
		if (vloc.at(k) != 1){
			daycounter = daycounter+1;
			goto golabel1;
		}
		
		//special case for the last date, otherwise vyear.at(k+1) is undefined (2014-01-01 is not part of the data)
		if (vyear.at(k) == 2013 && vmonth.at(k) == 12 && vday.at(k) == 31){
			daycounter = 365;
		}
		
		//if this year is not the same as the next iteration's year, the daycounter is 365
		else if (vyear.at(k) != vyear.at(k+1)){
			daycounter = 365;
		}
		
		//otherwise, if it's still the same year, the daycounter is that of the previous iteration + 1
		else if (vyear.at(k) == vyear.at(k+1)){
			daycounter = daycounter+1;
		}
		//put the sum of the temperatures of a day for every year in a vector
		sumtempvec.at(daycounter-1)=sumtempvec.at(daycounter-1) + vtemp.at(k);
		
		golabel1: //for excluding locations other than Uppsala
		
		//if the daycounter has reached 365, it's a new year and the daycounter must be reset
		if (daycounter == 365){
			daycounter = 0;
			yr_it = yr_it +1; //the number of years we've iterated over
		}
	}
	
	//calculating the mean temperatures for each day
	for (UInt_t q=0;q<sumtempvec.size();q++){
		sumtempvec.at(q) = sumtempvec.at(q)/(yr_it);
	}	
	
	
		
	//loop for calculating the standard deviation
	for (UInt_t k=0; k < vyear.size(); k++){
		
		//if the location isn't Uppsala, update the daycounter but exclude the temperature value
		if (vloc.at(k) != 1){
			daycounter = daycounter+1;
			goto golabel2;
		}
		
		//special case for the last date, otherwise vyear.at(k+1) is undefined (2014-01-01 is not part of the data)
		if (vyear.at(k) == 2013 && vmonth.at(k) == 12 && vday.at(k) == 31){
			daycounter = 365;
		}
		
		//if this year is not the same as the next iteration's year, the daycounter is 365
		else if (vyear.at(k) != vyear.at(k+1)){
			daycounter = 365;
		}
		
		//otherwise, if it's still the same year, the daycounter is that of the previous iteration + 1
		else if (vyear.at(k) == vyear.at(k+1)){
			daycounter = daycounter+1;
		}
		
		//put the difference between the temperature and the mean temperature squared in a vector
		vStdDev.at(daycounter-1) += (vtemp.at(k)-sumtempvec.at(daycounter-1))*(vtemp.at(k)-sumtempvec.at(daycounter-1));
				
		golabel2: //for excluding locations other than Uppsala
		
		//if the daycounter has reached 365, it's a new year and the daycounter must be reset
		if (daycounter == 365){
			daycounter = 0;
			yr_it = yr_it +1;  //the number of years we've iterated over
		}
	}
	
	//calculating the standard deviation for each day
	for (UInt_t q=0;q<vStdDev.size();q++){
		vStdDev.at(q) = TMath::Sqrt(vStdDev.at(q)/(yr_it-1));
	}
	
	
	
	//filling the histogram with values for the mean temperatures and the standard deviations
	for (int bin = 1; bin <= tempHist->GetNbinsX(); ++bin){
		tempHist->SetBinContent(bin,sumtempvec[bin-1]);
		tempHist->SetBinError(bin,vStdDev[bin-1]);
	}
	
	//for not displaying statistics on the histogram
	gStyle->SetOptStat(0);
	
	//creating a canvas for the histogram
	TCanvas *c1 = new TCanvas("c1","Mean temperature for each day of the year", 900,600);	
	
	tempHist->Draw();
	c1->SaveAs("tempPerDay.jpg");
}
