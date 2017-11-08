#include <iostream>
#include <fstream>
#include <vector>
#include <TH1.h>
//~ #include <TStyle.h>
//~ #include <TMath.h>
#include <TCanvas.h>

using namespace std;
int year;
int month;
int day;
float obsT;
float corrT;
int location;

void tempPerDay() {

	ifstream datafile("../datasets/uppsala_tm_1722-2013.dat");
	vector<int> vday;
	vector<int> vmonth;
	vector<int> vyear;
	vector<float> vtemp;
	vector<int> vloc;
	
	while (datafile >> year >> month >> day >> obsT >> corrT >> location) {
		
		if ((month == 2 && day == 29)) {
			continue;
		}
		if (year == 1722){
			continue;
		}
		
		vyear.push_back(year);
		vmonth.push_back(month);
		vday.push_back(day);
		vtemp.push_back(corrT);
		vloc.push_back(location);
	}
	
	int daycounter = 0;
	int yr_it = 0;


	TH1D* tempHist = new TH1D("tempHist", "Temperature of every day of the year",365,0,365);

	vector<float> sumtempvec;
	for (int p=0; p<365;p++){
		sumtempvec.push_back(0);
	}
 
	for (UInt_t k=0; k < vyear.size(); k++){
	//-------------------------------
		//~ day = vday.at(k);
		//~ month = vmonth.at(k);
		//~ year = vyear.at(k);
		//~ corrT = vtemp.at(k);
		//~ location = vloc.at(k);
	//---------------------------------
		
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
		
		//~ cout << vyear.at(k) << "  " << vmonth.at(k) << "  " << vday.at(k) << "  " <<"  "<< k << "  " << daycounter <<endl;
		sumtempvec.at(daycounter-1)=sumtempvec.at(daycounter-1) + vtemp.at(k);
		
		//if the daycounter has reached 365, it's a new year and the daycounter must be reset
		if (daycounter == 365){
			daycounter = 0;
			yr_it = yr_it +1;
		}
	}
	//~ double sd=0; 	//will store standard deviation
	
	for (UInt_t q=0;q<sumtempvec.size();q++){
		sumtempvec.at(q) = sumtempvec.at(q)/(yr_it);
		//~ cout << q << "  " << sumtempvec.at(q) << endl;
	}

	for (int bin = 1; bin <= tempHist->GetNbinsX(); ++bin){
		tempHist->SetBinContent(bin,sumtempvec[bin-1]);
		//~ tempHist->SetBinError(bin, /standard deviation/ );
	}
	
	TCanvas *c1 = new TCanvas("c1","Mean temperature for each day of the year", 900,600);
	
	tempHist->Draw();
	c1->SaveAs("TempPerDay.jpg");
	
}
