/*
 * DLPAggreg2Test.cpp
 *
 *  Created on: 20 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg2Test.h"


int f_DLPAggreg2Test(){
	cout<<"0"<<endl;
	vector <double> values0;
	vector <double> values1;
	vector <double> values2;
	vector <double> values3;
	values0.push_back(0);
	values0.push_back(500);
	values0.push_back(0.3);
	values0.push_back(10000);
	values1.push_back(200);
	values1.push_back(4);
	values1.push_back(345);
	values1.push_back(5);
	values2.push_back(30000);
	values2.push_back(0);
	values2.push_back(1);
	values2.push_back(398);
	values3.push_back(4);
	values3.push_back(1045667);
	values3.push_back(4);
	values3.push_back(3);
	cout<<"A"<<endl;
	DLPAggreg2 * father = new DLPAggreg2(0);
	cout<<"Father"<<endl;
	father->addChild(new DLPAggreg2(1));
	father->addChild(new DLPAggreg2(2));
	cout<<"Childs"<<endl;
	DLPAggreg2 * temp = new DLPAggreg2(3);
	temp->setValues(values0);
	father->getChildNodes()[0]->addChild(temp);
	temp = new DLPAggreg2(4);
	temp->setValues(values1);
	father->getChildNodes()[0]->addChild(temp);
	cout<<"1"<<endl;
	temp = new DLPAggreg2(5);
	temp->setValues(values2);
	father->getChildNodes()[1]->addChild(temp);
	temp = new DLPAggreg2(6);
	temp->setValues(values3);
	father->getChildNodes()[1]->addChild(temp);
	//bug avec les values
	cout<<"B"<<endl;
	father->computeQualities(true);
	cout<<"C"<<endl;
	father->computeAggregation(0.0);
	cout<<"D"<<endl;

	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
	cout<<father->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
	cout<<father->getChildNodes()[0]->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
		cout<<father->getChildNodes()[0]->getChildNodes()[0]->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
		cout<<father->getChildNodes()[0]->getChildNodes()[1]->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
	cout<<father->getChildNodes()[1]->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
		cout<<father->getChildNodes()[1]->getChildNodes()[0]->getOptimalPartitions()[i];
	cout<<endl;
	for (unsigned int i=0; i<father->getOptimalPartitions().size(); i++)
		cout<<father->getChildNodes()[1]->getChildNodes()[1]->getOptimalPartitions()[i];
	return 0;
}
