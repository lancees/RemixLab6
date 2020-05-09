#include <iostream>
#include "BinarySearchTree.h"

int main() {
//    BinarySearchTree<int> * tree = new BinarySearchTree<int>();
   auto tree2Ptr = std::make_shared<BinarySearchTree<int>>(3);
   auto tree3Ptr = std::make_shared<BinarySearchTree<int>>(6);
   auto tree4Ptr = std::make_unique<BinarySearchTree<int>>(5, tree2Ptr, tree3Ptr);

   std::cout << tree2Ptr->getRootData();
   std::cout << tree3Ptr->getRootData();
   std::cout << tree4Ptr->getRootData();
   std::cout << std::endl;
//    BinarySearchTree<int> * tree = new BinarySearchTree<int>(5);
    tree4Ptr->add(9);
    tree4Ptr->add(1);
//    tree4Ptr->showTree();
    tree4Ptr->showTree();
    std::cout << " ******* " << std::endl;
    tree4Ptr->neoShowTree(tree4Ptr->getRootPtr());
    std::cout << std::endl;
    std::cout << "root " << tree4Ptr->getRootPtr()->getItem() << tree4Ptr->getRootPtr()->getLeftChildPtr()->getItem();
//    std::cout << tree4Ptr->getRootPtr()->getLeftChildPtr()->getLeftChildPtr()->getItem();

    return 0;
}
