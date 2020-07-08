//
// Created by Andrea on 19/03/2020.
//

#include "gtest/gtest.h"
#include <SFML/Graphics.hpp>
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\findpath.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\MAP.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\PLAYER.h"
#include "C:\Users\Andrea\CLionProjects\LAB_PROJECT\ALGORITHM.h"


class TestPercorso : public testing::Test{
    //classe di testig del percorso
};


TEST(TestPercorso, ControlloPercorsoValido){
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(10, 10);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "D:/sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    EXPECT_EQ(SearchState, AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED);
}

TEST(TestPercorso, ControlloPercorsoNonValido){
    MapSearchNode StartNode(0, 0);
    MapSearchNode GoalNode(6, 11);
    AStarSearch<MapSearchNode> astarsearch;
    const unsigned int NumSearches = 1;
    Player player(16 + 32 * StartNode.x, 16 + 32 * StartNode.y, sf::Vector2u(3, 18), "D:/sprite/pinguino.png", 0.01f);
    unsigned int SearchState;

    findpathalg(&player, StartNode, GoalNode, &SearchState, &astarsearch, &NumSearches);
    EXPECT_EQ(SearchState, AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED);
}





