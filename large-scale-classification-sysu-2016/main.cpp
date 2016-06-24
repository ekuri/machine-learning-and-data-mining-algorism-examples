#include "comparefile.h"
#include "split.h"
#include "merge.h"
#include "generaterandomdata.cpp"
#include "randomforest.cpp"
#include <iostream>

using namespace::std;

int main(int argc, char** argv)
{
    //generateRandomData();
    //split(argc - 2, argv);
    //randomForest(argc, argv);
    //merge(argc - 2, argv);
    compareFile(argc - 1, argv);
    return 0;
}
