#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include "csv.h"
#include "linear_regression.h"
#include "run.h"

using namespace::std;

void catchSignal(int signal) {
    if (signal == SIGINT) {
        cout << "Signal Interrupt. Exiting..." << endl;
        writeToResumeFile(linearRegressionResult, resultFilename);
        exit(0);
    }
}

int main (int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        cout << "Invalid arguement" << endl;
        return 1;
    }

    if (strcmp(argv[1], "regression") == 0) {
        if (argc == 3 && strcmp(argv[2], "resume") == 0) {
            readFromResumeFile(linearRegressionResult, resultFilename);
        }
        vector<vector<double> > data(rowCount);
        data.clear();

        readDataFromFile("train.csv", data, rowLength);

        signal(SIGINT, &catchSignal);
        linearRegression(data);
    } else {
        run();
    }
    return 0;
}
