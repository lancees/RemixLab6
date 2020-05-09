//
// Created by Lance E. Sander on 5/9/2020.
//

#include <iostream>
#include <random>
#include <chrono>
#include "BinarySearchTree.h"

void display(int& anItem)
{
    std::cout << "Displaying item - " << anItem << std::endl;
}  // end display

int main() {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1,100);

    std::cout << " (Generating 21 random ints between 1 and 100)" << std::endl;
    int firstInt;
    auto bst = std::make_shared<BinarySearchTree<int>>();
    for (int i = 1; i <= 21; i++) {
        int randInt = distribution(generator);
        if (i == 1) {
            firstInt = randInt;
        }
        std::cout << randInt << std::endl;
        bst->add(randInt);
    }
    bst->showTree(bst->getRootPtr());
    std::cout << std::endl;
    std::cout << " (Removing first inserted " << firstInt <<  ")" << std::endl;
    bst->remove(firstInt);
    bst->showTree(bst->getRootPtr());
    std::cout << std::endl;
    bst->inorderTraverse(display);
    return 0;
}