/*
 * LPAggregScalarTrace.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#include <argp.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;


int main(int argc, const char* argv[]){

	/*Parameter list:
	 *
	 * argv[1] = trace element number
	 * argv[2] = line number
	 * argv[3] = output file
	 *
	 */

	//init random seed
	srand(time(NULL));

	//trace element number
	int elements = atoi(argv[1]);

	//line number
	int rows = atoi(argv[2]);

	//Open ouput files
	std::ofstream output(argv[3]);

	//Generating file header
	//output << "Parameter, Trace" << endl;

	//Generating a row
	for (int i=0; i < rows; i++){
		//Generating parameter (0<=p<=1, uniform distribution) TODO improve;
		double p = (double)rand()/(double)RAND_MAX;
		output << p;
		for (int j=0; j < elements; j++){
			int n =rand();
			output << ", "<< n;
		}
		output << endl;
	}
	return 0;
}
