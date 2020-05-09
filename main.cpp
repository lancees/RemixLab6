#include <iostream>
#include "BinarySearchTree.h"
template <class ItemType>
int countNodes(std::shared_ptr<BinaryNode<ItemType>> nodePtr, int i) {
    if (nodePtr == nullptr) {
        return i;
    } else {
        i++;
        auto leftPtr = nodePtr->getLeftChildPtr();
        auto rightPtr = nodePtr->getRightChildPtr();
        i = countNodes(leftPtr, i);
        i = countNodes(rightPtr, i);
    }
    return i;
}
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
//    tree4Ptr->showTree();
    std::cout << " ******* " << std::endl;
    tree4Ptr->showTree(tree4Ptr->getRootPtr());
    std::cout << std::endl;
    std::cout << "root " << tree4Ptr->getRootPtr()->getItem() << tree4Ptr->getRootPtr()->getLeftChildPtr()->getItem();
    std::cout << std::endl;
    std::cout << tree4Ptr->contains(5);
    if (tree4Ptr->getParentNodeOf(5) == nullptr) {
        std::cout << " 5 has no parent" << std::endl;
    }
    std::cout << "3 has parent of " << tree4Ptr->getParentNodeOf(3)->getItem();
    std::cout << std::endl;
    std::cout << "9 has parent of " << tree4Ptr->getParentNodeOf(9)->getItem();
    std::cout << std::endl;
    tree4Ptr->remove(6);
    tree4Ptr->showTree(tree4Ptr->getRootPtr());
    std::cout << std::endl;
    std::cout << countNodes(tree4Ptr->getRootPtr(), 0) << std::endl;
    tree4Ptr->removeSmallest();
    tree4Ptr->showTree(tree4Ptr->getRootPtr());
//    tree4Ptr->removeNode
//    auto nineNode = tree4Ptr->findNode(tree4Ptr->getRootPtr(), 9);
//    std::cout << tree4Ptr->getParentNodeOf(6)->getItem();
//    std::cout << tree4Ptr->getRootPtr()->getLeftChildPtr()->getLeftChildPtr()->getItem();

    return 0;
}
