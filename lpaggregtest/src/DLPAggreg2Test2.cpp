/*
 * DLPAggreg2Test.cpp
 *
 *  Created on: 20 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg2Test2.h"


int f_DLPAggreg2Test2(){
	cout<<"0"<<endl;
	vector <double> values0;
	vector <double> values1;
	vector <double> values2;
	vector <double> values3;
	values0.push_back(24);
	values0.push_back(30);
	values0.push_back(10);
	values0.push_back(10);
	values0.push_back(5);
	values1.push_back(7);
	values1.push_back(30);
	values1.push_back(10);
	values1.push_back(1000);
	values1.push_back(100);
	DLPAggreg2 * father = new DLPAggreg2(0);
	DLPAggreg2 * child1 = new DLPAggreg2(1);
	DLPAggreg2 * child2 = new DLPAggreg2(2);
	child1->setValues(values0);
	child2->setValues(values1);
	father->addChild(child1);
	father->addChild(child2);
	father->computeQualities(false);
	father->computeAggregation(0.0);


	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++){
		for (unsigned int j=0; j<father->getOptimalPartitions().size()-i; j++){
			cout<<child1->getQualities()[i][j]->getGain()<<"; ";
	}
		cout<<endl;
	}

	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++){
		for (unsigned int j=0; j<father->getOptimalPartitions().size()-i; j++){
			cout<<child1->getQualities()[i][j]->getLoss()<<"; ";
	}
		cout<<endl;
	}

	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
	cout<<father->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<child1->getOptimalPartitions().size(); i++)
	cout<<child1->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<child2->getOptimalPartitions().size(); i++)
	cout<<child2->getOptimalPartitions()[i];
	cout<<endl;
	return 0;
}
