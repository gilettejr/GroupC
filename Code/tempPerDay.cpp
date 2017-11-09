// function tempPerDay()
//-----------------------
#include <fstream>
#include <vector>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
using namespace std;

void tempPerDay() {
	int year;
	int month;
	int day;
	float obsT;
	float corrT;
	int location;

	ifstream datafile("uppsala_tm_1722-2013.dat");
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



