//
//  main.cpp
//  PEA_PROJECT_3
//
//  Created by Szymon Klimczuk on 09/01/2019.
//  Copyright © 2018 Szymon Klimczuk. All rights reserved.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

#include "Graph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand(time( NULL ));
    
    string MAIN_MENU = "\n-----MENU-----\n1-read data from file\n2-display graph\n3-genetic algorithm\n0-exit\nCHOICE: ";
    string FILE_MENU = "\ninsert file name: ";
    
    int choice;
    
    bool menuFlowCondition = true;
    
    Graph *graph = nullptr;
    
    do {
        do {
            cout << MAIN_MENU;
            cin >> choice;
        } while(0 > choice || choice > 4);
        
        switch (choice) {
            case 1:
            {
                //read data from file
                string filename;
                cout << FILE_MENU;
                cin >> filename;
                graph = new Graph(filename);
            } break;
            case 2:
            {
                if(graph != nullptr)
                    graph->displayGraph();
                else
                    cout << endl << "GRAPH IS NOT INITIALIZED" << endl;
            } break;
            case 3:
            {
                if(graph != nullptr){
                    int numOfSeconds;
                    cout << "number of seconds: ";
                    cin >> numOfSeconds;
                        graph->tsp(numOfSeconds);
                }
                else
                    cout << endl << "GRAPH IS NOT INITIALIZED" << endl;
            } break;
            case 0:
            {
                //exit
                if(graph != nullptr)
                    graph->~Graph();
                menuFlowCondition = false;
            } break;
            default:
                break;
        }
    } while(menuFlowCondition);
    
    return 0;
}

