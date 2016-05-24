#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>
#include <stdlib.h>
#include <assert.h>
#include "classify.h"

class LinearRegression {
private:
    std::vector<double> result;
    std::vector<std::vector<double> > data;
    double errorTolerance;
    double learningRate;
    size_t classifierIndex;

public:
    LinearRegression() {}

    LinearRegression(size_t rowLength, size_t classifierIndex) {
        result.resize(rowLength);
        errorTolerance = 1;
        learningRate = 0.05;
        this->classifierIndex = classifierIndex;
    }

    inline void init(size_t rowLength, size_t classifierIndex) {
        result.resize(rowLength);
        errorTolerance = 1;
        learningRate = 0.001;
        this->classifierIndex = classifierIndex;
    }

    inline void tryToAddData(const std::vector<std::vector<double> > &allData, Classify &classifier) {
        for (size_t count = 0; count < allData.size(); count++) {
            if (classifier.isMatch(classifierIndex, allData[count])) {
                data.push_back(allData[count]);
            }
        }
    }

    inline double compute(size_t iteration) {
        //std::cout << "#" << classifierIndex << ": Compute with data count: " << data.size() << std::endl;
        vector<double> currentPrediction(data.size());
        vector<double> noError(data.size());
        double currentError = 0;

        do {
            for (size_t count = 0; count < currentPrediction.size(); count++) {
                currentPrediction[count] = result[0];
                for (size_t index = 1; index < result.size(); index++) {
                    currentPrediction[count] += data[count][index] * result[index];
                }
                currentPrediction[count] -= data[count].back();
            }

            for (size_t count = 0; count < result.size(); count++) {
                computeSingle(currentPrediction, count);
            }

            currentError = computeVarivance(currentPrediction, noError);
            //cout << "current prediction varivance: " << currentError << endl;
        } while (--iteration);
        return currentError;
    }

private:
    inline void computeSingle(vector<double> &currentPrediction, size_t index) {
        double sum = 0;
        for (size_t count = 0; count < data.size(); count++) {
            sum += currentPrediction[count] * data[count][index];
        }
        sum *= learningRate;
        sum /= data.size() * 1.0;
        result[index] = result[index] - sum;
    }

    inline double computeVarivance(const std::vector<double> &left, const std::vector<double> &right) {
        double varivance = 0.0;
        assert(left.size() == right.size());
        for (size_t count = 0; count < left.size(); count++) {
            varivance += (left[count] - right[count]) * (left[count] - right[count]);
        }
        return varivance;
    }
};

#endif // LINEAR_REGRESSION_H

