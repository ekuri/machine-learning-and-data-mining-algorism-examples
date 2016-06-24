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
        bool leftPrediction;
        bool rightPrediction;
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
    static double errorTolerance;
    static size_t minSampleTolenrance;

    inline double computeSingleEntropy(const size_t &all, const size_t &trueAll, const size_t &positive, const size_t &negative) {
        assert(positive <= trueAll && trueAll <= all);
        assert(negative <= (all - trueAll) && (all - trueAll) <= all);
        assert(all != 0);
        double positiveEntropy, negativeEntropy;
        if (positive != 0 && positive < trueAll) {
            double positivePossibility = positive * 1.0 / trueAll;
            positiveEntropy = -(log(positivePossibility) / log(2) * positivePossibility +
                                log(1.0 - positivePossibility) / log(2) * (1.0 - positivePossibility));
            positiveEntropy = positiveEntropy * trueAll / all;
        } else {
            positiveEntropy = 0.0;
        }

        if (negative + trueAll < all && negative != 0) {
            double negativePossibility = negative * 1.0 / (all - trueAll);
            negativeEntropy = -(log(negativePossibility) / log(2) * negativePossibility +
                                log(1.0 - negativePossibility) / log(2) * (1.0 - negativePossibility));
            negativeEntropy = negativeEntropy * (all - trueAll) / all;
        } else {
            negativeEntropy = 0.0;
        }

        assert(positiveEntropy >= 0 && negativeEntropy >= 0);
        return positiveEntropy + negativeEntropy;
    }

    inline void computeEntropy(std::vector<size_t> &trueCount,
                                 std::vector<size_t> &positiveCount,
                                 std::vector<size_t> &negativeCount,
                                 std::vector<double> &entropy,
                                 std::vector<size_t> &columnIncluded,
                               const size_t &dataLength) {
        entropy.resize(columnIncluded.size());
        for (size_t count = 0; count < columnIncluded.size(); count++) {
            entropy[count] = computeSingleEntropy(dataLength, trueCount[count],
                                 positiveCount[count], negativeCount[count]);
            //std::cout << positive[currentColumn] << " " << negative[currentColumn] << std::endl;
        }
    }
    inline void deleteContent(Item *currentNode) {
        if (NULL == currentNode)
            return;
        deleteContent(currentNode->left);
        deleteContent(currentNode->right);
        delete currentNode;
    }

public:
    DecisionTree() {
        head = NULL;
    }

    ~DecisionTree() {
        deleteContent(head);
    }

    inline bool followTree(Item *currentNode, Data &data, size_t &row) {
        if (data.at(row, currentNode->column)) {
            if (currentNode->left) {
                return followTree(currentNode->left, data, row);
            }
            return currentNode->leftPrediction;
        }
        if (currentNode->right) {
            return followTree(currentNode->right, data, row);
        }
        return currentNode->rightPrediction;
    }

    inline void predict(Data &data, std::vector<size_t> &prediction) {
        assert(data.size() == prediction.size());
        assert(head);
        std::cout << "predicting" << std::endl;
        for (size_t count = 0; count < data.size(); count++) {
            if (followTree(head, data, count)) {
                prediction[count]++;
            }
        }
    }

    inline void build(Data &data) {
        Item virtualItem(0, 1.0);
        std::cout << "building tree" << std::endl;
        buildSubTree(data, head, &virtualItem, virtualItem.leftPrediction);
    }
    inline void buildSubTree(Data &data, Item* &currentNode, const Item *fatherNode, bool &targetPrediction) {
        if (data.size() < minSampleTolenrance) {
            targetPrediction = data.getPrediction();
            return;
        }
        assert(fatherNode != NULL);
        deleteContent(currentNode);
        std::vector<size_t> &columnIncluded = data.getColumnIncluded();
        assert(columnIncluded.size() > 0);

        std::vector<size_t> trueCount, positiveCount, negativeCount;
        std::vector<double> entropy;
        //std::cout << "getting count. data size: " << data.size() << std::endl;
        data.getCount(trueCount, positiveCount, negativeCount);
        //std::cout << "computing entropy. column included: " << columnIncluded.size() << std::endl;
        computeEntropy(trueCount, positiveCount, negativeCount, entropy, columnIncluded, data.size());

        double minEntropy = 1.0;
        size_t minColumn = columnIncluded[0];
        double currentEntropy;
        for (size_t count = 0; count < columnIncluded.size(); count++) {
            currentEntropy = entropy[count];
            if (currentEntropy < minEntropy) {
                minEntropy = currentEntropy;
                minColumn = columnIncluded[count];
            }
        }
        //std::cout << "select " << minColumn << " with entropy: " << minEntropy << std::endl;
        if (minColumn == fatherNode->column) {
            targetPrediction = data.getPrediction();
            return;
        }
        currentNode = new Item(minColumn, minEntropy);
        Data trueSide, failSide;
        data.clasify(trueSide, failSide, minColumn);
        data = Data();
        /*if (fatherNode->entropy - currentNode->entropy < errorTolerance) {
            return;
        }*/
        buildSubTree(trueSide, currentNode->left, currentNode, currentNode->leftPrediction);
        buildSubTree(failSide, currentNode->right, currentNode, currentNode->rightPrediction);
    }
};

double DecisionTree::errorTolerance = 0.0001;
size_t DecisionTree::minSampleTolenrance = 100;

#endif // DECISIONTREE_H

