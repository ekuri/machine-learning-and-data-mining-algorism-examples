#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
#include <stdlib.h>

using namespace::std;

const char resultFilename[] = "result";

inline void getDataFromString(const string &line, vector<double> &data, size_t rowLength) {
    unsigned int start = 0;
    const char* lineCharArray = line.c_str();
    unsigned int end = 0;
    while (end != string::npos) {
        end = line.find(',', start);
        data.push_back(strtod(lineCharArray + start, NULL));
        start = end + 1;
    }

    if (data.size() != rowLength) {
        cout << "Illegal row length not equal to definition. (" << rowLength << ")"
             << " current: " << data.size() << endl;
        exit(1);
    }
    data[0] = 1.0;
}

inline void readDataFromFile(const char *dataFilename, vector<vector<double> > &data, size_t rowLength) {
    fstream infile(dataFilename);
    if (!infile) {
        cout << "Error: Failed to open " << dataFilename << endl;
        exit(1);
    } else {
        cout << "Reading file: " << dataFilename << endl;

        time_t start, end;
        time(&start);

        string line;
        infile >> line; // ignore first line

        vector<double> tempData;
        while (infile >> line) {
            tempData.clear();
            getDataFromString(line, tempData, rowLength);
            data.push_back(tempData);
        }
        infile.close();

        time(&end);
        cout << "Data read cost " << difftime(end, start) << "s" << endl;
    }
}

inline double computeVarivance(const vector<double> &left, const vector<double> &right) {
    if (left.size() != right.size()) {
        throw "Varivance compute with different size";
    }

    double result = 0;
    for (size_t count = 0; count < left.size(); count++) {
        result += (left[count] - right[count]) * (left[count] - right[count]);
    }

    return result;
}

inline void writeToResumeFile(const vector<double> &data, const char *resultFilename) {
    fstream resultFile(resultFilename, ios::out);
    if (!resultFile) {
        cout << "outfile failed to open." << endl;
        resultFile.close();
        exit(1);
    }
    for (size_t count = 0; count < data.size(); count++) {
        resultFile << data[count] << " ";
    }
    resultFile.close();
}

inline void readFromResumeFile(vector<double> &linearRegressionResult, const char *resultFilename) {
    fstream resultFile(resultFilename);
    if (!resultFile) {
        cerr << "result file failed to open" << endl;
        exit(1);
    }
    cout << "Resuming..." << endl;
    double temp;
    while (resultFile >> temp) {
        linearRegressionResult.push_back(temp);
    }
}

#endif // CSV_H

