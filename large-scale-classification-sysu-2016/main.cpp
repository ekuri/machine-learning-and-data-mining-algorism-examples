#include "decisiontree.h"
#include <iostream>

using namespace::std;

int main()
{
    Data data;
    cout << data.readFromFile("train.txt") << endl;
    Data rData;
    cout << endl << rData.randomizeFromData(data) << endl;
    DecisionTree singleTree;
    singleTree.build(rData);
    return 0;
}
