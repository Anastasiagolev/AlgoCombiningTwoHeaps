//
//  BinaryNodeTree.h
//  Goleva_a09
//
//  Created by Anastasia Golev on 12/5/20.
//

#include <iostream>
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"
#ifndef BinaryNodeTree_h
#define BinaryNodeTree_h
using namespace std;
//link-based binary BinaryNodeTree
template<class T>
class BinaryNodeTree{
private:
    BinaryNode<T>* root;
    //recursive helper methods
    //returns the height of BinaryNodeTree
    int gHeiHlp( BinaryNode<T>* subtree ) const{
        //check if BinaryNodeTree is empty
        if (subtree == nullptr ){ return 0; }
        //else not empty, recursively call gHeiHlp
        else {
//            height is atleast one + the max of left or right subtree
            return 1 + max(gHeiHlp(subtree->lChild), gHeiHlp(subtree->rChild));
        }
    }
    //returns the number of nodes in a BinaryNodeTree
    int gNumOfNodesHlp( BinaryNode<T>* subtree ) const{
        //check if BinaryNodeTree is empty
        if ( subtree == nullptr ) { return 0; }
        //else the BinaryNodeTree is not empty, recursively call gNumofNodesHlp
        else {
            return 1 + gNumOfNodesHlp(subtree->lChild)+gNumOfNodesHlp(subtree->rChild);
        }
    }
    
    //adds nodes to a BinaryNodeTree using balanced method
    BinaryNode<T>* balancedAdd( BinaryNode<T>*& subtree, BinaryNode<T>* nNode ){
        //check if BinaryNodeTree is empty
        if ( subtree == nullptr ){ return nNode; } //base case
        //recursive case
        else{
            //create BinaryNode pointers to lChild and rChild
            BinaryNode<T>* lptr = subtree->lChild;
            BinaryNode<T>* rptr = subtree->rChild;
            //check case in which left subtree is taller than right subtree
            if ( gHeiHlp(lptr) > gHeiHlp(rptr)){
                //expand right subtree recursively using balancedAdd
                rptr = balancedAdd(rptr, nNode);
                //connect the right subtree with new node
                subtree->rChild=rptr;
            }
            //else right subtree is taller
            else{
                //expand left subtree recursively using balancedAdd
                lptr = balancedAdd(lptr, nNode);
                //connnect left subtree with new node
                subtree->lChild=lptr;
            }
        }
        return subtree;
    }
    
    //cpyTree function copies an existing BinaryNodeTree
    BinaryNode<T>* cpyTree( const BinaryNode<T>* oldRt ) const{
        //create BinaryNode pointer nroot, set to nullptr
        BinaryNode<T>* nroot = nullptr;
        //check if original BinaryNodeTree is not empty
        if (oldRt != nullptr){
            //set nroot to point to new node which will be the root of copied BinaryNodeTree with left and right child empty
            nroot= new BinaryNode<T>(oldRt->item, nullptr, nullptr);
            //recursively call cpyTree to copy left and right side of original BinaryNodeTree
            nroot->lChild = cpyTree(oldRt->lChild);
            nroot->rChild = cpyTree(oldRt->rChild);
        }
        //return the new BinaryNodeTree
        return nroot;
    }
    //function destroyTree deletes an existing BinaryNodeTree
    void destroyTree( BinaryNode<T>*& subtree ){
        //check if BinaryNodeTree is not empty
        if ( subtree != nullptr ){
            //recursively call destroyTree to left and right subtrees
            destroyTree(subtree->lChild);
            destroyTree(subtree->rChild);
            //delete the node subtree
            delete subtree;
            //set subtree pointer to nullptr to disconnect
            subtree = nullptr;
        }
    }
    
    //traversal methods
    //function preorder performs a preorder traversal of a BinaryNodeTree, VLR
    void preorder( void visit ( T& ), BinaryNode<T>* BinaryNodeTree ) const{
        //check if the BinaryNodeTree is not empty, aka has nodes
        if (BinaryNodeTree != nullptr){
            //create a T variable to save the value inside the root
            T item = BinaryNodeTree->item;
            //visit function called to get the value inside the root
            visit( item );
            //call function preorder recursively for left and right side
            preorder(visit, BinaryNodeTree->lChild );
            preorder(visit, BinaryNodeTree->rChild );
        }
    }
    //function inorder performs a inorder traversal of a BinaryNodeTree, LVR
    void inorder( void visit ( T& ), BinaryNode<T>* BinaryNodeTree ) const{
        //check if the BinaryNodeTree is not empty, aka has nodes
        if (BinaryNodeTree != nullptr){
            //since inorder traversal is LVR, we begin with recursively calling function inorder for the left side
            inorder(visit, BinaryNodeTree->lChild);
            //create a T variable to save the value inside the root
            T item = BinaryNodeTree->item;
            //visit function called to get the value inside the root
            visit( item );
            //call function inorder recursively for the right side
            inorder(visit, BinaryNodeTree->rChild);
        }
    }
    //function postorder performs a postorder traversal of a BinaryNodeTree, LRV
    void postorder( void visit ( T& ), BinaryNode<T>* BinaryNodeTree ) const{
        //check if the BinaryNodeTree is not empty, aka has nodes
        if (BinaryNodeTree != nullptr){
            //since postorder traversal is LRV, we begin with recursively calling function postorder for the left side
            postorder(visit, BinaryNodeTree->lChild);
            //call function postorder recursively for the right side
            postorder(visit, BinaryNodeTree->rChild);
            //create a T variable to save the value inside the root
            T item = BinaryNodeTree->item;
            //visit function called to get the value inside the root
            visit(item);
        }
    }
    //Removes the target value from the subtree by calling myValUp() to overwrite value with the value from child
    BinaryNode<T>* removeNode( BinaryNode<T>* subtree, const T& tgt, bool& success ){
        if ( subtree == nullptr ){ return nullptr; }
        if ( subtree->item == tgt ){
            subtree = myValUp (subtree);
            success = true;
            return subtree;
        }
        else {
            BinaryNode<T>* tgtNodePtr = removeNode( subtree->lChild, tgt, success);
            subtree->lChild = tgtNodePtr;
            if (!success){
                tgtNodePtr = removeNode(subtree->rChild, tgt, success);
                subtree->rChild = tgtNodePtr;
            }
            return subtree;
        }
    }
    
    //Copies values up BinaryNodeTree to overwrite values in current node until a leaf is reached; the leaf is then removed, since its value is now stored in the parent
    BinaryNode<T>* myValUp( BinaryNode<T>* subtree ){
        BinaryNode<T>* lptr = subtree->lChild;
        BinaryNode<T>* rptr = subtree->rChild;
        int lheight = gHeiHlp(lptr);
        int rheight = gHeiHlp(rptr);
        if (lheight > rheight){
            subtree->item = lptr->item;
            lptr = myValUp(lptr);
            subtree->lChild = lptr;
            return subtree;
        }
        else {
            if (rptr != nullptr){
                subtree->item = rptr->item;
                rptr = myValUp(rptr);
                subtree->rChild = rptr;
                return subtree;
            }
            else {
                delete subtree;
                return nullptr;
            }
        }
    }
    
public:
    //constructors and destructors
    BinaryNodeTree() : root(nullptr){}; //deault ctor
    BinaryNodeTree( const T& rtItem ) : root(new BinaryNode<T>(rtItem, nullptr, nullptr)){} //1 param ctor
    BinaryNodeTree( const T& rtItem, const BinaryNode<T>*& lTr, const BinaryNode<T>*& rTr ) : root( new BinaryNode<T>(rtItem, cpyTree(lTr->root), cpyTree(rTr->root))){} //3 param ctor
    BinaryNodeTree ( const BinaryNodeTree<T>& rhs ){ root = cpyTree(rhs.root); } //copy ctor
    ~BinaryNodeTree() { destroyTree(root); } //dctor
    
    //other methods
    bool isEmpty() const { return root == nullptr; } //tests whether a BinaryNodeTree is empty
    int getHeight() const { return gHeiHlp(root); } //returns the height of BinaryNodeTree using gHeiHlp
    int getNumberOfNodes() const { return gNumOfNodesHlp(root); } //returns the number of nodes in a BinaryNodeTree using gNumOfNodesHlp
    
    //returns the value inside the root is BinaryNodeTree is not empty, if empty error message is shown
    T getRootData() const throw (PrecondViolatedExcept){
        if (root == NULL){ throw (PrecondViolatedExcept("getRootData() called with an empty BinaryNodeTree.")); }
        else { return root->item; }
    }
    
    //function setRootData sets the root value
    void setRootData( const T& nData ){
        if ( root == NULL ) { root = new BinaryNode<T>(nData); } //call ctor to create root
        else { root->item = nData; } //set root node to value of nData
    }
    //function add will add nodes to a BinaryNodeTree
    bool add( const T& nData ){
        //create BinaryNode pointer nn to point to new BinaryNode with value of nData aka create a node
        BinaryNode<T>* nn = new BinaryNode<T>(nData);
        //connect new node to BinaryNodeTree using balancedAdd function
        root = balancedAdd(root, nn);
        return true;
    }
    //function remove will remove nodes from a BinaryNodeTree
    bool remove( const T& tgt ){
        bool canRmv = false;
        root = removeNode(root, tgt, canRmv);
        return canRmv;
    }
    //function clear will delete a BinaryNodeTree
    void clear() { destroyTree(root); root=nullptr; }
    
    /* BinaryNode<T>* function findNode will traverse the BinaryNodeTree recursively to find node that is equivalent to target value, or return a nullptr if target value is not found during traversal */
    BinaryNode<T>* findNode( BinaryNode<T>* subtree, const T& tgt ) const{
        //check if subtree is empty, if it is return nullptr
        if (subtree == nullptr){ return nullptr; }
        //if root value is equivalent to target value, return the root
        else if (subtree->item == tgt ){ return subtree; }
        //if root value is greater than target value, recursively call function findNode to traverse left side
        else if (subtree->item > tgt ){ return findNode(subtree->lChild, tgt); }
        //else root value is less than target value, recursively call function findNode to traverse right side
        else { return findNode(subtree->rChild, tgt); }
    }
    
    //function getEntry will return the node containing an entry given in parameter
    T getEntry( const T& anEntry ) const throw( NotFoundExcept ){
        BinaryNode<T>* nd = findNode(root, anEntry);
        if (nd == nullptr ){ throw NotFoundExcept( "Entry not found in BinaryNodeTree."); }
        else { return nd->item; }
    }
    //function contains tests if BinaryNodeTree contains parameter value
    bool contains( const T& anEntry ) const { return find( root, anEntry ); }
    
    void preTrav( void visit( T& )) const { preorder( visit, root ); }
    void inTrav( void visit( T& )) const { inorder( visit, root ); }
    void postTrav( void visit( T& )) const { postorder( visit, root ); }
    
};

//visit function outputs item in node
template <class T>
void visit( T& item ){ cout<< item << " "; }


#endif /* BinaryNodeTree_h */
