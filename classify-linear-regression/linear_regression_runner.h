#ifndef LINEAR_REGRESSION_RUNNER_H
#define LINEAR_REGRESSION_RUNNER_H

#include "linear_regression.h"

class LinearRegressionRunner
{
private:
    std::vector<LinearRegression> runs;
    size_t rowLength;
public:
    LinearRegressionRunner(size_t runnerCount) {
        runs.resize(runnerCount);
    }

    inline void init(const std::vector<std::vector<double> > &allData, Classify &classifier, size_t rowLength) {
        this->rowLength = rowLength;
        for (size_t count = 0; count < runs.size(); count++) {
            runs[count].init(rowLength, count);
            runs[count].tryToAddData(allData, classifier);
        }
    }
    inline void init(size_t rowLength) {
        this->rowLength = rowLength;
        for (size_t count = 0; count < runs.size(); count++) {
            runs[count].init(rowLength, count);
        }
    }

    inline double run(size_t iteration) {
        double sumVarivance = 0.0;
        double currentVarivance;
        for (size_t count = 0; count < runs.size(); count++) {
            currentVarivance = runs[count].compute(iteration);
            sumVarivance += currentVarivance;
            std::cout << currentVarivance << "(" << runs[count].getData().size() << ") ";
        }
        std::cout << std::endl << "Sum varivance: " << sumVarivance << std::endl;
        return sumVarivance;
    }

    inline void saveResult() {
        std::fstream regressionResult("regression.result", std::ios::out);
        if (!regressionResult) {
            throw "regression.result can not write";
        }
        for (size_t count = 0; count < runs.size(); count++) {
            std::vector<double> currentResult = runs[count].getResult();
            for (size_t index = 0; index < currentResult.size(); index++) {
                regressionResult << currentResult[index] << " ";
            }
            regressionResult << std::endl;
        }
        regressionResult.close();
    }

    inline void restoreResult() {
        std::fstream regressionResult("regression.result");
        if (!regressionResult) {
            throw "regression.result can not read";
        }
        for (size_t count = 0; count < runs.size(); count++) {
            std::vector<double> currentResult = runs[count].getResult();
            for (size_t index = 0; index < currentResult.size(); index++) {
                regressionResult >> currentResult[index];
            }
            runs[count].setResult(currentResult);
        }
        regressionResult.close();
    }

    inline void saveData() {
        std::fstream regressionData("regression.data", std::ios::out);
        if (!regressionData) {
            throw "regression.data can not write";
        }
        for (size_t count = 0; count < runs.size(); count++) {
            std::vector<std::vector<double> > currentData = runs[count].getData();
            regressionData << currentData.size() << std::endl;
            for (size_t index = 0; index < currentData.size(); index++) {
                for (size_t temp = 0; temp < currentData[index].size(); temp++) {
                    regressionData << currentData[index][temp] << " ";
                }
                regressionData << std::endl;
            }
        }
        regressionData.close();
    }

    inline size_t restoreData() {
        std::fstream regressionData("regression.data");
        if (!regressionData) {
            throw "regression.data can not read";
        }
        size_t totalRecords = 0;
        for (size_t count = 0; count < runs.size(); count++) {
            std::vector<std::vector<double> > currentData;
            size_t dataSize;
            regressionData >> dataSize;
            totalRecords += dataSize;
            currentData.resize(dataSize);
            for (size_t index = 0; index < dataSize; index++) {
                currentData[index].resize(rowLength + 1);
                for (size_t temp = 0; temp < rowLength + 1; temp++) {
                    regressionData >> currentData[index][temp];
                }
            }
            runs[count].setData(currentData);
        }

        regressionData.close();
        return totalRecords;
    }
};

#endif // LINEAR_REGRESSION_RUNNER_H

