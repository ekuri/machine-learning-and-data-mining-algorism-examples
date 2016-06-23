#include "decisiontree.h"
#include <iostream>

using namespace::std;

int main()
{
    size_t treeCount;
    fstream in("random.data");
    in >> treeCount;
    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "reading " << count << ": " << rData.readFromRandomFile(in) << endl;
        DecisionTree currentTree;
        currentTree.build(rData);
    }
    return 0;
}


