#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <map>

#include <iostream>

class Data {
private:
    std::vector<std::vector<size_t> > data;
    std::vector<bool> labels;
    std::vector<size_t> columnIncluded;
    std::map<size_t, size_t> columnRate;
    size_t columnLength;
    inline void appendFromStringLine(const std::string &dataLine) {
        const char * lineCharArray = dataLine.c_str();
        labels.push_back(strtoul(lineCharArray, NULL, 0));
        data.push_back(std::vector<size_t>());
        size_t start = dataLine.find(' ');
        size_t pos;
        while (start != std::string::npos) {
            pos = strtoul(lineCharArray + start + 1, NULL, 0);
            columnRate[pos]++;
            if (columnLength < pos) {
                columnLength = pos;
            }
            data.back().push_back(pos);
            start = dataLine.find(' ', start + 1);
        }
    }
    inline void countAll(std::vector<size_t> &trueCount,
                         std::vector<size_t> &positiveCount,
                         std::vector<size_t> &negativeCount,
                         const size_t &row) {
        for (size_t index = 0; index < columnIncluded.size(); index++) {
            size_t count = 0;
            for (; count < data[row].size(); count++) {
                if (data[row][count] == columnIncluded[index]) {
                    trueCount[index]++;
                    if (labels[row]) {
                        positiveCount[index]++;
                    }
                    break;
                }
            }
            if (count == data[row].size() && labels[row]) {
                negativeCount[index]++;
            }
        }
    }

    inline bool checkInColumnIncluded(const size_t &target) {
        for (size_t count = 0; count < columnIncluded.size(); count++) {
            if (target == columnIncluded[count])
                return true;
        }
        return false;
    }

public:
    static size_t treeCount;
    static size_t columnIncludedBound;
    inline size_t size() {
        return data.size();
    }

    inline std::vector<size_t> &getColumnIncluded() {
        return columnIncluded;
    }

    inline void printColumnRate() {
        for (std::map<size_t, size_t>::iterator it = columnRate.begin(); it != columnRate.end(); it++) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }
    inline void writeColumnRate(std::fstream &columnRateFile) {
        if (!columnRateFile) {
            throw "column rate file can not open";
        }
        for (std::map<size_t, size_t>::iterator it = columnRate.begin(); it != columnRate.end(); it++) {
            columnRateFile << it->first << " " << it->second << std::endl;
        }
    }

    inline bool at(const size_t &row, const size_t &column) {
        if (row >= data.size() || column > columnLength) {
            throw "data read out of range";
        }
        for (size_t count = 0; count < data[row].size(); count++) {
            if (data[row][count] == column) {
                return true;
            }
        }
        return false;
    }

    inline bool getPrediction() {
        size_t trueCount = 0;
        for (size_t count = 0; count < labels.size(); count++) {
            if (labels[count]) {
                trueCount++;
            }
        }
        //std::cout << "Predict " << (trueCount * 1.0 / labels.size()) << std::endl;
        return trueCount * 2 > labels.size();
    }

    inline void getCount(std::vector<size_t> &trueCount,
                               std::vector<size_t> &positiveCount,
                               std::vector<size_t> &negativeCount) {
        trueCount.resize(columnIncluded.size());
        positiveCount.resize(columnIncluded.size());
        negativeCount.resize(columnIncluded.size());
        for (size_t count = 0; count < data.size(); count++) {
            countAll(trueCount, positiveCount, negativeCount, count);
            /*if (count % 100 == 0) {
                std::cout << "getting count in: " << count << std::endl;
                std::cout << "column length: " << columnIncluded.size()
                          << " data row length: " << data[count].size() << std::endl;
            }*/
        }
    }

    inline size_t readFromFile(const char *fileName) {
        columnLength = 0;
        std::fstream dataFile(fileName);
        if (dataFile) {
            const size_t buffSize = 4096;
            char buff[buffSize];
            while (dataFile.getline(buff, buffSize)) {
                this->appendFromStringLine(buff);
            }
            assert(data.size() == labels.size());
            return data.size();
        } else {
            throw "can not open data file";
        }
        return 0;
    }

    inline size_t formColumnIncluded() {
        assert(columnRate.size() > 0);
        columnIncluded.clear();
        for (std::map<size_t, size_t>::iterator it = columnRate.begin(); it != columnRate.end(); it++) {
            if (it->second > columnIncludedBound) {
                columnIncluded.push_back(it->first);
            }
        }
        std::sort(columnIncluded.begin(), columnIncluded.end());
        return columnIncluded.size();
    }

    inline size_t randomizeFromData(const Data &origin) {
        data.clear();
        labels.clear();
        columnIncluded.clear();
        srand(time(NULL));

        // get random line
        size_t linesCount = origin.data.size() / treeCount;
        size_t index = 0;
        for (size_t count = 0; count < linesCount; count++) {
            index = (rand() + index) % origin.data.size();
            //std::cout << index << " ";
            data.push_back(origin.data[index]);
            labels.push_back(origin.labels[index]);
        }
        //std::cout << std::endl;
        assert(data.size() == labels.size());

        // include random column
        assert(origin.columnIncluded.size() > 0);
        size_t columnsIncludedCount = origin.columnIncluded.size() / 2;
        index = 0;
        for (size_t count = 0; count < columnsIncludedCount; count++) {
            index = (rand() + index) % origin.columnIncluded.size();
            columnIncluded.push_back(origin.columnIncluded[index]);
        }
        //std::cout << std::endl;
        std::sort(columnIncluded.begin(), columnIncluded.end());
        // delete duplicated
        std::vector<size_t>::iterator it = std::unique(columnIncluded.begin(), columnIncluded.end());
        assert(columnIncluded.size() == columnsIncludedCount);
        columnIncluded.erase(it, columnIncluded.end());
        return data.size();
    }
    inline void clasify(Data &trueSide, Data &failSide, const size_t &column) {
        trueSide.data.clear();
        trueSide.labels.clear();
        failSide.data.clear();
        failSide.labels.clear();
        trueSide.columnIncluded = columnIncluded;
        failSide.columnIncluded = columnIncluded;
        for (size_t count = 0; count < data.size(); count++) {
            size_t index = 0;
            for (; index < data[count].size(); index++) {
                if (data[count][index] == column) {
                    trueSide.data.push_back(data[count]);
                    trueSide.labels.push_back(labels[count]);
                    break;
                }
            }
            if (index >= data[count].size()) {
                failSide.data.push_back(data[count]);
                failSide.labels.push_back(labels[count]);
            }
        }
    }

    inline void writeToRandomFile(std::fstream &outputFile) {
        if (!outputFile) {
            throw "output file can not open";
        }
        outputFile << columnIncluded.size() << std::endl;
        for (size_t count = 0; count < columnIncluded.size(); count++) {
            outputFile << columnIncluded[count] << " ";
        }
        outputFile << std::endl;
        outputFile << data.size() << std::endl;
        for (size_t count = 0; count < data.size(); count++) {
            outputFile << labels[count] << " ";
            for (size_t index = 0; index < data[count].size() - 1; index++) {
                if (checkInColumnIncluded(data[count][index])) {
                    outputFile << data[count][index] << " ";
                }
            }
            if (checkInColumnIncluded(data[count].back())) {
                outputFile << data[count].back();
            }
            outputFile << std::endl;
        }
    }
    inline size_t readFromRandomFile(std::fstream &randomFile) {
        if (!randomFile) {
            throw "can not open random file";
        }
        columnIncluded.clear();
        labels.clear();
        data.clear();
        size_t includedColumnCount;
        randomFile >> includedColumnCount;
        columnIncluded.resize(includedColumnCount);

        size_t currentNumber;
        for (size_t count = 0; count < includedColumnCount; count++) {
            randomFile >> currentNumber;
            columnIncluded[count] = currentNumber;
        }

        size_t dataLineCount;
        randomFile >> dataLineCount;

        const size_t buffSize = 4096;
        char buff[buffSize];
        // read \n from last line where data start
        randomFile.getline(buff, buffSize);
        for (size_t count = 0; count < dataLineCount; count++) {
            randomFile.getline(buff, buffSize);
            this->appendFromStringLine(buff);
        }
        assert(data.size() == labels.size());
        return data.size();
    }
};

size_t Data::treeCount = 50;
size_t Data::columnIncludedBound = 10000;

#endif // DATA_H

