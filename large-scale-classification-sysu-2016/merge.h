#ifndef MERGE
#define MERGE

#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>

void merge(size_t fileCount, char **filenames) {
    std::vector<double> prediction;
    char buff[128];
    std::fstream predictionFile(filenames[2]);
    if (!predictionFile) {
        std::cout << "prediction file can not open: " << filenames[2] << std::endl;
        return;
    }
    size_t currentCount = 0;
    std::cout << "reading: " << filenames[2] << std::endl;
    predictionFile.getline(buff, 128);
    currentCount = strtoul(buff, NULL, 0);
    char *comaStart;
    while (predictionFile.getline(buff, 128)) {
        comaStart = strchr(buff, ',');
        prediction.push_back(strtod(comaStart + 1, NULL));
    }


    for (size_t count = 1; count < fileCount; count++) {
        std::fstream predictionFile(filenames[count + 2]);
        if (!predictionFile) {
            std::cout << "prediction file can not open: " << filenames[count + 2] << std::endl;
            return;
        }

        std::cout << "reading: " << filenames[count + 2] << std::endl;
        predictionFile.getline(buff, 128);
        assert(currentCount == strtoul(buff, NULL, 0));
        for (size_t index = 0; index < prediction.size(); index++) {
            predictionFile.getline(buff, 128);
            comaStart = strchr(buff, ',');
            prediction[index] += strtod(comaStart + 1, NULL);
        }
        assert(!predictionFile.getline(buff, 128));
    }

    std::fstream resultFile(filenames[1], std::ios::out);
    if (!resultFile) {
        std::cout << "result file can not open: " << filenames[1] << std::endl;
    }
    resultFile << "id,label" << std::endl;
    for (size_t count = 0; count < prediction.size(); count++) {
        resultFile << count << ",";
        if (prediction[count] > 0.5 * fileCount) {
            resultFile << 1 << std::endl;
        } else {
            resultFile << 0 << std::endl;
        }
    }
}

#endif // MERGE

