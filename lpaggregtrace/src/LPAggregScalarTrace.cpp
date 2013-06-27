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
#include <string.h>
#include <math.h>
#include <time.h>

using namespace std;


int main(int argc, const char* argv[]){

	/*Parameter list:
	 *
	 * argv[1] = trace element number
	 * argv[2] = line number
	 * argv[3] = trace type ("I"/"A")
	 * argv[4] = param type ("0", "1", "A")
	 * argv[5] = id
	 * argv[6] = output file
	 *
	 */

	//init random seed
	srand(time(NULL));

	//trace element number
	int elements = atoi(argv[1]);

	//line number
	int rows = atoi(argv[2]);

	//trace type
	bool randomTrace = (!strcmp(argv[3],"A"))?true:false;

	//param type
	int param = 0;
	if (!strcmp(argv[4],"A"))
		param=2;
	else if (!strcmp(argv[4],"1"))
		param=1;

	//Open ouput files
	std::ofstream output(argv[6]);

	//Generating file header
	//output << "ID, Trace Type, Parameter Type, Parameter, Trace" << endl;

	//Generating a row
	for (int i=0; i < rows; i++){
		//id
		output << argv[5];
		//trace Type
		output << ", "<< argv[3];
		double p = param;
		//Parameter Type
		if (param==2){
			p = (double)rand()/(double)RAND_MAX;
			output << ", A";
		}else
			output << ", " << param;
		//Parameter
		output << ", "<< p;
		//Trace
		for (int j=0; j < elements; j++){
			int n =1;
			if (randomTrace)
				n =rand();
			output << ", "<< n;
		}
		output << endl;
	}
	return 0;
}
