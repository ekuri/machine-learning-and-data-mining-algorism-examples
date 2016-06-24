#ifndef SPLIT_H
#define SPLIT_H

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
#include "data.h"

void split(size_t segment, char **filename) {
    assert(segment > 0);
    std::fstream dataFile(filename[1]);
    if (!dataFile) {
        std::cout << "can not open split file" << std::endl;
    }

    size_t treeCount;
    dataFile >> treeCount;
    std::cout << "All: " << treeCount << std::endl;

    size_t treeRead = 0;
    size_t segmentRowCount = treeCount / segment;
    for (size_t count = 0; count < segment - 1; count++) {
        std::cout << "Spliting segment: " << filename[count + 2] << " with row:" << segmentRowCount << std::endl;
        std::fstream segmentFile(filename[count + 2], std::ios::out);
        if (!segmentFile) {
            std::cout << "segment file can not open" << std::endl;
        }
        segmentFile << segmentRowCount << std::endl;
        for (size_t index = 0; index < segmentRowCount; index++) {
            Data currentData;
            currentData.readFromRandomFile(dataFile);
            currentData.writeToRandomFile(segmentFile);
            treeRead++;
        }
    }
    std::cout << "Spliting last segment: " << filename[segment + 1] << " with row:" << treeCount - treeRead << std::endl;
    std::fstream segmentFile(filename[segment + 1], std::ios::out);
    if (!segmentFile) {
        std::cout << "segment file can not open" << std::endl;
    }
    segmentFile << treeCount - treeRead << std::endl;
    for (; treeRead < treeCount; treeRead++) {
        Data currentData;
        currentData.readFromRandomFile(dataFile);
        currentData.writeToRandomFile(segmentFile);
    }
}

#endif // SPLIT_H

