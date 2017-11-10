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
    
    AVL<int> AVLtree;
    int b=60;
    int a[15] = {50, 35, 90, 30, 40, 70, 110, 10, 33, 38, 45, 60, 120, 20, 39};
    
    for(int i=0; i<15; i++)
    {
        AVLtree.insert(a[i], AVLtree.getnode());
    }
    
    if(AVLtree.searchAVL(b, AVLtree.getnode())==true) cout<<"Founded!";
    
    cout<<endl;
    return 0;
}
