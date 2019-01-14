//
//  Gene.hpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 14/01/2019.
//  Copyright © 2019 Szymon Klimczuk. All rights reserved.
//

#ifndef Gene_hpp
#define Gene_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <vector>

using namespace std;

class Gene{
private:
    int cost;
    vector<int> path;
public:
    Gene();
    Gene(vector<int> path, int cost);
    ~Gene();
    
    int getCost();
    vector<int> getPath();
    
    void setCost(int cost);
    void setPath(vector<int> path);
    
    void displayPath(int limit);
};

#endif /* Gene_hpp */
