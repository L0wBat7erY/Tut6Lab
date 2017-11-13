//
//  AVLtree.cpp
//  Tut6Lab
//
//  Created by macOS Sierra on 11/8/17.
//  Copyright © 2017 macOS Sierra. All rights reserved.
//

#include "AVLtree.hpp"

using namespace std;

template<class T>
void AVL<T>::rotRight(AVLnode<T>*& pRoot)
{
    if(pRoot==NULL) return;
    if(pRoot->pleft==NULL) return;
    AVLnode<T>* p = pRoot->pleft;
    pRoot->pleft = p->pright;
    p->pright = pRoot;
    pRoot=p;
};

template<class T>
void AVL<T>::rotLeft(AVLnode<T>*& pRoot)
{
    if(pRoot==NULL) return;
    if(pRoot->pright==NULL) return;
    AVLnode<T>* p = pRoot->pright;
    pRoot->pright = p->pleft;
    p->pleft = pRoot;
    pRoot=p;
}

template<class T>
void AVL<T>::rotLR(AVLnode<T>*& pRoot)
{
    rotLeft(pRoot->pleft);
    rotRight(pRoot);
}

template<class T>
void AVL<T>::rotRL(AVLnode<T>*& pRoot)
{
    rotRight(pRoot->pright);
    rotLeft(pRoot);
}

template<class T>
bool AVL<T>::balanceleft(AVLnode<T>*& pRoot)
{
    if(pRoot->b==EH) { pRoot->b=LH; return true; }
    if(pRoot->b==RH) { pRoot->b=EH; return false; }
    if(pRoot->pleft->b==LH){
        rotRight(pRoot);
        pRoot->b=pRoot->pright->b=EH;
        return false;
    }
    rotLR(pRoot);
    if(pRoot->b==LH){
        pRoot->b=pRoot->pleft->b=EH;
        pRoot->pleft->b=RH;
        return false;
    }
    pRoot->b=pRoot->pright->b=EH;
    pRoot->pleft->b=LH;
    return false;
}

template<class T>
bool AVL<T>::balanceright(AVLnode<T>*& pRoot)
{
    if(pRoot->b==EH) { pRoot->b=RH; return true; }
    if(pRoot->b==LH) { pRoot->b=EH; return false; }
    if(pRoot->pright->b==RH){
        rotLeft(pRoot);
        pRoot->b=pRoot->pleft->b=EH;
        return false;
    }
    rotRL(pRoot);
    if(pRoot->b==RH){
        pRoot->b=pRoot->pright->b=EH;
        pRoot->pright->b=LH;
        return false;
    }
    pRoot->b=pRoot->pleft->b=EH;
    pRoot->pright->b=RH;
    return false;
}

template<class T>
bool AVL<T>::insert(T& a, AVLnode<T>*& pRoot)
{
    if(pRoot==NULL) { pRoot = new AVLnode<T>(a); return true; }
    if(a<pRoot->data)
    {
        if(insert(a, pRoot->pleft)==false) return false;
        return balanceleft(pRoot);
    }
    else
    {
        if(insert(a, pRoot->pright)==false) return false;
        return balanceright(pRoot);
    }
}

template<class T>
bool AVL<T>::remove(T &a, AVLnode<T> *&pRoot)
{
    if(pRoot==NULL) return false;
    if(a<pRoot->data)
    {
        if(remove(a, pRoot->pleft)==false) return false;
        if(pRoot->b==LH) { pRoot->b=EH; return true; }
        if(pRoot->b==EH) { pRoot->b=RH; return false; }
        return !balanceright(pRoot);
    }
    if(a>pRoot->data)
    {
        if(remove(a, pRoot->pright)==false) return false;
        if(pRoot->b==RH) { pRoot->b=EH; return true; }
        if(pRoot->b==EH) { pRoot->b=LH; return false; }
        return !balanceleft(pRoot);
    }
    if(pRoot->pleft==NULL && pRoot->pright==NULL)
    {
        delete pRoot; pRoot=NULL; return true;
    }
    if(pRoot->pleft==NULL)
    {
        AVLnode<T>* p=pRoot;
        pRoot=pRoot->pright;
        delete p; p=NULL;
        return true;
    }
    if(pRoot->pright==NULL)
    {
        AVLnode<T>* p=pRoot;
        pRoot=pRoot->pleft;
        delete p; p=NULL;
        return true;
    }
    AVLnode<T>* p=pRoot->pright;
    while(p->pleft) p = p->pleft;
    pRoot->data = p->data;
    if(remove(p->data, pRoot->pright))
    {
        if(pRoot->b==RH) { pRoot->b=EH; return true; }
        if(pRoot->b==EH) { pRoot->b=LH; return false; }
        return !balanceleft(pRoot);
    }
    return true;
}

template<class T>
bool AVL<T>::remove1(T& a, AVLnode<T> *&pRoot)
{
    if(pRoot==NULL) return false;
    bool deleteLeft, rot;
    
    if(a<pRoot->data)
    {
        deleteLeft = true;
        rot = remove(a, pRoot->pleft);
    }
    else if(a>pRoot->data)
    {
        deleteLeft = false;
        rot = remove(a, pRoot->pright);
    }
    else
    {
        deleteLeft = false;
        rot = remove(pRoot->data, pRoot->pright);
    }
    if(rot==false) return false;
    if(deleteLeft) return !balanceright(pRoot);
    
    return !balanceleft(pRoot);
}

template <class T>
void AVL<T>::traverseNLR(AVLnode<T>* pRoot)
{
    if (pRoot != NULL)
    {
        cout << pRoot->data << " ";
        traverseNLR(pRoot->pleft);
        traverseNLR(pRoot->pright);
    }
}

template <class T>
void AVL<T>::traverseLNR(AVLnode<T>* pRoot)
{
    if(pRoot!=NULL)
    {
        traverseLNR(pRoot->pleft);
        cout << pRoot->data << " ";
        traverseLNR(pRoot->pright);
    }
    return;
}

template<class T>
bool AVL<T>::search(T a, AVLnode<T> *pRoot)
{
    if(pRoot==NULL) return false;
    if(a < pRoot->data) return searchAVL(a, pRoot->pleft);
    if(a > pRoot->data) return searchAVL(a, pRoot->pright);
    else return true;
}

template<class T>
T* AVL<T>::find(T &a, AVLnode<T> *pRoot)
{
    if(pRoot==NULL) return NULL;
    if(pRoot->data==a) return &pRoot->data;
    else if(pRoot->data>a) return find(a, pRoot->pleft);
    else return find(a, pRoot->pright);
}

template<class T>
bool AVL<T>::insertAVLtree(T& a)
{
    if(insert(a, pRoot)==true) return true;
    else return false;
}

template<class T>
bool AVL<T>::removeNodeAVLtree(T &a)
{
    if(remove(a, pRoot)==true) return true;
    else return false;
}

template<class T>
void AVL<T>::traverseNLR_AVLtree()
{
    traverseNLR(pRoot);
}

template<class T>
void AVL<T>::traverseLNR_AVLtree()
{
    traverseLNR(pRoot);
}

template<class T>
bool AVL<T>::searchDataAVLtree(T a)
{
    if(search(a, pRoot)==true) return true;
    else return false;
}

template<class T>
T* AVL<T>::findDataAVLtree(T& a)
{
    find(a, pRoot);
}
