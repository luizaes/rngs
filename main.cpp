/* 
	Representação 1D de diferentes distribuições de probabilidade
*/

#include <bits/stdc++.h>
#include <boost/program_options.hpp>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "gnuplot-iostream/gnuplot-iostream.h"

using namespace std;

/* Funções que definem as distribuições */

// Logistic Map, r = 4.0 (Fister, 2015)
double logisticMap(double randomNum, double r) {
	randomNum = r * randomNum * (1 - randomNum);
	return randomNum;
}

// Circle Map, a = 0.5, b = 0.2 (Gandomi, 2013)
double circleMap(double randomNum, double a, double b) {
	randomNum = fmod(randomNum + b - a/(2*M_PI) * sin(2*M_PI*randomNum), 1.0);
	return randomNum;
}

// Gauss Map
double gaussMap(double randomNum) {
	if(randomNum == 0.0) {
		return 0.0;
	} else {
		return fmod((1/randomNum), 1.0);
	}
}

// Piecewise Map, p = 0.4 (Saxena, 2018)
double piecewiseMap(double randomNum, double p) {
	if(randomNum >= 0 && randomNum < p) {
		return randomNum/p;
	} else if(randomNum >= p && randomNum < 0.5) {
		return (randomNum-p)/(0.5-p);
	} else if(randomNum >= 0.5 && randomNum <= 1-p) {
		return (1-p-randomNum)/(0.5-p);
	} else if(randomNum >= 1-p && randomNum < 1) {
		return (1-randomNum)/p;
	}
}

// Sine Map, a = 4.0 (Saxena, 2018)
double sineMap(double randomNum, double a) {
	return (a/4.0) * sin(M_PI * randomNum);
}

// Singer Map, u = 1.07 (Kaveh, 2018)
double singerMap(double randomNum, double u) {
	return u*(7.86*randomNum - 23.31*pow(randomNum, 2) + 28.75*pow(randomNum, 3) - 13.302875*pow(randomNum, 4));
}

// Sinusoidal Map, a = 2.3 (Saxena, 2018)
double sinusoidalMap(double randomNum, double a) {
	return a*pow(randomNum, 2)*sin(M_PI*randomNum);
}

// Tent Map
double tentMap(double randomNum) {
	if(randomNum < 0.7) {
		return randomNum/0.7;
	} else if(randomNum >= 0.7) {
		return (10/3.0) * (1-randomNum);
	}
}

// Chebyshev Map, i = iteration number (Kaveh, 2018)
double chebyshevMap(double randomNum, int i) {
	return cos(i*acos(randomNum));
}

// Iteractive Map, a = 0.7 (Saxena, 2018)
double iteractiveMap(double randomNum, double a) {
	return sin((a*M_PI)/randomNum);
}


int main() {
	
	Gnuplot gp;
	gsl_rng *r;
	gsl_rng_env_setup();
	const gsl_rng_type * ti = gsl_rng_default;
	r = gsl_rng_alloc (ti);
    vector< pair<int, int> > graph;
	mt19937 rng;
    rng.seed(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> random2(0, 1);
    double last = random2(rng);
    int contador = 1;

    cout << "Which distribution you want to display?" << endl;
    cout << "1 - Uniform\n2 - Gaussian\n3 - Cauchy\n4 - Logistic\n5 - Circle\n6 - Gauss\n7 - Piecewise\n8 - Sine\n9 - Singer\n10 - Sinusoidal\n11 - Tent\n12 - Chebyshev\n13 - Iteractive\n";
    int distribution;

    cin >> distribution;
  
    gp << "set yrange [" << 0 << ":" << 100 << "]\nset xrange [0:100]\n";

    switch(distribution) {

    	// Uniform distribution
    	case 1:
    		{
    			int count[101] = {0};
    			uniform_int_distribution<int> random(0, 100);
	    		for(int i = 0; i < 2000; i++) {
	    			int y = random(rng);
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Uniform Distribution'\n";
	    		break;
    		}

    	// Gaussian distribution
    	case 2:
    		{
    			int count[101] = {0};
    			int y;
	    		for(int i = 0; i < 2000; i++) {
	    			// Média 50, desvio-padrão 15
	    			while(true) {
	    				y = gsl_ran_gaussian(r, 15.0) + 50;
	    				if(y >= 0 && y <= 100) {
	    					break;
	    				}
	    			}
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Gaussian Distribution'\n";
	    		break;
    		}

    	// Cauchy distribution
    	case 3:
    		{
    			int count[101] = {0};
    			int y;
    			for(int i = 0; i < 2000; i++) {

    				while(true) {
    					y = gsl_ran_cauchy(r, 10.0) + 50;
    					if(y >= 0 &&  y <= 100) {
    						break;
    					}
    				}
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Cauchy Distribution'\n";
    			break;
    		}

    	// Logistic map
    	case 4:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = logisticMap(last, 4.0);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Logistic Distribution'\n";
    			break;
    		}

    	// Circle map
    	case 5:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = circleMap(last, 0.5, 0.2);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Circle Distribution'\n";
    			break;
    		}

    	// Gauss map
    	case 6:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = gaussMap(last);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Gauss Distribution'\n";
    			break;
    		}

    	// Piecewise map
    	case 7:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = piecewiseMap(last, 0.4);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Piecewise Distribution'\n";
    			break;
    		}

    	// Sine map
    	case 8:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = sineMap(last, 4.0);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Sine Distribution'\n";
    			break;
    		}

    	// Singer map
    	case 9:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = singerMap(last, 1.07);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}
	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Singer Distribution'\n";
    			break;
    		}

    	// Sinusoidal map
    	case 10:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = sinusoidalMap(last, 2.3);
	    			int y = 100 * last;
	    			count[y]++;
	    		}
	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}

	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Sinusoidal Distribution'\n";
    			break;
    		}

    	// Tent map
    	case 11:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = tentMap(last);
	    			int y = 100 * last;
	    			count[y]++;
	    		}

	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}

	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Tent Distribution'\n";
    			break;
    		}
    	
    	// Chebyshev map
    	case 12:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = chebyshevMap(last, i+1);
	    			int y = (100 * (last+1))/2;
	    			count[y]++;
	    		}

	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}

	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Chebyshev Distribution'\n";
    			break;
    		}

    	// Iteractive map
    	case 13:
    		{
    			int count[101] = {0};
    			for(int i = 0; i < 2000; i++) {
	    			last = iteractiveMap(last, 0.7);
	    			int y = (100 * (last+1))/2;
	    			count[y]++;
	    		}

	    		for(int i = 0; i < 101; i++){
	    			graph.push_back(make_pair(i, count[i]));
	    		}

	    		gp << "plot '-' with lines pt 7 ps 1 lt rgb 'red' title 'Iteractive Distribution'\n";
    			break;
    		}
    }

    gp.send1d(graph);

    gsl_rng_free (r);

	return 0;
}
