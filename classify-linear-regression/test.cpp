#include "global_variable.h"
#include <iostream>
#include <signal.h>

int main()
{
    classifier.restore();
    std::cout << "Done restore classifier" << std::endl;
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
    return 0;
}

