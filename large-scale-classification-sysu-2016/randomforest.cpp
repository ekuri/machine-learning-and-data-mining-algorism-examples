#include "decisiontree.h"
#include <iostream>

using namespace::std;

int randomForest()
{
    Data testData;
    cout << "reading test data" << endl;
    testData.readFromFile("test.txt");

    size_t treeCount;
    fstream in("random.data");
    if (!in) {
        cout << "can not open random data file" << endl;
        return 1;
    }

    in >> treeCount;
    treeCount = 4;

    vector<size_t> prediction(testData.size());
    fstream testResultFile("result.data", ios::out);
    fstream testResultAccurateFile("result_accurate.data", ios::out);
    if (!testResultFile || !testResultAccurateFile) {
        cout << "result file can not open" << endl;
        return 1;
    }

    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "reading " << count << ": " << rData.readFromRandomFile(in) << endl;
        DecisionTree currentTree;
        currentTree.build(rData);
        currentTree.predict(testData, prediction);
    }

    double currentPredictionRate;
    testResultFile << "id,label" << endl;
    for (size_t count = 0; count < prediction.size(); count++) {
        currentPredictionRate = prediction[count] * 1.0 / treeCount;
        testResultFile << count << "," << ((currentPredictionRate > 0.5)?1:0) << endl;
        testResultAccurateFile << count << "," << currentPredictionRate << endl;
    }

    return 0;
}


