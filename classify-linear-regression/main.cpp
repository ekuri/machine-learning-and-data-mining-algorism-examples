#include "csv.h"
#include "classify.h"
#include "linear_regression_runner.h"
#include <iostream>
#include <signal.h>

const size_t rowLength = 386;
const size_t classesCount = 10;
Classify classifier(classesCount, rowLength - 1);
LinearRegressionRunner regressionRunner(classesCount);

void catchSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "Interrupted. Exiting..." << std::endl;
        //classifier.save();
        //regressionRunner.saveResult();
        //regressionRunner.saveData();
        std::cout << "Done" << std::endl;
        exit(0);
    }
}

int main()
{
    /*fstream trainFile("train.csv");
    vector<vector<double> > data;
    CSV::readDataFromFile(trainFile, data, rowLength);
    std::cout << "Done reading data" << std::endl;*/

    classifier.restore();
    std::cout << "Done restore classifier" << std::endl;
    //regressionRunner.init(data, classifier, rowLength - 1);
    regressionRunner.init(rowLength - 1);
    std::cout << "Done init regression runner" << std::endl;
    regressionRunner.restoreResult();
    std::cout << "Done restore result" << std::endl;

    fstream testFile("test.csv");
    vector<vector<double> > data;
    CSV::readDataFromFile(testFile, data, rowLength - 1);
    std::cout << "Done reading test data. " << data.size() << " records" << std::endl;

    regressionRunner.test(data, classifier);
    std::cout << "Done testing" << std::endl;
    //size_t totalRecords = regressionRunner.restoreData();
    //std::cout << "Done reading " << totalRecords << " records" << std::endl;

    /*signal(SIGINT, &catchSignal);
    while(true) {
        regressionRunner.run(1);
    }*/
    return 0;
}

