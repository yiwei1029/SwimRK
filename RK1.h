
#pragma once
#include<vector>
#include <stdexcept>
using namespace std;
double* f(double x, double y, double t,double* args);
double cal_force(double f_hand_x, double f_hand_y, double w_hand_x, double w_hand_y,
	double T, double t);
double integral_trap(vector<double> x, vector<double> t);
double* rk_step(double x, double y, double t,  double h, double args[], vector<double> y_values, vector<double> t_values);
template<typename T>
vector<T> slice(const vector<T>& vec, size_t start, size_t end) {
	// Check if indices are within the bounds
	if (start > end || start >= vec.size() || end > vec.size()) {
		throw out_of_range("Invalid slice indices");
	}

	// Create a new vector for the slice
	return vector<T>(vec.begin() + start, vec.begin() + end);
}
