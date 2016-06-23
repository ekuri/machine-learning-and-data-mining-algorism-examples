#include <iostream>
#include <fstream>
#include <string>
#include "data.h"

using namespace std;

int main()
{
    fstream dataFile("train.txt");
    Data data;
    data.read(dataFile);
    return 0;
}

