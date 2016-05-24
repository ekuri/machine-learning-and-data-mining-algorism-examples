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

int main () {
    cout << "t to train. r ro run test"<< endl;
    char command = getchar();
    getchar(); // read \n
    if (command == 't') {
        cout << "resume from " << resultFilename << "?(y/n)";
        command = getchar();
        if (command == 'y') {
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
