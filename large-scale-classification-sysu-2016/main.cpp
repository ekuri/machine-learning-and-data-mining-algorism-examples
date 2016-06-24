#include "comparefile.h"
#include "split.h"
#include "generaterandomdata.cpp"
#include "randomforest.cpp"
#include <iostream>

using namespace::std;

int main(int argc, char** argv)
{
    //generateRandomData();
    split(argc - 2, argv);
    //randomForest(argc, argv);
    //compareFile();
    return 0;
}
