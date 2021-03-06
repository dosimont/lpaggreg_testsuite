/*
 * LPAggregScalarTest.cpp
 *
 *  Created on: 20 juin 2013
 *      Author: dosimont
 */


#include "OLPAggreg1Test.h"


int f_OLPAggreg1Test(int argc, const char* argv[]) {

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
    for(; loop != CSVIterator(); ++loop) {

        //Gain/loss parameter is the first field
        float parameter = atof((*loop)[3].c_str());

        //Vector for storing trace elements
        vector<double>elements;

        //Store input file line elements in the vector
        for (unsigned int i = 4; i<(*loop).size(); i++) {
            elements.push_back(atof((*loop)[i].c_str()));
        }

        //LPAggreg Scalar algorithm is called to process the data
        OLPAggreg1 algo = OLPAggreg1(elements);

        //Init -> compute qualities
        algo.computeQualities(false);

        //getParts -> compute best cuts and best parts
        vector<int>parts = algo.getParts(parameter);

        //Get and write in the ouput file time duration for each process
        output << (*loop)[0] <<", "<<  parts.size() << ","<< (*loop)[1] <<","<< (*loop)[2] <<", "<< algo.getQualityCount() <<", "<< algo.getBestCutCount() <<", "<< algo.getBestPartitionCount() <<", "<< algo.getQualityDuration() <<", " << algo.getBestCutDuration()<<", "<<algo.getBestPartitionDuration()<< endl;
    }


    return 0;
}


