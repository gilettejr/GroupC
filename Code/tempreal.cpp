
//necessary libraries included

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

//standard namespace

using namespace std;

//function, which will be utilised as member function in class
//takes a month and a day as input

void tempreal(int inday, int inmonth)

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
ofstream outfile("templist3.dat");
ofstream oufile("templist2.dat");
ofstream ofile("templist.dat");

//loop to pick out data for inputted month and day, for every year


for (int i=0;i<30000;i++) {
	
	if ((vday[i] == inday&& vmonth[i]==inmonth && vid[i]==1))
		ofile<<vtemps[i]<<endl;
	}
	
for (int a=30000;a<60000;a++) {
	
	if ((vday[a] == inday&& vmonth[a]==inmonth && vid[a]==1))
		oufile<<vtemps[a]<<endl;
	}

for  (int b=60000; b<vtemps.size();b++) 

if ((vday[b] == inday&& vmonth[b]==inmonth && vid[b]==1))
		outfile<<vtemps[b]<<endl;
	
	
//output file closed
	
	ofile.close();
	oufile.close();
	outfile.close();
	
//this file now used as input file
	
	ifstream ifile ("templist.dat");
	
//vector vtemp filled with values to fill the graph
	double ftemp;
	
	while (ifile >> ftemp) {
		
		vhist.push_back(ftemp);
		
	}
	
	ifstream infile ("templist2.dat");
	
//vector vtemp filled with values to fill the graph
	double ftemp2;
	
	while (infile >> ftemp2) {
		
		vhist2.push_back(ftemp2);
		
	}
	
	ifstream innfile ("templist3.dat");
	
//vector vtemp filled with values to fill the graph
	double ftemp3;
	
	while (innfile >> ftemp3) {
		
		vhist3.push_back(ftemp3);
	}
	
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
		
		




}
int main()

{
	
	tempreal(29, 4);
	
}










