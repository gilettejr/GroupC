
//necessary libraries included

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//standard namespace

using namespace std;

//function, which will be utilised as member function in class
//takes a month and a day as input

void tempreal(int inday, int inmonth)

{

//opens necessary infile for streaming

ifstream myfile ("/home/courseuser/Project/Project/datasets/uppsala_tm_1722-2013.dat");

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

ofstream ofile("templist.dat");

//loop to pick out data for inputted month and day, for every year


for (int i=0;i<vtemps.size();i++) {
	
	if ((vday[i] == inday&& vmonth[i]==inmonth))
		ofile<<vtemps[i]<<endl;
	}
	
//output file closed
	
	ofile.close();
	
//this file now used as input file
	
	ifstream ifile ("templist.dat");
//vector vtemp filled with values to fill the graph
	double ftemp;
	
	while (ifile >> ftemp) {
		
		vhist.push_back(ftemp);
		
	}
	
	//cout<<vhist[23];//simple testing output
	
TH1I* hist = new TH1I("temperature", "Temperature;Temperature [#circC];Entries", 300, -20, 40);
hist->SetFillColor(kRed + 1);
hist->Fill(-3.2);
double mean = hist->GetMean();
double stdev = hist->GetRMS();
TCanvas* can = new TCanvas();
hist->Draw();
		
		




}
int main()

{
	
	tempreal(29, 4);
	
}










