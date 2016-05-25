#include "global_variable.h"
#include <iostream>
#include <signal.h>

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


