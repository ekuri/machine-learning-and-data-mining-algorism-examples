#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "csv.h"
#include "classify.h"
#include "linear_regression_runner.h"

const size_t rowLength = 386;
const size_t classesCount = 10;
Classify classifier(classesCount, rowLength - 1);
LinearRegressionRunner regressionRunner(classesCount);


#endif // GLOBAL_VARIABLE_H

