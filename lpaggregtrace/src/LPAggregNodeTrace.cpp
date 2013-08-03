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
	 * argv[1] = id
	 * argv[2] = line number
	 * argv[3] = node number
	 * argv[4] = tree structure(int, 0=Aléatoire)
	 * argv[5] = random type ("I"/"A")
	 * argv[6] = param type ("0", "1", "A")
	 *
	 * argv[7] = output file
	 *
	 */

	//init random seed
	srand(time(NULL));

	//trace element number
	int elements = atoi(argv[3]);

	//line number
	int lines = atoi(argv[2]);

	//trace type
	bool randomTrace = (!strcmp(argv[5],"A"))?true:false;

	//param type
	int param = 0;
	if (!strcmp(argv[6],"A"))
		param=2;
	else if (!strcmp(argv[6],"1"))
		param=1;

	//Open ouput files
	std::ofstream output(argv[7]);

	//Generating file header
	//output << "ID, Nodes, Tree, Random Type, Parameter Type, Parameter, Trace" << endl;

	//Generating a row
	for (int i=0; i < lines; i++){
		//id
		output << argv[1];
		output << ", "<< argv[3];
		output << ", "<< argv[4];
		output << ", "<< argv[5];
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
