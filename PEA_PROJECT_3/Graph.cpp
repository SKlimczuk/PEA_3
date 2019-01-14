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

Graph::Graph(string filename)
{
    ifstream file;
    file.open(filename.c_str());
    
    if(!file.good())
        cout << endl << "INCORRECT FILE !" << endl;
    else{
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
    this->finalSizeOfPopulation = 10;
    this->numOfGenerations = 50;
    this->numOfCrossings = 5;
    this->numOfMutations = 1;
    
    generateRandomPopulation();

    for(int i = 0; i < numOfGenerations; i++){
        for (int k = 0; k < numOfCrossings; k++) {
            crossingOperation();
        }
        for (int k = 0; k < numOfMutations; k++) {
            mutationOperation();
        }
        sortPopulation();
        cutPopulation();
    }
    displayBestPath();
}

void Graph::generateRandomPopulation(){
    for(int i = 0; i < finalSizeOfPopulation; i++){
       
        vector<int> singlePopulation;
        
        int randomA;
        int randomB;
        
        do{
            randomA = rand() % (cities - 1) + 1;
            randomB = rand() % (cities - 1) + 1;
        }while (randomA == randomB);
        
        for (int k = 0; k < cities; k++)
            singlePopulation.push_back(k);
        singlePopulation.push_back(0);
        swap(singlePopulation[randomA], singlePopulation[randomB]);
        
        Gene *gene = new Gene(singlePopulation, calculatePathsCost(singlePopulation));

        population.push_back(*gene);
    }
}

void Graph::displayPopulation(){
    int counter = 0;
    cout << endl << "-----POPULATION-----" << endl;
    for(int i = 0; i < finalSizeOfPopulation; i++){
        cout << counter << " === ";
        population.at(i).displayPath(cities);
        counter++;
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
    
    auto vecToMutation = population[randomA].getPath();
    swap(vecToMutation[randomB], vecToMutation[randomC]);
    population[randomA].setPath(vecToMutation);
    population[randomA].setCost(calculatePathsCost(vecToMutation));
}

void Graph::crossingOperation(){
    int randomA;
    int randomB;
    
    do{
        randomA = rand() % (finalSizeOfPopulation);
        randomB = rand() % (finalSizeOfPopulation);
    }while (randomA == randomB);
    
    auto tempA = population[randomA].getPath();
    auto tempB = population[randomB].getPath();
    
    vector<int> child;
    
    bool *visited = new bool[cities];
    for (int i = 0; i < cities; i++)
        visited[i] = false;
    
    int crossingIndex = 0;
    for (int i = 0; i < (cities+1)/2; i++){
        child.push_back(tempA[crossingIndex]);
        visited[tempA[crossingIndex]] = true;
        crossingIndex++;
    }
    
    for (int i = 0; i < cities + 1; i++) {
        if(visited[tempB[i]] == false){
            child.push_back(tempB[i]);
            visited[tempB[i]] = true;
            crossingIndex++;
        }
    }
    child.push_back(0);
    
    Gene gene;
    gene.setPath(child);
    gene.setCost(calculatePathsCost(child));
    population.push_back(gene);
}

int Graph::calculatePathsCost(vector<int> path){
    int sum = 0;
    for(int i = 0; i < cities; i++){
        sum += graph[path[i]][path[i+1]];
    }
    return sum;
}

void Graph::sortPopulation(){
    for(int i = 0; i < population.size() - 1; i++)
        for(int j = 0; j < population.size() - i - 1; j++)
            if(population[j].getCost() > population[j+1].getCost())
                swap(population[j], population[j+1]);
}

void Graph::cutPopulation(){
    while(population.size() != finalSizeOfPopulation){
        population.pop_back();
    }
    cout << endl << "zostalo " << population.size() << " elementow" << endl;
}

void Graph::displayBestPath(){
    cout << endl << "-----BEST-----" << endl;
    population[0].displayPath(cities);
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
