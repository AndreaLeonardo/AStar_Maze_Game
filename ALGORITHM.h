//
// Created by Andrea on 07/07/2020.
//

#ifndef LAB_PROJECT_ALGORITHM_H
#define LAB_PROJECT_ALGORITHM_H

#include <iostream>
#include "findpath.h"
#include "PLAYER.h"


void findpathalg(Player* player, MapSearchNode StartNode, MapSearchNode GoalNode, unsigned int* ss,
                 AStarSearch<MapSearchNode>* astarsearch, const unsigned int* NumSearches){


    unsigned int SearchCount = 0;
    unsigned int SearchState;
    while(SearchCount < (*NumSearches))
    {
        MapSearchNode nodeStart;
        nodeStart.x = StartNode.x;
        nodeStart.y = StartNode.y;
        MapSearchNode nodeEnd;
        nodeEnd.x = GoalNode.x;
        nodeEnd.y = GoalNode.y;

        (*astarsearch).SetStartAndGoalStates( nodeStart, nodeEnd );
        unsigned int SearchSteps = 0;
        do
        {
            SearchState = (*astarsearch).SearchStep();
            SearchSteps++;
        }
        while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );
        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
        {
            cout << "Traguardo Trovato! Visualizzo percorso...\n";
            MapSearchNode *node = (*astarsearch).GetSolutionStart();
            int steps = 0;
            (*player).directions.push_back(node);
            for( ;; )
            {
                node = (*astarsearch).GetSolutionNext();
                if( !node ) break;
                (*player).directions.push_back(node);
                steps ++;
            };
            cout << "Passi al traguardo: " << steps << endl;
            (*astarsearch).FreeSolutionNodes();
        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
        {
            cerr << "ERRORE: Traguardo non trovato! Termino programma...";
            (*astarsearch).EnsureMemoryFreed();

        }
        cout << "Passi Ricerca : " << SearchSteps << "\n";
        SearchCount ++;
        (*astarsearch).EnsureMemoryFreed();
    }
    (*player).NewPath = false;
    *ss = SearchState;

}


#endif //LAB_PROJECT_ALGORITHM_H
