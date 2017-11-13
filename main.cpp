//
//  main.cpp
//  Tut6Lab
//
//  Created by macOS Sierra on 11/7/17.
//  Copyright © 2017 macOS Sierra. All rights reserved.
//

#include "AVLtree.hpp"
#include <iostream>

using namespace std;


int main(int argc, const char * argv[]) {
    // insert code here...
    
    AVL<int>* pAVLtree = new AVL<int>();
    int a[5] = {50, 35, 90, 30, 40};
    
    pAVLtree->insertAVLtree(a[0]);
    pAVLtree->insertAVLtree(a[1]);
    pAVLtree->insertAVLtree(a[2]);
    
    cout<<endl;
    return 0;
}
