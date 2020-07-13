//
// Created by Andrea on 08/07/2020.
//

#include "gtest/gtest.h"
#include <SFML/Graphics.hpp>
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\findpath.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\MAP.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\PLAYER.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\ALGORITHM.h"

const int cellSize = cellSize;
const int cellCenter = cellSize/2;


class TestPercorso : public testing::Test{
    //classe di testig del percorso
};


TEST(TestPercorso, ControlloPercorsoValido){
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(10, 10);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    EXPECT_EQ(SearchState, AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED);
}

TEST(TestPercorso, ControlloPercorsoNonValido){
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(6, 11);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    EXPECT_EQ(SearchState, AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED);
}

TEST(TestPercorso, ControlloEfficienza1){
    MapSearchNode StartNode(0, 19);
    MapSearchNode GoalNode(12, 5);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    bool founderr = false;
    for(int i = 0; i< player.directions.size(); i++){
        if(player.directions[i]->x == 10 & player.directions[i]->y == 10)
            founderr = true;
    }

    EXPECT_EQ(founderr, false);
}

TEST(TestPercorso, ControlloEfficienza2){
    MapSearchNode StartNode(0, 19);
    MapSearchNode GoalNode(11, 5);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    bool founderr = false;
    for(int i = 0; i< player.directions.size(); i++){
        if(player.directions[i]->x == 10 & player.directions[i]->y == 10)
            founderr = true;
    }

    EXPECT_EQ(founderr, true);
}

TEST(TestPercorso, BoomerangTest){

    srand((unsigned)time(0));
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(rand()%20, rand()%20);
    if (world_map[GoalNode.y * MAP_HEIGHT + GoalNode.x] == 9){
        GoalNode.x = 19;
        GoalNode.y = 19;
    }
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    std::vector<MapSearchNode*> path1(player.directions);
    player.directions.clear();
    findpathalg(&player, GoalNode, StartNode, &SearchState, &astarsearch, &NumSearches);
    std::vector<MapSearchNode*> path2(player.directions);

    EXPECT_EQ(path1.size(), path2.size());
}

TEST(TestPercorso, HardBoomerangTest){

    srand((unsigned)time(0));
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(rand()%20, rand()%20);
    if (world_map[GoalNode.y * MAP_HEIGHT + GoalNode.x] == 9){
        GoalNode.x = 19;
        GoalNode.y = 19;
    }
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(cellCenter + cellSize * StartNode.x, cellCenter + cellSize * StartNode.y, sf::Vector2u(3, 18), "../../sprite/pinguino.png", 0.01f);
    unsigned int SearchState;
    int sum1 = 0;
    int sum2 = 0;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    std::vector<MapSearchNode*> path1(player.directions);
    for(int i=0; i<path1.size(); i++){
        sum1 += world_map[path1[i]->y * MAP_HEIGHT + path1[i]->x];
    }
    player.directions.clear();
    findpathalg(&player, GoalNode, StartNode, &SearchState, &astarsearch, &NumSearches);
    std::vector<MapSearchNode*> path2(player.directions);
    for(int i=0; i<path2.size(); i++){
        sum2 += world_map[path2[i]->y * MAP_HEIGHT + path2[i]->x];
    }

    cout << "sum1: " << sum1 << " sum2: " << sum2 << endl;

    EXPECT_EQ(sum1, sum2);
}




