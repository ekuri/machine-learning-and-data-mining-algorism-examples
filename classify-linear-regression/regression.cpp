#include "global_variable.h"
#include <iostream>
#include <signal.h>

void catchSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "Interrupted. Exiting..." << std::endl;
        regressionRunner.saveResult();
        std::cout << "Done" << std::endl;
        exit(0);
    }
}

int main()
{
    classifier.restore();
    std::cout << "Done restoring classifier" << std::endl;
    regressionRunner.init(rowLength - 1);
    std::cout << "Done initializing regression runner" << std::endl;

    std::cout << "Restore result?(y/n)";
    char restore = getchar();
    getchar(); // for \n
    if (restore == 'y') {
        regressionRunner.restoreResult();
        std::cout << "Done restoring result" << std::endl;
    }

    size_t totalRecords = regressionRunner.restoreData();
    std::cout << "Done reading " << totalRecords << " records" << std::endl;

    signal(SIGINT, &catchSignal);
    while(true) {
        regressionRunner.run(1);
    }
    return 0;
}
