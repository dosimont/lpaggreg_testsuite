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
	//Input: "ID, Nodes, Tree, Random Type, Parameter Type, Parameter, Trace"
	//Write name fields in the output file (first line)
	output << "ID, NODES, LEAVES, TREE, TYPE, PARAM, INST1, INST2, INST3, TEMP1, TEMP2, TEMP3" << endl;

	//Read each line of input file
    for(; loop != CSVIterator(); ++loop)
    {

    	int number = atoi((*loop)[1].c_str())+1;
    	int tree = atoi((*loop)[2].c_str());
    	float parameter = atof((*loop)[5].c_str());
    	//Vector for storing trace elements
    	vector<NodeLPAggreg*>elements;
    	vector<NodeLPAggreg*>leaves;


    	NodeLPAggreg* root=new NodeLPAggreg(0,0);
    	elements.push_back(root);

    	if (tree==0)
			for (int i=1; i<number; i++){
				int father=min((int)((double)(rand())/(double)(RAND_MAX)*((double)elements.size()-1)),(int)elements.size()-1);
				elements.push_back(new NodeLPAggreg(i,0));
				elements[father]->addChild(elements[elements.size()-1]);
			}
    	else
    		for (int i=1, j=0; i<number; i++){
    			elements.push_back(new NodeLPAggreg(i,0));
    			elements[j]->addChild(elements[elements.size()-1]);
    			if (i%tree==0)
    				j++;
    		}



    	//LPAggreg Scalar algorithm is called to process the data
    	NodeLPAggreg * algo=root;

    	for (unsigned int i=0; i< elements.size(); i++){
    		if (!elements[i]->hasChild())
    			leaves.push_back(elements[i]);
    	}

    	for (unsigned int i=0; i< leaves.size(); i++){
    		leaves[i]->setValue(atoi((*loop)[i+6].c_str()));
    	}

    	//Init -> compute qualities
    	algo->init(false);

    	//getParts -> compute best cuts and best parts
    	//vector<int>* parts =
    	algo->getAggregation(parameter);

    	//Get and write in the ouput file time duration for each process
    	output << (*loop)[0] << ", "<<  elements.size() << ", "<<  leaves.size() << ","<< (*loop)[2] <<","<< (*loop)[3] <<","<<(*loop)[4] <<", "<< algo->getQualityCount() <<", "<< algo->getBestCutCount() <<", "<< algo->getBestPartitionCount() <<", "<< algo->getQualityDuration() <<", " << algo->getBestCutDuration()<<", "<<algo->getBestPartitionDuration()<< endl;
    	//cout<<"done"<<endl;
    	delete algo;
    }


	return 0;
}
