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
    AVLnode<T>* proot;
public:
    AVL() : proot(NULL) {}
    ~AVL(){}
    
    AVLnode<T>*& getnode(){
        return proot;
    }
    
    void    rotRight(AVLnode<T>*& pr);
    void    rotLeft(AVLnode<T>*& pr);
    void    rotLR(AVLnode<T>*& pr);
    void    rotRL(AVLnode<T>*& pr);
    bool    balanceleft(AVLnode<T>*& pr);
    bool    balanceright(AVLnode<T>*& pr);
    bool    insert(T& a, AVLnode<T>*& pr);
    bool    remove1(T&a, AVLnode<T>*& pr);
    bool    remove(T&a, AVLnode<T>*& pr);
    bool    searchAVL(T&a, AVLnode<T>* pr);
    void    traverseNLR(AVLnode<T>* pr);
    void    traverseLNR(AVLnode<T>* pr);
};

template<class T>
void AVL<T>::rotRight(AVLnode<T>*& pr)
{
    if(pr==NULL) return;
    if(pr->pleft==NULL) return;
    AVLnode<T>* p = pr->pleft;
    pr->pleft = p->pright;
    p->pright = pr;
    pr=p;
};

template<class T>
void AVL<T>::rotLeft(AVLnode<T>*& pr)
{
    if(pr==NULL) return;
    if(pr->pright==NULL) return;
    AVLnode<T>* p = pr->pright;
    pr->pright = p->pleft;
    p->pleft = pr;
    pr=p;
}

template<class T>
void AVL<T>::rotLR(AVLnode<T>*& pr)
{
    rotLeft(pr->pleft);
    rotRight(pr);
}

template<class T>
void AVL<T>::rotRL(AVLnode<T>*& pr)
{
    rotRight(pr->pright);
    rotLeft(pr);
}

template<class T>
bool AVL<T>::balanceleft(AVLnode<T>*& pr)
{
    if(pr->b==EH) { pr->b=LH; return true; }
    if(pr->b==RH) { pr->b=EH; return false; }
    if(pr->pleft->b==LH){
        rotRight(pr);
        pr->b=pr->pright->b=EH;
        return false;
    }
    rotLR(pr);
    if(pr->b==LH){
        pr->b=pr->pleft->b=EH;
        pr->pleft->b=RH;
        return false;
    }
    pr->b=pr->pright->b=EH;
    pr->pleft->b=LH;
    return false;
}

template<class T>
bool AVL<T>::balanceright(AVLnode<T>*& pr)
{
    if(pr->b==EH) { pr->b=RH; return true; }
    if(pr->b==LH) { pr->b=EH; return false; }
    if(pr->pright->b==RH){
        rotLeft(pr);
        pr->b=pr->pleft->b=EH;
        return false;
    }
    rotRL(pr);
    if(pr->b==RH){
        pr->b=pr->pright->b=EH;
        pr->pright->b=LH;
        return false;
    }
    pr->b=pr->pleft->b=EH;
    pr->pright->b=RH;
    return false;
}

template<class T>
bool AVL<T>::insert(T& a, AVLnode<T>*& pr)
{
    if(pr==NULL) { pr = new AVLnode<T>(a); return true; }
    if(a<pr->data)
    {
        if(insert(a, pr->pleft)==false) return false;
        return balanceleft(pr);
    }
    else
    {
        if(insert(a, pr->pright)==false) return false;
        return balanceright(pr);
    }
}

template <class T>
void AVL<T>::traverseNLR(AVLnode<T>* pr)
{
    if (pr != NULL)
    {
        cout << pr->data << " ";
        traverseNLR(pr->pleft);
        traverseNLR(pr->pright);
    }
}

template <class T>
void AVL<T>::traverseLNR(AVLnode<T>* pr)
{
    if(pr!=NULL)
    {
        traverseLNR(pr->pleft);
        cout << pr->data << " ";
        traverseLNR(pr->pright);
    }
    return;
}

template<class T>
bool AVL<T>::remove(T &a, AVLnode<T> *&pr)
{
    if(pr==NULL) return false;
    if(a<pr->data)
    {
        if(remove(a, pr->pleft)==false) return false;
        if(pr->b==LH) { pr->b=EH; return true; }
        if(pr->b==EH) { pr->b=RH; return false; }
        return !balanceright(pr);
    }
    if(a>pr->data)
    {
        if(remove(a, pr->pright)==false) return false;
        if(pr->b==RH) { pr->b=EH; return true; }
        if(pr->b==EH) { pr->b=LH; return false; }
        return !balanceleft(pr);
    }
    if(pr->pleft==NULL && pr->pright==NULL)
    {
        delete pr; pr=NULL; return true;
    }
    if(pr->pleft==NULL)
    {
        AVLnode<T>* p=pr;
        pr=pr->pright;
        delete p; p=NULL;
        return true;
    }
    if(pr->pright==NULL)
    {
        AVLnode<T>* p=pr;
        pr=pr->pleft;
        delete p; p=NULL;
        return true;
    }
    AVLnode<T>* p=pr->pright;
    while(p->pleft) p = p->pleft;
    pr->data = p->data;
    if(remove(p->data, pr->pright))
    {
        if(pr->b==RH) { pr->b=EH; return true; }
        if(pr->b==EH) { pr->b=LH; return false; }
        return !balanceleft(pr);
    }
    return true;
}

template<class T>
bool AVL<T>::remove1(T& a, AVLnode<T> *&pr)
{
    if(pr==NULL) return false;
    bool deleteLeft, rot;
    
    if(a<pr->data)
    {
        deleteLeft = true;
        rot = remove(a, pr->pleft);
    }
    else if(a>pr->data)
    {
        deleteLeft = false;
        rot = remove(a, pr->pright);
    }
    else
    {
        deleteLeft = false;
        rot = remove(pr->data, pr->pright);
    }
    if(rot==false) return false;
    if(deleteLeft) return !balanceright(pr);
    
    return !balanceleft(pr);
}

template<class T>
bool AVL<T>::searchAVL(T&a, AVLnode<T> *pr)
{
    if(pr==NULL) return false;
    if(a < pr->data) return searchAVL(a, pr->pleft);
    if(a > pr->data) return searchAVL(a, pr->pright);
    else return true;
}

#endif /* AVLtree_hpp */
