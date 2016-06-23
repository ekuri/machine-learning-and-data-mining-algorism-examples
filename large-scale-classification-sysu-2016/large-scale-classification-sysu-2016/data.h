#ifndef DATA_H
#define DATA_H

#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

class Data {
    struct Item {
        unsigned int index;
        bool value;
        Item() {}
        Item(unsigned int &index) {
            this->index = index;
            this->value = true;
        }
        Item(unsigned int &index, bool &value) {
            this->index = index;
            this->value = value;
        }
    };
private:
    const size_t bufferSize = 65536;
    std::vector<std::vector<Item> > data;
    std::vector<bool> reference;
public:
    inline void read(std::fstream &dataFile) {
        if (!dataFile) {
            throw "Data read failed. File not opened";
        }
        char *buffer = new char[bufferSize];
        while (dataFile.getline(buffer, bufferSize)) {
            parseSingleLine(buffer);
            for (size_t count = 0; count < data.front().size())
        }
        delete[] buffer;
    }
private:
    inline void parseSingleLine(const char *buffer) {
        data.push_back(Item(0, atoi(buffer)));
        char *pos;
        while (pos = strchr(buffer, ' ')) {
            data.push_back(Item(atoi(pos)));
            assert(data.back().index != 0);
        }
    }
};

#endif // DATA_H

