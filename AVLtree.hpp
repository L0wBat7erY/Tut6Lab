//
//  AVLtree.hpp
//  Tut6Lab
//
//  Created by macOS Sierra on 11/8/17.
//  Copyright © 2017 macOS Sierra. All rights reserved.
//

#ifndef AVLtree_hpp
#define AVLtree_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

enum BFactor {EH=0, LH=-1, RH=1};

template<class T>
struct AVLnode
{
    T data; BFactor b;
    AVLnode<T>* pleft, *pright;
    AVLnode(T&a): data(a), b(EH), pleft(NULL), pright(NULL){};
    AVLnode(T&a, AVLnode<T>* pleft, AVLnode<T>* pright): data(a), b(EH), pleft(pleft), pright(pright){};
};

template<class T>
class AVL
{
    AVLnode<T>* pRoot;
    
    void    rotRight(AVLnode<T>*& pRoot);
    void    rotLeft(AVLnode<T>*& pRoot);
    void    rotLR(AVLnode<T>*& pRoot);
    void    rotRL(AVLnode<T>*& pRoot);
    bool    balanceleft(AVLnode<T>*& pRoot);
    bool    balanceright(AVLnode<T>*& pRoot);
    bool    insert(T& a, AVLnode<T>*& pRoot);
    bool    remove1(T&a, AVLnode<T>*& pRoot);
    bool    remove(T&a, AVLnode<T>*& pRoot);
    void    traverseNLR(AVLnode<T>* pRoot);
    void    traverseLNR(AVLnode<T>* pRoot);
    bool    search(T a, AVLnode<T>* pRoot);
    T*      find(T&a, AVLnode<T>* pRoot);
public:
    
    AVL() : pRoot(NULL) {}
    ~AVL(){}
    
    bool    insertAVLtree(T& a);
    bool    removeNodeAVLtree(T&a);
    void    traverseNLR_AVLtree();
    void    traverseLNR_AVLtree();
    bool    searchDataAVLtree(T a);
    T*      findDataAVLtree(T& a);
    
};



#endif /* AVLtree_hpp */
