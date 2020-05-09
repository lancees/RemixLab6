//
// Created by Lance Sander on 5/9/20.
//

#ifndef REMIXLAB6_BINARYSEARCHTREE_H
#define REMIXLAB6_BINARYSEARCHTREE_H

#include <memory>
#include <vector>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
// use this->rootPtr to access the BinaryNodeTree rootPtr

protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    // Recursively finds where the given node should be placed and
    // inserts it in a leaf at that point.
    std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
    std::shared_ptr<BinaryNode<ItemType>> newNode);

    // Removes the given target value from the tree while maintaining a
    // binary search tree.
    std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
    const ItemType target,
    bool& success);

    // Removes a given node from a tree while maintaining a
    // binary search tree.
    std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);

    // Removes the leftmost node in the left subtree of the node
    // pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
    ItemType& inorderSuccessor);

    // Returns a pointer to the node containing the given value,
    // or nullptr if not found.
    std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
    const ItemType& target) const;

public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    // inherits from BinaryNodeTree

    //------------------------------------------------------------
    // Public Methods Section.
    //------------------------------------------------------------
//    void setRootData(const ItemType& newData) ;
    bool add(const ItemType& newEntry) ;
//    bool remove(const ItemType& anEntry) ;
//    ItemType getEntry(const ItemType& anEntry) const;
//    bool contains(const ItemType& anEntry) const;
    void showTree();
    void neoShowTree(std::shared_ptr<BinaryNode<ItemType>> thisRoot);

    BinarySearchTree(const ItemType& rootItem,
                   const std::shared_ptr<BinarySearchTree<ItemType>> leftTreePtr,
                   const std::shared_ptr<BinarySearchTree<ItemType>> rightTreePtr);

    BinarySearchTree(const ItemType &rootItem);



}; // end BinarySearchTree

// add function implementations below

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem,
                                         const std::shared_ptr<BinarySearchTree<ItemType>> leftTreePtr,
                                         const std::shared_ptr<BinarySearchTree<ItemType>> rightTreePtr)


{
//    this->rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem,
//                                                         copyTree(leftTreePtr->rootPtr),
//                                                         copyTree(rightTreePtr->rootPtr)));
    this->rootPtr = std::make_shared<BinaryNode<ItemType>>(rootItem, this->copyTree(leftTreePtr->rootPtr), this->copyTree(rightTreePtr->rootPtr));
//    this->copyTree(leftTreePtr->rootPtr);
//    this->copyTree(rightTreePtr->rootPtr);

}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
//    auto newNode = std::shared_ptr<BinaryNode<ItemType>> (newEntry);
    std::shared_ptr<BinaryNode<ItemType>> newNode = std::make_shared<BinaryNode<ItemType>>(newEntry, nullptr, nullptr);
    std::shared_ptr<BinaryNode<ItemType>> thisRoot = this->rootPtr;
//    BinaryNode<ItemType>*  newNode = new BinaryNode<ItemType>(newEntry);
    placeNode(thisRoot, newNode);
    return true;
}  // end destroyTree

template<class ItemType>
void BinarySearchTree<ItemType>::showTree()
{
    std::cout << std::endl;
    std::cout << this->getRootData();
    std::cout << this->rootPtr->getLeftChildPtr()->getItem();
    std::cout << this->rootPtr->getRightChildPtr()->getItem();
//    std::cout << this->rootPtr->getRightChildPtr()->getRightChildPtr()->getItem();
    std::cout << std::endl;
    std::cout << " ---- " << std::endl;
}  // end destroyTree

template<class ItemType>
void BinarySearchTree<ItemType>::neoShowTree(std::shared_ptr<BinaryNode<ItemType>> thisRoot)
{
    while (this->rootPtr != nullptr) {

    }
}



template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem){
    this->setRootData(rootItem);
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                      std::shared_ptr<BinaryNode<ItemType>> newNode) {
    if (subTreePtr == nullptr) {
        std::cout << "subTreePtr is NULL " << std::endl;
        return newNode;
    } else {
        std::cout << "subTreePtr getItem - " << subTreePtr->getItem() << std::endl;
        auto leftTreePtr = subTreePtr->getLeftChildPtr();
        auto rightTreePtr = subTreePtr->getRightChildPtr();
        if (subTreePtr->getItem() > newNode->getItem()) {
            leftTreePtr = placeNode(leftTreePtr, newNode);
            subTreePtr->setLeftChildPtr(leftTreePtr);
        } else {
            rightTreePtr = placeNode(rightTreePtr, newNode);
            std::cout << "subTreePtr " << subTreePtr->getItem() << " right pointing to " << rightTreePtr->getItem() << std::endl;
//            std::cout << rightTreePtr->getItem() << std::endl;
            subTreePtr->setRightChildPtr(rightTreePtr);
        }
    }


    return subTreePtr;
}
// end constructor


#endif //REMIXLAB6_BINARYSEARCHTREE_H
