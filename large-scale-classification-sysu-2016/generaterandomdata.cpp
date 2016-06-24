#include "data.h"
#include <iostream>

using namespace::std;

int generateRandomData()
{
    Data data;
    cout << "data reading: " << data.readFromFile("train.txt") << endl;
    cout << "included column: " << data.formColumnIncluded() << endl;

    //fstream columnRateFile("column.rate", ios::out);
    //data.writeColumnRate(columnRateFile);
    size_t treeCount = Data::treeCount;

    fstream out("random.data", ios::out);
    fstream in("random.data");
    out << treeCount << endl;
    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "randomizing " << count << ": " << rData.randomizeFromData(data);
        cout << " column: " << rData.getColumnIncluded().size() << endl;
        rData.writeToRandomFile(out);
    }


    in >> treeCount;
    for (size_t count = 0; count < treeCount; count++) {
        Data rData;
        cout << "reading " << count << ": " << rData.readFromRandomFile(in) << endl;
    }

    return 0;
}

