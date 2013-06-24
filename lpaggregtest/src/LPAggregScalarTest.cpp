/*
 * LPAggregScalarTest.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#include <argp.h>
#include <cstdlib>
#include <time.h>
#include <ScalarLPAggreg.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include "CSVIterator.h"

using namespace std;


int main(int argc, const char* argv[]){

	/*Parameter list:
	 *
	 * argv[1] = input file
	 * argv[2] = output file
	 *
	 */

	//Open input and ouput files
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	//Iterator for parsing csv file. ',' is used as separator between each field.
	CSVIterator loop(input);

	//Skip the first line (name fields)
	loop++;

	//Write name fields in the output file (first line)
	output << "elements, qualities, bestcuts, bestpartitions" << endl;

	//Read each line of input file
    for(; loop != CSVIterator(); ++loop)
    {

    	//Gain/loss parameter is the first field
    	float parameter = atof((*loop)[0].c_str());

    	//Vector for storing trace elements
    	vector<double>elements;

    	//Store input file line elements in the vector
    	for (unsigned int i = 1; i<(*loop).size(); i++){
    		elements.push_back(atof((*loop)[i].c_str()));
    	}

    	//LPAggreg Scalar algorithm is called to process the data
    	ScalarLPAggreg algo = ScalarLPAggreg(elements);

    	//Init -> compute qualities
    	algo.init(0);

    	//getParts -> compute best cuts and best parts
    	//TODO should we store or write aggregation result contained in "parts"?
    	vector<int>parts = algo.getParts(parameter);

    	//Get and write in the ouput file time duration for each process
    	//TODO time granularity is second. Is it enough?
    	output << parts.size() <<", "<< algo.getQualityDuration() <<", " << algo.getBestCutDuration()<<", "<<algo.getBestPartitionDuration()<< endl;
    }


	return 0;
}
