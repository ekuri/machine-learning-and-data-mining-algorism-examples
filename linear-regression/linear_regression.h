#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

const size_t rowLength = 386;
const size_t rowCount = 26000;
const double errorTolerance = 1;
const double learningRate = 0.05;
const double giveUpInterval = 0.000001 * 0.000001;
vector<double> linearRegressionResult;

inline void singleLinearRegression(const vector<vector<double> > &data, vector<double> &currentPrediction,
                                   vector<double> &result, size_t index) {
    double sum = 0;
    for (size_t count = 0; count < data.size(); count++) {
        sum += currentPrediction[count] * data[count][index];
    }
    sum *= learningRate;
    sum /= data.size() * 1.0;
    result[index] = result[index] - sum;
}

inline void linearRegression(const vector<vector<double> > &data) {
    linearRegressionResult.resize(data.front().size() - 1);

    vector<double> currentPrediction(data.size());
    vector<double> noError(data.size());
    double currentError = 0;

    do {
        for (size_t count = 0; count < currentPrediction.size(); count++) {
            currentPrediction[count] = linearRegressionResult[0];
            for (size_t index = 1; index < linearRegressionResult.size(); index++) {
                currentPrediction[count] += data[count][index] * linearRegressionResult[index];
            }
            currentPrediction[count] -= data[count].back();
        }

        for (size_t count = 0; count < linearRegressionResult.size(); count++) {
            singleLinearRegression(data, currentPrediction, linearRegressionResult, count);
        }

        currentError = computeVarivance(currentPrediction, noError);
        cout << "current prediction varivance: " << currentError << endl;
    } while (currentError > errorTolerance);

    cout << "Writing to resume file." << endl;
    writeToResumeFile(linearRegressionResult, resultFilename);
    cout << "Done." << endl;
}

#endif // LINEAR_REGRESSION_H

