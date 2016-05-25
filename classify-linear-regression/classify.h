#ifndef CLASSIFY_H
#define CLASSIFY_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <float.h>
#include <assert.h>
#include <fstream>

class Classify {
private:
    std::vector<std::vector<double> > contain;

public:
    Classify(size_t rowSize, size_t rowLength) {
        contain.resize(rowSize);
        for (size_t count = 0; count < rowSize; count++) {
            contain[count].resize(rowLength);
        }
    }

    inline void randomizeSingleContain(size_t count) {
        for (size_t index = 0; index < contain.front().size(); index++) {
            contain[count][index] = rand() * 1.0 / RAND_MAX;
        }
    }

    inline void randomizeContain() {
        for (size_t count = 0; count < contain.size(); count++) {
            for (size_t index = 0; index < contain.front().size(); index++) {
                contain[count][index] = rand() * 1.0 / RAND_MAX;
            }
        }
    }

    inline void initContain(const std::vector<std::vector<double> > &data) {
        for (size_t count = 0; count < contain.size(); count++) {
            size_t randomIndex = rand() % data.size();
            for (size_t index = 0; index < contain[count].size(); index++) {
                contain[count][index] = data[randomIndex][index];
            }
        }
    }

    inline void printContain() {
        for (size_t count = 0; count < contain.size(); count++) {
            for (size_t index = 0; index < contain.front().size(); index++) {
                std::cout << contain[count][index] << " ";
            }
            std::cout << std::endl;
        }
    }

    inline bool isMatch(size_t index, const std::vector<double> &row) {
        return index == classifySingle(row);
    }

    inline void classify(const std::vector<std::vector<double> > &data) {
        std::vector<size_t> classesCount(contain.size());
        std::vector<size_t> oldClassesCount(contain.size());
        do {
            oldClassesCount = classesCount;
            std::vector<std::vector<std::vector<double> > > currentClassify;
            currentClassify.resize(contain.size());
            for (size_t count = 0; count < data.size(); count++) {
                size_t classifiedResult = classifySingle(data[count]);
                currentClassify[classifiedResult].push_back(data[count]);
            }

            size_t rowCount = 0;
            for (size_t count = 0; count < currentClassify.size(); count++) {
                classesCount[count] = currentClassify[count].size();
                rowCount += currentClassify[count].size();
                std::cout << currentClassify[count].size() << " ";
            }
            std::cout << std::endl;
            assert(rowCount == data.size());
            computeContain(currentClassify);
        } while (classesCount != oldClassesCount);
    }

    inline size_t classifySingle(const std::vector<double> &row) {
        size_t minRowIndex = 0;
        double minDistance = DBL_MAX;
        double currentDistance = 0.0;
        for (size_t count = 0; count < contain.size(); count++) {
            currentDistance = computeDistance(contain[count], row);
            if (currentDistance < minDistance) {
                minRowIndex = count;
                minDistance = currentDistance;
            }
        }
        return minRowIndex;
    }

    inline void save() {
        std::fstream classifyResultFile("classify.result", std::ios::out);
        if (!classifyResultFile) {
            throw "Classify.result can not write";
        }
        for (size_t count = 0; count < contain.size(); count++) {
            for (size_t index = 0; index < contain[count].size(); index++) {
                classifyResultFile << contain[count][index] << " ";
            }
            classifyResultFile << std::endl;
        }
        classifyResultFile.close();
    }

    inline void restore() {
        std::fstream classifyResultFile("classify.result");
        if (!classifyResultFile) {
            throw "Classify.result can not read";
        }
        for (size_t count = 0; count < contain.size(); count++) {
            for (size_t index = 0; index < contain[count].size(); index++) {
                classifyResultFile >> contain[count][index];
            }
        }
        classifyResultFile.close();
    }

private:
    inline void computeMean(const std::vector<std::vector<double> > &singleClass, std::vector<double> &singleClassifier) {
        assert(singleClassifier.size() == singleClass.front().size() - 1);
        for (size_t index = 0; index < singleClassifier.size(); index++) {
            double mean = 0.0;
            for (size_t count = 0; count < singleClass.size(); count++) {
                mean += singleClass[count][index];
            }
            mean /= singleClass.size();
            singleClassifier[index] = mean;
        }
    }

    inline void computeContain(const std::vector<std::vector<std::vector<double> > > &currentClassify) {
        assert(contain.size() == currentClassify.size());
        for (size_t count = 0; count < contain.size(); count++) {
            if (currentClassify[count].size() < 1) {
                continue;
            }
            computeMean(currentClassify[count], contain[count]);
        }
    }

    inline double computeDistance(const std::vector<double> &left, const std::vector<double> &right) {
        double sum = 0.0;
        assert(left.size() == right.size() - 1 || left.size() == right.size());
        for (size_t count = 0; count < left.size(); count++) {
            sum += (left[count] - right[count]) * (left[count] - right[count]);
        }
        return sum;
    }
};

#endif // CLASSIFY_H

