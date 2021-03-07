//
//  BinaryNode.h
//  Goleva_a09
//
//  Created by Anastasia Golev on 12/5/20.
//

#ifndef BinaryNode_h
#define BinaryNode_h

//Binary tree node class BinaryNode, or Binary Node
template<class T>
class BinaryNode{
public:
    T item;
    BinaryNode<T>* lChild; //left child
    BinaryNode<T>* rChild; //right child
    BinaryNode() : lChild(nullptr), rChild(nullptr){} //default ctor
    BinaryNode( const T& anItem ) : item(anItem), lChild(nullptr), rChild(nullptr){} //1 param ctor
    BinaryNode( const T& anItem, BinaryNode<T>* left, BinaryNode<T>* right) : item(anItem), lChild(left), rChild(right){} //3 param ctor
    bool isLeaf() const{ if (lChild==nullptr && rChild == nullptr ) return true; else return false; } //checks if node is a leaf
};
#endif /* BinaryNode_h */
