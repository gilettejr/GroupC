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


for (int i=0;i<vtemps.size();i++) {
	
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
for(int k=0;k<vhist.size();k++) {
hist->Fill(vhist[k]);
}
double mean = hist->GetMean();
double stdev = hist->GetRMS();
TCanvas* can = new TCanvas();
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
