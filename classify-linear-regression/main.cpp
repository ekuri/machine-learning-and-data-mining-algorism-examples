#include "csv.h"
#include "classify.h"
#include <iostream>
#include <signal.h>

const size_t rowLength = 386;
Classify classifier(10, rowLength - 1);

void catchSignal(int signal) {
    if (signal == SIGINT) {
        classifier.save();
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
    classifier.classify(data);
    /*classifier.initContain(data);
    signal(SIGINT, &catchSignal);
    while (true) {
        classifier.classify(data);
    }*/
    //classifier.restore();
    //classifier.printContain();
    //classifier.printContain();
    return 0;
}

