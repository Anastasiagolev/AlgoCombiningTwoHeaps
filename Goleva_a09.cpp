//
//  Goleva_a09.cpp
//
//  Created by Anastasia Golev on 12/3/20.
//

#include <iostream>
#include <string>
#include <stdexcept>

#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

using namespace std;


/* This  algorithm combines two arbitrary-sized heaps into one heap. The Big Oh performance for this step will be O(logn). Since O(n+m) > O(logn), the Big Oh performance for the algorithm will be O(n*m). */

 //maxHeap function maxHeap will recursively create a maxheap using three parameters, and integer array, integer idx which represents index and int n which represents the size of the array
void maxHeap( int arr[], int idx, int n){
    //if a node is at index i, then its left child is at 2i+1, its right child is at 2i+2
    //create integer variables to represent left and right child
    int lChildIdx = 2 * idx + 1;
    int rChildIdx = lChildIdx + 1;
    
    //create an integer variable maxIdxto represent the max index, which we will use for comparisons and swaping
    int maxIdx;
    
    //begin sorting the array comparing the values at the left and right children of given index
    //first we check if the left and right child is within the bounds of the array
    if ((lChildIdx < n) && (rChildIdx < n)){
        //then we check if the value at the left child index is greater than the value at the given index
        if (arr[lChildIdx] > arr[idx])
        {
            // if it is then set the maximum to the lChild index, to be the new root
                maxIdx = lChildIdx;
        }
        
        //then we check if the value at the right child index is greater than the value at the given index
        else if (arr[rChildIdx] > arr[idx] )
        {
             // if it is then set the maximum to the rChild index, to be the new root
                maxIdx = rChildIdx;
            
        }
        //else the given index holds the maximum value, set it to maxIdx
        else {
            maxIdx = idx;
        }
    }
    
    //once the maximum index is found, we swap it with the given index in the array
    swap(arr[maxIdx], arr[idx]);
    //to continue traversing the array, we recursively call maxHeap
    maxHeap(arr, n, maxIdx);
}

//function createHeap will take two parameters, an integer array[], and integer n which represents the size of the array
void createHeap( int arr[], int n){
    //since the leaf nodes are already heaps, we start from the second level down and work our way up
    int startingLevel = ((n/2)-1); //will give start us at the level of the parents of the leaf nodes
    
    //begin traversing the array, since we are working with an array, we want to reach index 0, so we traverse using a for loop decreasing i. Call function maxHeap to create the heap from the starting level, working up the array
    for ( int i = startingLevel; i >= 0; i--){ maxHeap(arr, n, i);}
}

//function mergeArrays will take 4 parameters, two integer arrays which represents heaps, and two integer variables, the sizes of the arrays
void mergeArrays( int arr1[], int arr2[], int size1, int size2){
    //create an integer array which will be used to merge the two heaps
    int nArray[size1+size2+1];
    
    //copy the elements from arr1 to nArray
    for (int i = 0; i < size1; i++){ nArray[i] = arr1[i]; }
    
    //copy the elements from arr2 to nArray starting at the index at which we finished copying arr1, which would be size1
    for (int j = 0; j < size2; j++){ nArray[j+size1] = arr2[j]; }
    
    //after all the elements have been copied from our two heaps into nArray build the max heap by calling function createHeap
    createHeap(nArray, size1+size2);
    
}


/* ************************* Q3 *******************************  */
template< class T>
class BinarySearchTree : public BinaryNodeTree<T>
{
private:
BinaryNode<T>* rootPtr;
protected:
//------------------------------------------------------------
// Protected Utility Methods Section:
// Recursive helper methods for the public methods.
//------------------------------------------------------------
// Recursively finds where the given node should be placed and
// inserts it in a leaf at that point.
    BinaryNode<T>* insertInorder(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNode);
// Removes the given target value from the tree while maintaining a
// binary search tree.
    BinaryNode<T>* removeValue(BinaryNode<T>* subTreePtr, const T target, bool& success);
// Removes a given node from a tree while maintaining a
// binary search tree.
    BinaryNode<T>* removeNode(BinaryNode<T>* nodePtr); //implemented
// Removes the leftmost node in the left subtreePtr of the node
// pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node.
// Returns a pointer to the revised subtreePtr.
    BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* subTreePtr, T& inorderSuccessor);
// Returns a pointer to the node containing the given value,
// or nullptr if not found.
    BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T& target) const;
    BinaryNode<T>* cpyTree( const BinaryNode<T>* oldRt ) const;
public:
//------------------------------------------------------------
// Constructor and Destructor Section.
//------------------------------------------------------------
    BinarySearchTree();
    BinarySearchTree( const T& rootItem);
    BinarySearchTree( const BinarySearchTree<T>& tree);
    virtual ~BinarySearchTree();
//------------------------------------------------------------
// Public Methods Section.
//------------------------------------------------------------
    bool isEmpty() const { return rootPtr == nullptr; }
    int getHeight() const { return gHeiHlp(rootPtr); }
    int getNumberOfNodes() const;
    T getRootData() const throw(PrecondViolatedExcept);
    void setRootData( const T& newData) const throw(PrecondViolatedExcept);
    bool add( const T& newEntry);
    bool remove( const T& anEntry);
    void clear();
    T getEntry( const T& anEntry) const throw(NotFoundExcept);
    bool contains( const T& anEntry) const;
//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------
    void preorderTraverse(void visit(T&)) const;
    void inorderTraverse(void visit(T&)) const;
    void postorderTraverse(void visit(T&)) const;
//------------------------------------------------------------
// Overloaded Operator Section.
//------------------------------------------------------------
    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& rightHandSide){
        if (!isEmpty()){ clear();}
        this->rootPtr=cpyTree(rightHandSide.rootPtr);
        return *this;
        }
}; // end BinarySearchTree


//Definitions

// Recursively finds where the given node should be placed and
// inserts it in a leaf at that point.
template <class T>
BinaryNode<T>* BinarySearchTree<T> :: insertInorder(BinaryNode<T>* subTreePtr, BinaryNode<T>* newNode){
    //we will use recursion
    if (subTreePtr == nullptr) { return newNode; }
    else {
        if ((subTreePtr->item) == newNode->item){ return subTreePtr; }
        else if ((subTreePtr->item) > newNode->item){ subTreePtr->lChild = insertInorder(subTreePtr->lChild, newNode); }
        else { subTreePtr->rChild = insertInorder(subTreePtr->rChild, newNode); }
    }
    return subTreePtr;
}

template < class T >
BinaryNode<T>* BinarySearchTree<T> :: removeValue(BinaryNode<T>* subTreePtr, const T target, bool& success){
    if ( subTreePtr == nullptr ){ return nullptr; }
    if ( subTreePtr->item == target ){
        subTreePtr = myValUp (subTreePtr);
        success = true;
        return subTreePtr;
    }
    else {
        BinaryNode<T>* targetNodePtr = rmvVal( subTreePtr->lChild, target, success);
        subTreePtr->lChild = targetNodePtr;
        if (!success){
            targetNodePtr = rmvVal(subTreePtr->rChild, target, success);
            subTreePtr->rChild = targetNodePtr;
        }
        return subTreePtr;
    }
}

// Removes the leftmost node in the left subtreePtr of the node
// pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node.
// Returns a pointer to the revised subtreePtr.
template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* subTreePtr, T& inorderSuccessor){
    //we must move completely left
    //a node with two children
    if ( subTreePtr == nullptr ) return nullptr;
    BinaryNode<T>* curr = subTreePtr; //points to the same root
    while (curr->lChild != nullptr ) { curr = curr->lChild; }
    //after we've found the leftmost node, delete it
    removeNode(curr);
    //set inorderSuccessor to the tree
    curr = insertInorder(subTreePtr, inorderSuccessor);
}

// Returns a pointer to the node containing the given value,
// or nullptr if not found.
template <class T>
BinaryNode<T>* BinarySearchTree<T> :: findNode(BinaryNode<T>* treePtr, const T& target) const{
    //check if tree is empty, if so then we return a nullptr
    if (treePtr == nullptr ){ return nullptr; }
    //else if the root value is the target value then we return treePtr
    else if ( treePtr->item == target ){ return treePtr; }
    //else the tree is not empty and we traverse the tree to find the tgt node
    else{
        //if the target value is greater than the root value, then we go to the right subtree
        if ( treePtr->item < target) { treePtr = findNode(treePtr->rChild, target); }
        //else the target value is less than the root value, we go to the left subtree
        else{
            treePtr = findNode(treePtr->lChild, target);
        }
    }
    return treePtr;
}


int main() {
    
}
