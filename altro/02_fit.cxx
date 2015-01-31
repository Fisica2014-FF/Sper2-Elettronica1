#include <iostream>
#include <fstream>
#include <cmath>
#include "libstat.h"

using namespace std;

struct line
	{
		double q, m, sq, sm;
	};
	
int main (){
	int N = 11;
	double * x = new double [N];
	double * y = new double [N];
	
	for(int i = 0; i < N; i++){
		cin >> x[i];
		cin >> y[i];
	}

	
	line ret;
	ret.q = interp_a(N, x, y);
	ret.m = interp_b(N, x, y);
	ret.sq = interp_sigmaa(N, x, y);
	ret.sm = interp_sigmab(N, x, y);
		
	cout <<
		"# x medio = " << media(N, x) << ", Var(x) = " << scarto2(N, x) << endl <<
		"# y medio = " << media(N, y) << ", Var(y) = " << scarto2(N, y) << endl;
	
	cout << 
		"# Parametri retta:" <<
		"\n# m = " << ret.m << " +/- " << ret.sm << 
		"\n# q = " << ret.q << " +/- " << ret.sq <<
		"\n# cov(m, q) = " << cov_mq(N, x, y) << endl;	
		
	//RESIDUI
	for(int i=0; i<N; i++){
		cout << x[i] << "	" << y[i] - (x[i] * (ret.m) + (ret.q)) << endl;
	}
	
	return 0;
}
