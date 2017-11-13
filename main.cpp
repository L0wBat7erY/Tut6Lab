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
    
    
    AVL<int>* tree = new AVL<int>;
    
    tree->insertAVLtree(50);
    tree->traverseLNR_AVLtree();
    
    cout<<endl;
    return 0;
}
