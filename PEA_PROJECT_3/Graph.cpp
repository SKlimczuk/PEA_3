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
int **copyPopulation(int **array, int limitY, int limitX);
void swap(int *path, int x, int y);
void swapArrays(int *pathA, int *pathB, int limit);

Graph::Graph(string filename)
{
    ifstream file;
    file.open(filename.c_str());
    
    if(!file.good())
        cout << endl << "INCORRECT FILE !" << endl;
    else{
        cout << endl << "CORRECT FILE !" << endl;
        
        file >> this->cities;
        this->weightIndex = this->cities + 1;
        
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

Graph::~Graph(){
    for(int i = 0; i < cities; i++)
        delete[] graph[i];
    delete[] graph;
}

void Graph::displayGraph(){
    cout << endl << "-----GRAPH-----" << endl;
    for(int i = 0; i < cities; i++){
        for(int k = 0; k < cities; k++){
            cout << setw(4) << graph[i][k] << " ";
        }
        cout << endl;
    }
}

void Graph::tsp(){
    this->currentSizeOfPopulation = 10;
    this->finalSizeOfPopulation = currentSizeOfPopulation;
    this->population = new int*[currentSizeOfPopulation];
    initializePopulations(population, cities + 1, finalSizeOfPopulation);
    this->numOfGenerations = 50;
    this->numOfCrossings = 5;
    this->numOfMutations = 1;
    
    generateRandomPopulation();
//    for(int i = 0; i < finalSizeOfPopulation; i++){
//        for (int k = 0; k <= cities + 1; k++)
//            cout << population[i][k] << " ";
//        cout << endl;
//    }
    displayPopulation();

    for(int i = 0; i < numOfGenerations; i++){
        for (int k = 0; k < numOfCrossings; k++) {
            crossingOperation();
        }
        for (int k = 0; k < numOfMutations; k++) {
            mutationOperation();
        }
        sortPopulation(currentSizeOfPopulation);
        currentSizeOfPopulation = finalSizeOfPopulation;
//        displayPopulation();
    }
    displayBestPath();
    
    for(int i = 0; i < currentSizeOfPopulation; i++)
        delete population[i];
    delete []population;
}

void Graph::generateRandomPopulation(){
    for(int i = 0; i < finalSizeOfPopulation; i++){
        int *singlePopulation = new int[cities + 1];
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
        calculatePathsCost(singlePopulation);
        
        for (int k = 0; k <= cities + 1; k++)
            population[i][k] = singlePopulation[k];
        delete[] singlePopulation;
        for (int k = 0; k <= cities + 1; k++)
            cout << population[i][k] << " ";
        cout << endl;
    }
}

void Graph::displayPopulation(){
    cout << endl << "-----POPULATION-----" << endl;
    for(int i = 0; i < finalSizeOfPopulation; i++){
        cout << i << " === ";
        for (int k = 0; k <= cities; k++) {
            cout << population[i][k] << " ";
        }
        cout << " w(" << population[i][weightIndex] << ") " << endl;
    }
}

void Graph::mutationOperation(){
    int randomA;
    int randomB;
    int randomC;
    
    do{
        randomA = rand() % (finalSizeOfPopulation);
        randomB = rand() % (cities - 1) + 1;
        randomC = rand() % (cities - 1) + 1;
    }while (randomB == randomC);
    
//    cout << "---------------------------------PRZED" << endl;
//    cout << randomA << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << population[randomA][i] << " ";
//    }
//    cout << " w(" << population[randomA][weightIndex] << ")";
//    cout << endl;
    
    swap(population[randomA], randomB, randomC);
    calculatePathsCost(population[randomA]);
    
//    cout << "---------------------------------PO" << endl;
//    cout << randomA << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << population[randomA][i] << " ";
//    }
//    cout << " w(" << population[randomA][weightIndex] << ")" << endl;
}

void Graph::crossingOperation(){
    int randomA;
    int randomB;
    
    do{
        randomA = rand() % (finalSizeOfPopulation);
        randomB = rand() % (finalSizeOfPopulation);
    }while (randomA == randomB);
    
    int *tempA = population[randomA];
    int *tempB = population[randomB];
    
//    cout << "---------------------------------PRZED" << endl;
//    cout << randomA << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << tempA[i] << " ";
//    }
//    cout << endl;
//    cout << randomB << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << tempB[i] << " ";
//    }
//    cout << endl;
    
    int *child = new int[cities + 1];
    
    bool *visited = new bool[cities];
    for (int i = 0; i < cities; i++)
        visited[i] = false;
    
    int crossingIndex = 0;
    for (int i = 0; i < (cities+1)/2; i++){
        child[crossingIndex] = tempA[crossingIndex];
        visited[tempA[crossingIndex]] = true;
        crossingIndex++;
    }
    
    for (int i = 0; i < cities + 1; i++) {
        if(visited[tempB[i]] == false){
            child[crossingIndex] = tempB[i];
            visited[tempB[i]] = true;
            crossingIndex++;
        }
    }
    
    child[cities] = 0;
    calculatePathsCost(child);
    
//    cout << "---------------------------------PO" << endl;
//    cout << randomA << "x" << randomB << " === ";
//    for(int i = 0; i < cities + 1; i++){
//        cout << child[i] << " ";
//    }
//    cout << " w(" << child[weightIndex] << ")" << endl;
    
    currentSizeOfPopulation++;
    population = copyPopulation(population, currentSizeOfPopulation, cities + 1);
    
    for(int i = 0; i <= cities + 1; i++)
        population[currentSizeOfPopulation-1][i] = child[i];
    
    delete []visited;
    delete []child;
}

void Graph::calculatePathsCost(int *path){
    int sum = 0;
    for(int i = 0; i < cities; i++){
        sum += graph[path[i]][path[i+1]];
    }
    path[weightIndex] = sum;
}

void Graph::sortPopulation(int limit){
    for(int i = 0; i < limit - 1; i++)
        for(int j = 0; j < limit - i - 1; j++)
            if(population[j][weightIndex] > population[j+1][weightIndex])
                swapArrays(population[j], population[j+1], cities+1);
}

void Graph::cutPopulation(int limit){
    population = copyPopulation(population, limit, cities+1);
}

void Graph::displayBestPath(){
    cout << endl << "-----BEST-----" << endl;
    for (int i = 0; i < cities + 1; i++) {
        cout << population[0][i] << " ";
    }
    cout << " w(" << population[0][weightIndex] << ")" << endl;
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

int **initializePopulations(int **population, int limitX, int limitY){
    for(int i = 0; i < limitY; i++){
        population[i] = new int[limitY];
        for(int k = 0; k < limitX; k++)
            population[i][k] = 0;
    }
    
    return population;
}

void swap(int *path, int x, int y){
    int tmp = path[x];
    path[x] = path[y];
    path[y] = tmp;
}

void swapArrays(int *pathA, int *pathB, int limit){
    int *tmpArray = new int[limit];
    
    for(int k = 0; k <= limit; k++){
        tmpArray[k] = pathA[k];
        pathA[k] = pathB[k];
        pathB[k] = tmpArray[k];
    }
}

int **copyPopulation(int **array, int limitY, int limitX){
    int **tempArr = new int*[limitY];
    initializePopulations(tempArr, limitX, limitY);
    
    for (int i = 0; i < limitY-1; i++)
        for (int k = 0; k <= limitX + 1; k++)
            tempArr[i][k] = array[i][k];
    
//    for (int i = 0; i < limitY; i++)
//        delete array[i];
//    delete []array;
    
    return tempArr;
}
