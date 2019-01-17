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
#include <vector>
#include <algorithm>

using namespace std;

#include "Gene.hpp"

class Graph {
    
private:
    //number of cities/vertexes
    int cities;
    
    //graph represented as adjency matrix
    int **graph;
    
    int numOfGenerations;
    int currentSizeOfPopulation;
    int finalSizeOfPopulation;
    int numOfMutations;
    int numOfCrossings;
    
    vector<Gene> population;
    
    void generateRandomPopulation();
    void displayPopulation();
    
    int calculatePathsCost(vector<int> path);
    
    void mutationOperation();
    void crossingOperationA();
    void crossingOperationB();
    
    void sortPopulation();
    void cutPopulation();
    void displayBestPath();
    
public:
    Graph(string filename);
    Graph(int cities);
    ~Graph();
    
    void displayGraph();
    
    void tsp(int numOfSeconds);
};


#endif /* Graph_hpp */
