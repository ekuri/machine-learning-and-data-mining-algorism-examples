#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <vector>
#include <stdlib.h>
#include "data.h"

class DecisionTree {
    struct Item {
        size_t column;
        Item *left;
        Item *right;
        double entropy;
        Item(const size_t &_column, const double &_entropy) {
            column = _column;
            entropy = _entropy;
            left = NULL;
            right = NULL;
        }
    };

private:
    Item *head;
    static const double errorTolerance = 0.01;
    inline double computeEntropy(Data &data, const size_t &column) const {
        size_t trueCount = data.trueCount(column);
        double truePossibility = trueCount * 1.0 / data.size();
        double failPossibility = 1.0 - truePossibility;
        return -(log(truePossibility) / log(2) * truePossibility +
                log(failPossibility) / log(2) * failPossibility);
    }
    inline void deleteContent(Item *currentNode) {
        if (NULL == currentNode)
            return;
        deleteContent(currentNode->left);
        deleteContent(currentNode->right);
        delete currentNode;
    }

public:
    ~DecisionTree() {
        deleteContent(head);
    }

    inline void build(Data &data) {
        Item virtualItem(0, 1.0);
        buildSubTree(data, head, &virtualItem);
    }
    inline void buildSubTree(Data &data, Item *currentNode, const Item *fatherNode) {
        assert(fatherNode != NULL);
        deleteContent(currentNode);
        double minEntropy = 1.0;
        size_t minColumn;
        double currentEntropy;
        for (size_t count = 0; count < data.getColumnIncluded().size(); count++) {
            currentEntropy = computeEntropy(data, data.getColumnIncluded()[count]);
            std::cerr << "current entropy: " << currentEntropy << std::endl;
            assert(currentEntropy >= 0);
            if (currentEntropy < minEntropy) {
                minEntropy = currentEntropy;
                minColumn = count;
            }
        }
        currentNode = new Item(minColumn, currentEntropy);
        Data trueSide, failSide;
        data.clasify(trueSide, failSide, minColumn);
        data = Data();
        if (currentNode->entropy - fatherNode->entropy < errorTolerance) {
            return;
        }
        buildSubTree(trueSide, currentNode->left, currentNode);
        buildSubTree(failSide, currentNode->right, currentNode);
    }
};

#endif // DECISIONTREE_H

