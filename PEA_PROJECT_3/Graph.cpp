//
//  Graph.cpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 09/01/2019.
//  Copyright © 2019 Szymon Klimczuk. All rights reserved.
//

#include "Graph.hpp"

//prototypes of methods used only in this class
int **initializeMatrix(int **matrix, int limit);
int **initializePopulations(int **populations, int limitX, int limitY);
void displayTspResult(int *resultArr, int counter, int totalWeight);
void swap(int *path, int x, int y);

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

void Graph::tsp(){
    this->sizeOfPopulation = 10;
    this->population = new int*[sizeOfPopulation];
    initializePopulations(population, cities + 2, sizeOfPopulation);
    this->numOfGenerations = 5;
    this->numOfCrossings = 5;
    this->numOfMutations = 1;
    
    generateRandomPopulation();
    
//    for (int i = 0; i < numOfGenerations; i++) {
        crossingOperation();
//        mutationOperation();
//    }
    
}

//method generate starting population of random permutations
void Graph::generateRandomPopulation(){
    for(int i = 0; i < sizeOfPopulation; i++){
        int *singlePopulation = new int[cities+1];
        int randomA;
        int randomB;
        
        do{
            randomA = rand() % (cities - 1) + 1;
            randomB = rand() % (cities - 1) + 1;
        }while (randomA == randomB);
        
        for (int k = 0; k < cities; k++)
            singlePopulation[k] = k;

        swap(singlePopulation, randomA, randomB);
        
        singlePopulation[cities] = 0;
//        int tmpSum = calculatePathsCost(singlePopulation);
//        singlePopulation[cities + 1] = tmpSum;
        
        for (int k = 0; k <= cities + 1; k++)
            population[i][k] = singlePopulation[k];
        delete[] singlePopulation;
    }

    for(int i = 0; i < sizeOfPopulation; i++){
        cout << i << " === ";
        for (int k = 0; k < cities + 1; k++) {
            cout << population[i][k] << " ";
        }
        cout << " w(" << population[cities + 1] << ") " << endl;
    }
}

void Graph::mutationOperation(){
    int randomA;
    int randomB;
    int randomC;
    
    do{
        randomA = rand() % (sizeOfPopulation);
        randomB = rand() % (cities - 1) + 1;
        randomC = rand() % (cities - 1) + 1;
    }while (randomB == randomC);
    
//    cout << "---------------------------------PRZED" << endl;
//    cout << randomA << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << populations[randomA][i] << " ";
//    }
//    cout << endl;
    
    //mutating 2 of random chosen permutations
    swap(population[randomA], randomB, randomC);
    
//    cout << "---------------------------------PO" << endl;
//    cout << randomA << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << populations[randomA][i] << " ";
//    }
//    cout << endl;
}

void Graph::crossingOperation(){
    int randomA;
    int randomB;
    
    do{
        randomA = rand() % (sizeOfPopulation);
        randomB = rand() % (sizeOfPopulation);
    }while (randomA == randomB);
    
    int *tempA = population[randomA];
    int *tempB = population[randomB];
    
    cout << "---------------------------------PRZED" << endl;
    cout << randomA << " === ";
    for(int i = 0; i < cities + 1; i++){
        cout << tempA[i] << " ";
    }
    cout << endl;
    cout << randomB << " === ";
    for(int i = 0; i < cities + 1; i++){
        cout << tempB[i] << " ";
    }
    cout << endl;
    
    //crossing 2 of random chosen permutations
    int *newPermutation = new int[cities + 2];
    bool *visited = new bool[cities];
    for(int i = 0; i < cities + 1; i++){
        if(i < (cities+2)/2){
            newPermutation[i] = tempA[i];
            visited[tempA[i]] = true;
        } else {
            for(int k = 0; k < cities + 1; k++){
                if(visited[tempB[k]] != true){
                    newPermutation[i] = tempB[k];
                    visited[tempB[k]] = true;
                }
            }
        }
    }
    
    cout << "---------------------------------PO" << endl;
    cout << randomA << "+" << randomB << " === ";
    for(int i = 0; i < cities + 1; i++){
        cout << newPermutation[i] << " ";
    }
    cout << endl;
}

int Graph::calculatePathsCost(int *path){
    int sum = 0;
    for(int i = 0; i < cities; i++){
        sum += graph[path[i]][path[i+1]];
    }
    return sum;
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

int **initializePopulations(int **populations, int limitX, int limitY){
    for(int i = 0; i < limitY; i++){
        populations[i] = new int[limitY];
        for(int k = 0; k < limitX; k++)
            populations[i][k] = 0;
    }
    
    return populations;
}

void swap(int *path, int x, int y){
    int tmp = path[x];
    path[x] = path[y];
    path[y] = tmp;
}
