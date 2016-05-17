#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "csv.h"

using namespace::std;
const char testFilename[] = "test.csv";
const char submissionFilename[] = "submission.csv";

void run() {
    fstream resultFile(resultFilename, ios::in);
    fstream testFile(testFilename, ios::in);
    fstream submissionFile(submissionFilename, ios::out);
    if (!(resultFile && testFile && submissionFile)) {
        cerr << "At least one file failed to open: " << resultFilename
             << " " << testFilename << " " << submissionFilename << endl;
        exit(1);
    }

    vector<double> linearRegressionResult;
    double temp;
    while (resultFile >> temp) {
        linearRegressionResult.push_back(temp);
    }

    string line;
    testFile >> line; // ignore first header line
    vector<double> tempData;
    vector<vector<double> > data;
    while (testFile >> line) {
        tempData.clear();
        getDataFromString(line, tempData, linearRegressionResult.size());
        data.push_back(tempData);
    }

    vector<double> reference(data.size());
    for (size_t count = 0; count < data.size(); count++) {
        reference[count] = linearRegressionResult[0];
        for (size_t index = 1; index < linearRegressionResult.size(); index++) {
            reference[count] += linearRegressionResult[index] * data[count][index];
        }
    }

    submissionFile << "Id,reference" << endl;
    for (size_t count = 0; count < reference.size(); count++) {
        submissionFile << count << "," << reference[count] << endl;
    }
    cout << "Done." << endl;
}
