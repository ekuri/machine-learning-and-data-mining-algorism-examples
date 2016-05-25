#include "csv.h"
#include "classify.h"
#include "linear_regression_runner.h"
#include <iostream>
#include <signal.h>

const size_t rowLength = 386;
const size_t classesCount = 10;
Classify classifier(classesCount, rowLength - 1);
LinearRegressionRunner regressionRunner(classesCount);

int main()
{
    fstream trainFile("train.csv");
    vector<vector<double> > data;
    CSV::readDataFromFile(trainFile, data, rowLength);
    std::cout << "Done reading train data. " << data.size() << " records" << std::endl;

    classifier.initContain(data);
    classifier.classify(data);
    std::cout << "Done classifying" << std::endl;
    regressionRunner.init(data, classifier, rowLength - 1);
    std::cout << "Done initializing regression runner" << std::endl;

    classifier.save();
    std::cout << "Done saving classifier" << std::endl;
    regressionRunner.saveData();
    std::cout << "Done saving regression data" << std::endl;
    return 0;
}


