#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()

{

ifstream myfile ("/home/courseuser/Project/Project/datasets/uppsala_tm_1722-2013.dat");

double year, month, day, untemp, temp, dummy;
vector<double> vtemps;

if(myfile) {
	

while (myfile >> year >> month >> day >> untemp >> temp >> dummy) {
	vtemps.push_back(temp);
}

}

myfile.close();

cout << vtemps.at(4);

}












