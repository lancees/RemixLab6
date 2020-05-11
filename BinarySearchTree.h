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

    std::shared_ptr<BinaryNode<ItemType>> findParentNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
                                                   const ItemType& target, std::shared_ptr<BinaryNode<ItemType>> parentPtr) const;

public:
    BinarySearchTree(const ItemType& rootItem,
                     const std::shared_ptr<BinarySearchTree<ItemType>> leftTreePtr,
                     const std::shared_ptr<BinarySearchTree<ItemType>> rightTreePtr);


    BinarySearchTree(const ItemType &rootItem);
    BinarySearchTree();

//    void setRootData(const ItemType& newData) ;
    bool add(const ItemType& newEntry) ;
    bool remove(const ItemType& anEntry) ;
    ItemType getEntry(const ItemType& anEntry) const;
    bool contains(const ItemType& anEntry) const;
    std::shared_ptr<BinaryNode<ItemType>> getRootPtr() const;
    void removeSmallest();
    void showTree(std::shared_ptr<BinaryNode<ItemType>> thisRoot);
    std::shared_ptr<BinaryNode<ItemType>> getParentNodeOf(const ItemType& newEntry) const;



}; // end BinarySearchTree

// add function implementations below
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() { }

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem,
                                         const std::shared_ptr<BinarySearchTree<ItemType>> leftTreePtr,
                                         const std::shared_ptr<BinarySearchTree<ItemType>> rightTreePtr)
{
    this->rootPtr = std::make_shared<BinaryNode<ItemType>>(rootItem, this->copyTree(leftTreePtr->rootPtr), this->copyTree(rightTreePtr->rootPtr));
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem){
    this->setRootData(rootItem);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
    std::shared_ptr<BinaryNode<ItemType>> newNode = std::make_shared<BinaryNode<ItemType>>(newEntry, nullptr, nullptr);
    std::shared_ptr<BinaryNode<ItemType>> thisRoot = this->rootPtr;
    if (thisRoot == nullptr) {
        this->setRootData(newEntry);
    } else {
        placeNode(thisRoot, newNode);
    }
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &anEntry) {
    bool f = false;
//    removeValue(getRootPtr(), anEntry, f);
    auto node = findNode(this->getRootPtr(), anEntry);
    std::cout << " Removing Node with entry " << anEntry << std::endl;
    removeNode(node);
    return true;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const {
    auto binaryNodePtr = findNode(this->rootPtr, anEntry);

    if (binaryNodePtr != nullptr)
        return binaryNodePtr->getItem();
    else
        throw NotFoundException("Entry not found in tree!");
}  // end getEntry

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const {
    if (findNode(this->rootPtr, anEntry) != nullptr) {
        return true;
    } else {
        return false;
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::getRootPtr() const {
    return this->rootPtr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::showTree(std::shared_ptr<BinaryNode<ItemType>> thisRoot)
{
    if (thisRoot != nullptr) {
//        std::cout << thisRoot->getItem() << " ";
//        showTree(thisRoot->getLeftChildPtr());
//        showTree(thisRoot->getRightChildPtr());

        showTree(thisRoot->getLeftChildPtr());
        std::cout << thisRoot->getItem() << " ";
        showTree(thisRoot->getRightChildPtr());
    }

}

template<class ItemType>
void BinarySearchTree<ItemType>::removeSmallest()
{
    int i = 0;
//    std::cout << "Attempting to remove smallest" << std::endl;
    removeLeftmostNode(this->getRootPtr(), i);
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                      std::shared_ptr<BinaryNode<ItemType>> newNode) {
    if (subTreePtr == nullptr) {
//        std::cout << "subTreePtr is NULL " << std::endl;
        return newNode;
    } else {
//        std::cout << "subTreePtr getItem - " << subTreePtr->getItem() << std::endl;
        auto leftTreePtr = subTreePtr->getLeftChildPtr();
        auto rightTreePtr = subTreePtr->getRightChildPtr();
        if (subTreePtr->getItem() > newNode->getItem()) {
            leftTreePtr = placeNode(leftTreePtr, newNode);
            subTreePtr->setLeftChildPtr(leftTreePtr);
        } else {
            rightTreePtr = placeNode(rightTreePtr, newNode);
//            std::cout << "subTreePtr " << subTreePtr->getItem() << " right pointing to " << rightTreePtr->getItem() << std::endl;
//            std::cout << rightTreePtr->getItem() << std::endl;
            subTreePtr->setRightChildPtr(rightTreePtr);
        }
    }
    return subTreePtr;
}



template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target,
                                        bool &success) {
    if(subTreePtr == nullptr) // not found here
        return subTreePtr;

    if (subTreePtr->getItem() == target) // found it
    {
        subTreePtr = this->moveValuesUpTree(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        auto targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(targetNodePtr);
        if (!success) // no need to search right subTree
        {
            targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
            subTreePtr->setRightChildPtr(targetNodePtr);
        }  // end if

        return subTreePtr;
    }  // end if

    return std::shared_ptr<BinaryNode<ItemType>>();
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr) {
    // move bubble down and then delete
    auto leftNode = nodePtr->getLeftChildPtr();
    auto rightNode = nodePtr->getRightChildPtr();

    if (rightNode == nullptr && leftNode == nullptr) {
        return nodePtr;
    } else if (rightNode != nullptr) {
        nodePtr->setItem(rightNode->getItem());
        if (rightNode->isLeaf()) {
            nodePtr->setRightChildPtr(nullptr);
        }
        removeNode(rightNode);
    } else if (leftNode != nullptr) {
        nodePtr->setItem(leftNode->getItem());
        if (leftNode->isLeaf()) {
            nodePtr->setLeftChildPtr(nullptr);
        }
        removeNode(leftNode);
    }
    return nodePtr;
//    std::shared_ptr<BinaryNode<ItemType>> newNode;
    if (nodePtr == this->getRootPtr()) {
//        auto leftNode = nodePtr->getLeftChildPtr();
//        auto rightNode = nodePtr->getRightChildPtr();
//        if (rightNode != nullptr) {
//            newNode = std::make_shared<BinaryNode<ItemType>>(rightNode->getItem(), nodePtr->getLeftChildPtr(),
//                    rightNode->getRightChildPtr());
//            this->rootPtr = newNode;
//            removeNode(rightNode);
//        } else if (leftNode != nullptr) {
////            newNode->setItem(leftNode->getItem());
////            newNode->setLeftChildPtr(leftNode->getLeftChildPtr());
////            newNode->setRightChildPtr(leftNode->getRightChildPtr());
////            this->rootPtr = newNode;
////            removeNode(leftNode);
//        }
    }
    else if (nodePtr != nullptr) {
        std::cout <<" Trying to remove a subright node " << nodePtr->getItem() <<  std::endl;

        auto parentNode = findParentNode(this->getRootPtr(), nodePtr->getItem(), nullptr);
        auto leftNode = nodePtr->getLeftChildPtr();
        auto rightNode = nodePtr->getRightChildPtr();

        if (rightNode != nullptr) {
//            newNode = std::make_shared<BinaryNode<ItemType>>(rightNode->getItem(), nodePtr->getLeftChildPtr(),
//                                                             rightNode->getRightChildPtr());
//            this->rootPtr = newNode;
//            removeNode(rightNode);
        } else {
//            newNode->setItem(leftNode->getItem());
//            newNode->setLeftChildPtr(leftNode->getLeftChildPtr());
//            newNode->setRightChildPtr(leftNode->getRightChildPtr());
//            removeNode(leftNode);
        }
    }
    return nodePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                               ItemType &inorderSuccessor) {
    auto thisTreePtr = subTreePtr;
    while (subTreePtr != nullptr) {
        thisTreePtr = subTreePtr;
        subTreePtr = subTreePtr->getLeftChildPtr();
    }
    inorderSuccessor = thisTreePtr->getItem();
    std::cout << " (removing left most node " << thisTreePtr->getItem() << " )" << std::endl;
    removeNode(thisTreePtr);
    return thisTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType &target) const {
    if (treePtr == nullptr) {
        return nullptr;
    } else {
        if (treePtr->getItem() == target) {
            return treePtr;
        } else if (target < treePtr->getItem()) {
            return findNode(treePtr->getLeftChildPtr(), target);
        } else {
            return findNode(treePtr->getRightChildPtr(), target);
        }
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>>
BinarySearchTree<ItemType>::findParentNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType &target, std::shared_ptr<BinaryNode<ItemType>> parentPtr) const {
//    std::cout << "Looking for " << target << std::endl;
    if (treePtr == nullptr || (parentPtr == nullptr && treePtr->getItem() == target)) {
        return nullptr;
    } else {
        if (treePtr->getItem() == target) {
            return parentPtr;
        } else if (target < treePtr->getItem()) {
//            std::cout << "finding " << target << std::endl;
            return findParentNode(treePtr->getLeftChildPtr(), target, treePtr);
        } else {
            return findParentNode(treePtr->getRightChildPtr(), target, treePtr);
        }
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::getParentNodeOf(const ItemType &anEntry) const {
//    return std::shared_ptr<BinaryNode<ItemType>>();
    return findParentNode(this->rootPtr, anEntry, nullptr);
}





#endif //REMIXLAB6_BINARYSEARCHTREE_H
