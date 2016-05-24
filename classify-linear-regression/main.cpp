#include "csv.h"
#include "classify.h"
#include "linear_regression.h"
#include <iostream>
#include <signal.h>

const size_t rowLength = 386;
const size_t classesCount = 10;
Classify classifier(classesCount, rowLength - 1);
std::vector<LinearRegression> regressionRunner(classesCount);

void catchSignal(int signal) {
    if (signal == SIGINT) {
        //classifier.save();
        std::cout << "Interrupted. Exiting...";
        exit(0);
    }
}

int main()
{
    fstream trainFile("train.csv");
    vector<vector<double> > data;
    CSV::readDataFromFile(trainFile, data, rowLength);

    classifier.restore();
    for (size_t count = 0; count < regressionRunner.size(); count++) {
        regressionRunner[count].init(rowLength - 1, count);
        regressionRunner[count].tryToAddData(data, classifier);
    }
    while(true) {
        double sumVarivance = 0.0;
        double currentVarivance;
        for (size_t count = 0; count < regressionRunner.size(); count++) {
            currentVarivance = regressionRunner[count].compute(1);
            sumVarivance += currentVarivance;
            std::cout << currentVarivance << " ";
        }
        std::cout << std::endl << "Sum varivance: " << sumVarivance << std::endl;
    }
    return 0;
}

