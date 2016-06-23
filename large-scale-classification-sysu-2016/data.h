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

#include <iostream>

class Data {
private:
    std::vector<std::vector<size_t> > data;
    std::vector<bool> labels;
    std::vector<size_t> columnIncluded;
    size_t columnLength;
    inline void appendFromStringLine(const std::string &dataLine) {
        const char * lineCharArray = dataLine.c_str();
        labels.push_back(strtoul(lineCharArray, NULL, 0));
        data.push_back(std::vector<size_t>());
        size_t start = dataLine.find(' ');
        size_t pos;
        while (start != std::string::npos) {
            pos = strtoul(lineCharArray + start + 1, NULL, 0);
            if (columnLength < pos) {
                columnLength = pos;
            }
            data.back().push_back(pos);
            start = dataLine.find(' ', start + 1);
        }
    }

public:
    inline size_t size() {
        return data.size();
    }

    inline std::vector<size_t> &getColumnIncluded() {
        return columnIncluded;
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

    inline size_t trueCount(const size_t &column) {
        size_t result = 0;
        for (size_t count = 0; count < data.size(); count++) {
            for (size_t index = 0; index < data[count].size(); index++) {
                if (data[count][index] == column) {
                    result++;
                    break;
                }
            }
        }
        return result;
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
    inline size_t randomizeFromData(const Data &origin) {
        data.clear();
        labels.clear();
        columnIncluded.clear();
        srand(time(NULL));

        // get random line
        size_t linesCount = origin.data.size() / 100;
        size_t index = 0;
        for (size_t count = 0; count < linesCount; count++) {
            index = (rand() + index) % origin.data.size();
            //std::cout << index << " ";
            data.push_back(origin.data[index]);
            labels.push_back(origin.labels[index]);
        }
        //std::cout << std::endl;
        assert(data.size() == labels.size());

        // exclude random column
        size_t columnsIncludedCount = origin.columnLength / 10;
        index = 0;
        for (size_t count = 0; count < columnsIncludedCount; count++) {
            index = (rand() + index) % origin.columnLength;
            //std::cout << index << " ";
            columnIncluded.push_back(index);
        }
        //std::cout << std::endl;
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
                outputFile << data[count][index] << " ";
            }
            outputFile << data[count].back() << std::endl;
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


#endif // DATA_H

