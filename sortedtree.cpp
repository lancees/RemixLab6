//
// Created by Lance E. Sander on 5/9/2020.
//

#include <iostream>
#include <random>
#include <chrono>
#include "BinarySearchTree.h"
#include <list>

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
//    std::list<int> mylist;
//    mylist.push_back(11);
//    mylist.push_back(12);
//    mylist.push_back(16);
//    mylist.push_back(22);
//    mylist.push_back(23);
//    mylist.push_back(26);
//    mylist.push_back(35);
//    mylist.push_back(36);
    for (int i = 1; i <= 21; i++) {

        int randInt = distribution(generator);
//        int randInt = mylist.front();
//        std::cout << "-- " << randInt << std::endl;
//        mylist.pop_front();
        if (i == 1) {
            firstInt = randInt;
        }
        std::cout << randInt << std::endl;
        bst->add(randInt);
    }
    bst->showTree(bst->getRootPtr());
    std::cout << std::endl;
    bst->inorderTraverse(display);
    std::cout << std::endl;
    std::cout << " (Removing first inserted " << firstInt <<  ")" << std::endl;
    bst->remove(firstInt);
//    bst->removeSmallest();
    bst->inorderTraverse(display);
//    bst->showTree(bst->getRootPtr());
//    std::cout << std::endl;
//    bst->inorderTraverse(display);
//    bst->removeSmallest();
//    bst->showTree(bst->getRootPtr());
    return 0;
}