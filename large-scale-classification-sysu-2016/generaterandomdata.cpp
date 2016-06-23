#include "data.h"
#include <iostream>

using namespace::std;

int main()
{
    Data data;
    cout << data.readFromFile("train.txt") << endl;
    size_t treeCount = 300;

    fstream out("random.data", ios::out);
    fstream in("random.data");
    out << treeCount << endl;
    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "randomizing " << count << ": " << rData.randomizeFromData(data) << endl;
        rData.writeToRandomFile(out);
    }


    in >> treeCount;
    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "reading " << count << ": " << rData.readFromRandomFile(in) << endl;
    }

    return 0;
}

