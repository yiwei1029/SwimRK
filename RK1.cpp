#include"RK1.h"
#include<cmath>
#include<iostream>
using namespace std;
double f_float_ratio(double y_integral, double h, double theta) {
	double ratio_under_water = 1 - y_integral/ (h * sin(theta));
	return min(max(ratio_under_water, 0.5), 1.0);
}
double cal_force(double f_hand, double f_leg, double w_hand, double w_leg, 
	double T, double t, double h) {
	int period_deltas = (int)(T / h);
	int time_deltas = (int)(t / h);
	int remain_deltas = time_deltas % period_deltas;
	cout << remain_deltas << endl;
	if (remain_deltas < (int)(period_deltas / 4)) {
		return f_hand * sin(w_hand * remain_deltas * h);
	}
	else if(remain_deltas < (int)(period_deltas / 2)){
		return 0.0;
	}
	else if (remain_deltas < (int)(3 * period_deltas / 4)) {
		return f_leg * sin(w_leg * sin(remain_deltas -
			(int)(period_deltas / 2)) * h);
	}
	else {
		return 0.0;
	}
}
double integral_trap(vector<double> x, vector<double> t) {
	double sum = 0.0;
	for (size_t i = 0; i < x.size()-1; i++) {
		double height = t.at(1) - t.at(0);
		double temp = (x.at(i) + x.at(i + 1)) * height / 2;
		sum += temp;
	}
	return sum;
}
double* f(double x, double y, double t, double h, double y_integral,double* args) {
	double m = args[0];
	double k = args[1];
	double rho = args[2];
	double g = args[3];
	double V_0 = args[4];
	double height = args[5];
	double theta = args[6];
	double f_hand_x = args[7];
	double f_hand_y = args[8];
	double f_leg_x = args[9];
	double f_leg_y = args[10];
	double w_hand = args[11];
	double w_leg = args[12];
	double T = args[13];
	double f_x = cal_force(f_hand_x, f_leg_x, w_hand, w_leg, T, t, h);
	double f_y = cal_force(f_hand_y, f_leg_y,w_hand,w_leg, T, t,h);
	double dxdt = 1 / m * (f_x - k * x * sqrt(pow(x, 2) + pow(y, 2)));
	double dydt = 1/m*(
		f_y
		+rho*g*f_float_ratio(y_integral,height,theta)
		-m*g
		-k*abs(y)* sqrt(pow(x, 2) + pow(y, 2))
		);
	double diff[2] = { dxdt, dydt };
	return diff;
}


double* rk_step(double x, double y, double t, double h, double args[], vector<double> y_values, vector<double> t_values) {
	double y_integral = integral_trap(y_values, t_values);
	auto k1 = f(x, y,t, h, y_integral,args);
	auto k2 = f(x + h / 2 * k1[0], y + h / 2 * k1[1],t+h/2,h, y_integral, args);
	auto k3 = f(x + h / 2 * k2[0], y + h / 2 * k2[1],t+h/2,h, y_integral, args);
	auto k4 = f(x + h * k3[0], y + h * k3[1],t+h, h, y_integral, args);
	double x_y_next[2] = { 
		x + h / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]),
		y + h / 6 * (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) 
	};
	return x_y_next;

};