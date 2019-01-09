//
//  Graph.hpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 09/01/2019.
//  Copyright © 2019 Szymon Klimczuk. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <sstream>

using namespace std;

class Graph {
    
private:
    //number of cities/vertexes
    int cities;
    
    //graph representation as adjency matrix
    int **graph;
    
public:
    Graph(string filename);
    Graph(int cities);
    ~Graph();
    
    void displayGraph();
    
    void tsp();
};


#endif /* Graph_hpp */