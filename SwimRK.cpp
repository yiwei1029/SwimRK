// SwimRK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"RK1.h"
#include"utils.h"
#define M_PI 3.14159265358979323846
using namespace std;
int main()
{
	vector<double> t;
	for (int i = 0; i < 10000; i++) {
		t.push_back(i * 0.001);
	}
	vector<double> x = { 1 };
	vector<double> y = { 1 };
	cout << x.at(0) << endl;
	double args[14] = { 
		65,10,1000,10,0.06,1.7,M_PI/6,
		150,1000,150,1000,M_PI/3,2*M_PI/3,3
	};
	for (size_t i = 0; i < t.size() - 1; i++) {
		double* xynext = rk_step(
			x.at(i), y.at(i), t.at(i), 
			t.at(i + 1) - t.at(i), args, y, slice(t, 0, i + 1)
		);
		x.push_back(xynext[0]);
		y.push_back(xynext[1]);
		//cout << x.at(i) << "  ";

	}
	print_vec2file(y,
		"C:\\Users\\Administrator\\Documents\\python_projects\\pde_swim\\v_y_cpp.txt");
}
