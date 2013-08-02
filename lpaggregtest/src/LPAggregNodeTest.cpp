/*
 * LPAggregScalarTest.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */

#include <argp.h>
#include <cstdlib>
#include <sys/time.h>
#include <NodeLPAggreg.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>
#include "CSVIterator.h"

using namespace std;


int main(int argc, const char* argv[]){

	/*Parameter list:
	 *
	 * argv[1] = input file
	 * argv[2] = output file
	 *
	 */
	srand(time(NULL));

	//Open input and ouput files
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);

	//Iterator for parsing csv file. ',' is used as separator between each field.
	CSVIterator loop(input);

	//Skip the first line (name fields)
	loop++;

	//Write name fields in the output file (first line)
	output << "ID, SIZE, TYPE, PARAM, INST1, INST2, INST3, TEMP1, TEMP2, TEMP3" << endl;

	//Read each line of input file
    for(; loop != CSVIterator(); ++loop)
    {

    	//Gain/loss parameter is the first field
    	float parameter = atof((*loop)[3].c_str());

    	//Vector for storing trace elements
    	vector<NodeLPAggreg*>elements;
    	vector<NodeLPAggreg*>orphans;
    	vector<NodeLPAggreg*>nonorphans;
    	//Store input file line elements in the vector
    	for (unsigned int i = 4; i<(*loop).size(); i++){
    		elements.push_back(new NodeLPAggreg(i-4,atof((*loop)[i].c_str())));
    		if (i!=4)
    			orphans.push_back(elements[elements.size()-1]);
    		else
    			nonorphans.push_back(elements[elements.size()-1]);
    	}
    	for (unsigned int i=0; i< elements.size()-1; i++){
    		if (orphans.empty()){
    			break;
    		}
    		int number=1;
    		if (orphans.size()>1)
    			number= rand()%(orphans.size()-1)+1;
			for (vector<NodeLPAggreg*>::iterator it= orphans.begin(); it!= min(orphans.end(),orphans.begin()+number); it++){
				nonorphans.push_back(*it);
				elements[i]->addChild(*it);
			}
			vector<NodeLPAggreg*>::iterator it= orphans.begin();
				orphans.erase(it, it+number);
    	}
    	//LPAggreg Scalar algorithm is called to process the data
    	NodeLPAggreg * algo = elements[0];

    	//Init -> compute qualities
    	algo->init(false);

    	//getParts -> compute best cuts and best parts
    	vector<int>* parts = algo->getAggregation(parameter);

    	//Get and write in the ouput file time duration for each process
    	output << (*loop)[0] <<", "<<  parts->size() << ","<< (*loop)[1] <<","<< (*loop)[2] <<", "<< algo->getQualityCount() <<", "<< algo->getBestCutCount() <<", "<< algo->getBestPartitionCount() <<", "<< algo->getQualityDuration() <<", " << algo->getBestCutDuration()<<", "<<algo->getBestPartitionDuration()<< endl;
    	//cout<<"done"<<endl;
    	delete algo;
    }


	return 0;
}
