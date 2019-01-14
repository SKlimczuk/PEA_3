//
//  Gene.cpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 14/01/2019.
//  Copyright © 2019 Szymon Klimczuk. All rights reserved.
//

#include "Gene.hpp"

Gene::Gene(){}

Gene::Gene(vector<int> path, int cost){
    this->cost = cost;
    this->path = path;
}

Gene::~Gene(){
}

int Gene::getCost(){
    return this->cost;
}

vector<int> Gene::getPath(){
    return this->path;
}

void Gene::setCost(int cost){
    this->cost = cost;
}

void Gene::setPath(vector<int> path){
    this->path = path;
}

void Gene::displayPath(int limit){
    for (int i = 0; i <= limit; i++)
        cout << path.at(i) << " ";
    cout << " w(" << cost << ")" << endl;
}
