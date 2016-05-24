#ifndef CSV_H
#define CSV_H

#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace::std;
class CSV {
    class CSVError {
    private:
        string msg;
    public:
        CSVError(const string &msg) {
            this->msg = msg;
        }
        string what() {
            return msg;
        }
    };

public:
    inline static void getDataFromString(const string &line, vector<double> &data, size_t rowLength) {
        unsigned int start = 0;
        const char* lineCharArray = line.c_str();
        size_t end = 0;
        while (end != string::npos) {
            end = line.find(',', start);
            data.push_back(strtod(lineCharArray + start, NULL));
            start = end + 1;
        }

        if (data.size() != rowLength) {
            throw CSVError("Csv line read error");
        }
        data[0] = 1.0;
    }

    inline static void readDataFromFile(fstream &infile, vector<vector<double> > &data, const size_t &rowLength) {
        if (!infile) {
            throw CSVError("File open error in reading data from file");
        } else {
            string line;
            infile >> line; // ignore first line

            vector<double> tempData;
            while (infile >> line) {
                tempData.clear();
                getDataFromString(line, tempData, rowLength);
                data.push_back(tempData);
            }
        }
    }
};

#endif // CSV_H

