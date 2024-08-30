
#pragma once
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
template<typename T>
void print_vec2file(const vector<T>& vec, string out) {
	ofstream of(out);
	if (!of) {
		cerr << "cannot open file" << endl;
	}
	for (T item : vec) {
		of << item << endl;
	}
	of.close();
	cout << "output finished" << endl;
}