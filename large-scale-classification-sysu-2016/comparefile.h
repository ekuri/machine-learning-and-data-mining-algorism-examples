#ifndef COMPAREFILE
#define COMPAREFILE

#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>

using namespace::std;

int compareFile()
{
    fstream leftFile("result.data");
    fstream rightFile("result1.csv");
    if (!leftFile || !rightFile) {
        cout << "at least one compare file can not open" << endl;
    }

    char leftBuff[128], rightBuff[128];

    size_t diffCount = 0;
    size_t count = 0;
    char *leftStart, *rightStart;
    while(rightFile.getline(rightBuff, 128) && leftFile.getline(leftBuff, 128)) {
        leftStart = strchr(leftBuff, ',');
        rightStart = strchr(rightBuff, ',');
        if (strtoul(leftStart + 1, NULL, 0) != strtoul(rightStart + 1, NULL, 0)) {
            diffCount++;
        }
        count++;
    }
    assert(!rightFile.getline(rightBuff, 128) && !leftFile.getline(leftBuff, 128));
    cout << count << endl;
    cout << diffCount << endl;
    return 0;
}


#endif // COMPAREFILE

