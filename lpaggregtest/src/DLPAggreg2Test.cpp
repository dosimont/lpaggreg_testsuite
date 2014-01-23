/*
 * DLPAggreg2Test.cpp
 *
 *  Created on: 20 janv. 2014
 *      Author: dosimont
 */

#include "DLPAggreg2Test.h"
#define SIZE 30
#define NODES 10
#define CHILDS 2
#define THRESHOLD 0.0001


int f_DLPAggreg2Test(){
	srand(time(NULL));
	vector <double> values;
	vector <DLPAggreg1 *> nodes = vector<DLPAggreg1*>();
	nodes.push_back(new DLPAggreg1(0));
	for (int i=1; i<=NODES; i++){
		nodes.push_back(new DLPAggreg1(i));
		nodes[(i-1)/(CHILDS)]->addChild(nodes[i]);
	}
	cout<<"Values"<<endl;
	for (int i=1; i<=NODES; i++){
		if (!nodes[i]->hasChild()){
			values.clear();
			cout<<endl<<"Node "<<i<<":    ";
			for (int j=0; j<SIZE; j++){
				int temp=rand()%20+1;
				values.push_back(temp);
				cout<<temp<<" ";
			}
			nodes[i]->setValues(values);
		}
	}
	nodes[0]->computeQualities(false);

			vector<float> p=nodes[0]->getParameters(THRESHOLD);
	while(true){
		cout<<endl<<endl<<"Parameters"<<endl<<endl;
		for (unsigned int i=0; i<p.size(); i++)
			cout<<p[i]<<" ";
		cout<<endl;
		float param;
		cin>>param;
		nodes[0]->computeAggregation(param);
		cout<<"Aggregation"<<endl<<endl;
		for (int i=1; i<=NODES; i++){
			if (!nodes[i]->hasChild()){
				cout<<endl<<"Node "<<i<<":    ";
				for (unsigned int j=0; j<nodes[i]->getBestPartitions().size(); j++)
						cout<<nodes[i]->getBestPartitions()[j]<<" ";
			}
		}
	}
	return 0;
}
