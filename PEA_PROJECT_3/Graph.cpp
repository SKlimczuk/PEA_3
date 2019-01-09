//
//  Graph.cpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 09/01/2019.
//  Copyright © 2019 Szymon Klimczuk. All rights reserved.
//

#include "Graph.hpp"

//prototypes of methods used only in this class
int** initializeMatrix(int **matrix, int limit);
void displayTspResult(int *resultArr, int counter, int totalWeight);

Graph::Graph(string filename)
{
    ifstream file;
    file.open(filename.c_str());
    
    if(!file.good())
        cout << endl << "INCORRECT FILE !" << endl;
    else
    {
        cout << endl << "CORRECT FILE !" << endl;
        
        file >> this->cities;
        
        graph = new int*[cities];
        graph = initializeMatrix(graph, cities);
        
        int weight;
        for(int i = 0; i < cities; i++){
            for(int k = 0; k < cities; k++){
                file >> weight;
                graph[i][k] = weight;
            }
        }
        
        file.close();
        
        cout << "\nCITIES:" << cities << endl;
    }
}

Graph::Graph(int cities)
{
    this -> cities = cities;
    graph = new int*[cities];
    graph = initializeMatrix(graph, cities);
    
    for(int i = 0; i < cities; i++){
        for(int k = 0; k < cities; k++){
            if(i == k)
                graph[i][k] = 0;
            else
                graph[i][k] = rand()%100;
        }
    }
}

Graph::~Graph()
{
    for(int i = 0; i < cities; i++)
    {
        delete[] graph[i];
    }
    
    delete[] graph;
}

void Graph::displayGraph(){
    for(int i = 0; i < cities; i++){
        for(int k = 0; k < cities; k++){
            cout << setw(4) << graph[i][k] << " ";
        }
        cout << endl;
    }
}

//----------------------------------------------class methods
int** initializeMatrix(int **matrix, int limit)
{
    for(int i = 0; i < limit; i++){
        matrix[i] = new int[limit];
        for(int k = 0; k < limit; k++)
            matrix[i][k] = 0;
    }
    
    return matrix;
}

void displayTspResult(int *resultArr, int counter, int totalWeight)
{
    if(counter)
    {
        for(int i = 0; i < counter; i++)
            cout << resultArr[i] << " ";
        cout << resultArr[0] << endl;
        cout << "WEIGHT = " << totalWeight << endl;
    }
    else
        cout << "\nERROR" << endl;
}
