#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void tempreal(int inday, int inmonth)

{

ifstream myfile ("/home/courseuser/Project/Project/datasets/uppsala_tm_1722-2013.dat");

double year, month, day, untemp, temp, id;
vector<double> vtemps;
vector<int> vyear;
vector<int> vmonth;
vector<int> vday;
vector<int> vid;
vector<double> vhist;


if(myfile) {
	

while (myfile >> year >> month >> day >> untemp >> temp >> id) {
	
	vyear.push_back(year);
	vmonth.push_back(month);
	vday.push_back(day);
	vtemps.push_back(temp);
	vid.push_back(id);
	
	
	
	
}

}

myfile.close();

ofstream ofile("templist.dat");




for (int i=0;i<vtemps.size();i++) {
	
	if ((vday[i] == inday&& vmonth[i]==inmonth))
		ofile<<vtemps[i]<<endl;
	}
	
	ofile.close();
	
	ifstream ifile ("templist.dat");
	
	double ftemp;
	
	while (ifile >> ftemp) {
		
		vhist.push_back(ftemp);
		
	}
	
	cout<<vhist[2];
		
		

}
int main()

{
	
	tempreal(29, 4);
	
}










