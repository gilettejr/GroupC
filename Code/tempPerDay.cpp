#include <iostream>
#include <fstream>
#include <vector>

//~ #include <TF1.h>
//~ #include <TH1.h>
//~ #include <TStyle.h>
//~ #include <TMath.h>
//~ #include <TCanvas.h>

using namespace std;
int year;
int month;
int day;
float obsT;
float corrT;
int location;

int main() {

	ifstream datafile("uppsala_tm_1722-2013.dat");
	//int i = 0;
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
		
		//i=i+1;
	}


//TH1D* tempHist = new TH1D("tempHist", "Temperature of every day of the year",365,0,365);
//1D histogram of type double, (name, title, nBins, xMin, xMax)

	int d, m, y, l;
	float t;
	int daycounter=0;
 
	for (int k=0; k < vyear.size(); k++){
		d = vday.at(k);
		m = vmonth.at(k);
		y = vyear.at(k);
		t = vtemp.at(k);
		l = vloc.at(k);
		
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
		
		cout << y << "  " << m << "  " << d << "  " <<"  "<< k << "  " << daycounter <<endl;
		
		//if the daycounter has reached 365, it's a new year and the daycounter must be reset
		if (daycounter == 365){
			daycounter = 0;
		}
	}


//tempHist->Draw();
}

/*
Left to do:
adapt to ROOT
exclude data values from location != 1
means -> fill histogram
*/
