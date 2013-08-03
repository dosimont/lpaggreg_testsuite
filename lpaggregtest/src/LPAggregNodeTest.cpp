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
	output << "ID, NODES, LEAVES, TYPE, PARAM, INST1, INST2, INST3, TEMP1, TEMP2, TEMP3" << endl;

	//Read each line of input file
    for(; loop != CSVIterator(); ++loop)
    {

    	//Gain/loss parameter
    	float parameter = atof((*loop)[3].c_str());
    	int number = (*loop).size()-4;
    	//Vector for storing trace elements
    	vector<NodeLPAggreg*>elements;
    	vector<NodeLPAggreg*>leaves;
    	vector<NodeLPAggreg*>orphans;
    	vector<NodeLPAggreg*>nonorphans;

    	NodeLPAggreg* root=new NodeLPAggreg(0,0);
    	elements.push_back(root);

    	for (int i=0; i<number-1; i++){
    		int father=min((int)((double)(rand())/(double)(RAND_MAX)*((double)elements.size()-1)),(int)elements.size()-1);
    		elements.push_back(new NodeLPAggreg(i+1,0));
    		elements[father]->addChild(elements[elements.size()-1]);
    	}

    	//Store input file line elements in the vector

//    	for (unsigned int i = 4; i<(*loop).size(); i++){
//    		//elements.push_back(new NodeLPAggreg(i-4,atof((*loop)[i].c_str())));
//    		//orphans.push_back(elements[elements.size()-1]);
//    	}
//
//    	while (orphans.size()>1){
//    		int son= ((double)(rand())/(double)RAND_MAX)*((double)orphans.size());
//    		int father= ((double)(rand())/(double)RAND_MAX)*((double)elements.size());
//    		if (son<(int)orphans.size()&&father<(int)elements.size()&&(!orphans[son]->ownsNode(elements[father]))){
//    			elements[father]->addChild(orphans[son]);
//    			//elements.push_back(orphans[son]);
//    			orphans.erase(orphans.begin()+son);
//    		}
//    	}

    	//LPAggreg Scalar algorithm is called to process the data
    	NodeLPAggreg * algo=root;

    	for (unsigned int i=0; i< elements.size()-1; i++){
    		if (!elements[i]->hasChild())
    			leaves.push_back(elements[i]);
    	}

    	for (unsigned int i=0; i< leaves.size()-1; i++){
    		leaves[i]->setValue(atof((*loop)[i].c_str()));
    	}

    	//Init -> compute qualities
    	algo->init(false);

    	//getParts -> compute best cuts and best parts
    	//vector<int>* parts =
    	algo->getAggregation(parameter);

    	//Get and write in the ouput file time duration for each process
    	output << (*loop)[0] << ", "<<  elements.size() << ", "<<  leaves.size() << ","<< (*loop)[1] <<","<< (*loop)[2] <<", "<< algo->getQualityCount() <<", "<< algo->getBestCutCount() <<", "<< algo->getBestPartitionCount() <<", "<< algo->getQualityDuration() <<", " << algo->getBestCutDuration()<<", "<<algo->getBestPartitionDuration()<< endl;
    	//cout<<"done"<<endl;
    	delete algo;
    }


	return 0;
}
