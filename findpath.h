
#ifndef LAB_PROJECT_FINDPATH_H
#define LAB_PROJECT_FINDPATH_H

#include "stlastar.h" // See header for copyright and usage information

#include <iostream>
#include <stdio.h>
#include <math.h>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

// Global data

// The world map

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

int world_map[ MAP_WIDTH * MAP_HEIGHT ] =
        {

            // 0001020304050607080910111213141516171819
                1,1,2,1,1,3,1,1,4,4,1,1,1,1,2,1,1,1,1,1,   // 00
                1,9,9,7,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
                1,9,9,1,1,9,9,9,1,9,1,9,1,9,3,9,9,9,1,1,   // 02
                1,9,9,2,1,9,9,9,4,9,1,9,2,9,1,9,9,9,1,1,   // 03
                4,9,1,4,1,1,9,9,1,9,1,9,3,1,4,1,9,9,2,1,   // 04
                1,9,1,1,9,1,3,1,1,9,5,1,1,1,9,1,2,1,1,1,   // 05
                1,9,9,9,9,1,4,1,2,1,1,9,9,9,9,1,1,1,1,5,   // 06
                1,9,9,9,9,9,9,7,8,9,5,1,9,9,9,7,8,9,9,1,   // 07
                1,9,1,2,1,4,1,1,1,1,1,9,1,1,2,1,3,1,1,1,   // 08
                5,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
                1,9,1,5,1,1,9,1,1,9,1,2,1,1,1,3,1,1,1,1,   // 10
                1,9,9,9,9,9,3,9,1,9,4,9,9,7,8,9,1,2,1,5,   // 11
                1,9,1,9,1,9,9,9,4,9,3,9,1,1,1,9,9,9,1,1,   // 12
                1,9,1,9,3,9,9,9,1,9,5,9,5,9,1,9,9,9,1,1,   // 13
                1,9,1,2,1,1,9,9,1,9,4,9,1,4,1,1,9,9,1,1,   // 14
                5,9,1,1,9,1,2,1,1,9,5,1,1,1,9,1,1,3,1,1,   // 15
                1,9,9,9,9,1,1,1,1,2,1,9,9,9,9,1,1,1,1,1,   // 16
                1,1,9,9,9,7,8,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
                1,9,3,2,1,3,1,4,1,1,1,9,1,1,1,1,4,1,1,1,   // 18
                1,1,1,1,1,1,1,1,2,1,1,1,1,5,5,5,1,1,1,3,   // 19

        };

// map helper functions

int GetMap( int x, int y )
{
    if( x < 0 ||
        x >= MAP_WIDTH ||
        y < 0 ||
        y >= MAP_HEIGHT
            )
    {
        return 9;
    }

    return world_map[(y*MAP_WIDTH)+x];
}



// Definitions

class MapSearchNode
{
public:
    int x;	 // the (x,y) positions of the node
    int y;

    MapSearchNode() { x = y = 0; }
    MapSearchNode( int px, int py ) { x=px; y=py; }

    float GoalDistanceEstimate( MapSearchNode &nodeGoal );
    bool IsGoal( MapSearchNode &nodeGoal );
    bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
    float GetCost( MapSearchNode &successor );
    bool IsSameState( MapSearchNode &rhs );

    void PrintNodeInfo();

    void setX(int x);

    void setY(int y);

};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

    // same state in a maze search is simply when (x,y) are the same
    if( (x == rhs.x) && (y == rhs.y) )
    {
        return true;
    }
    else
    {
        return false;
    }

}

void MapSearchNode::PrintNodeInfo()
{
    char str[100];
    sprintf( str, "Node position : (%d,%d)\n", x,y );

    cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

    if( (x == nodeGoal.x) &&
        (y == nodeGoal.y) )
    {
        return true;
    }

    return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

    int parent_x = -1;
    int parent_y = -1;

    if( parent_node )
    {
        parent_x = parent_node->x;
        parent_y = parent_node->y;
    }


    MapSearchNode NewNode;

    // push each possible move except allowing the search to go backwards

    if( (GetMap( x-1, y ) < 9) && !((parent_x == x-1) && (parent_y == y))
            )
    {
        NewNode = MapSearchNode( x-1, y );
        astarsearch->AddSuccessor( NewNode );
    }

    if( (GetMap( x, y-1 ) < 9)
        && !((parent_x == x) && (parent_y == y-1))
            )
    {
        NewNode = MapSearchNode( x, y-1 );
        astarsearch->AddSuccessor( NewNode );
    }

    if( (GetMap( x+1, y ) < 9)
        && !((parent_x == x+1) && (parent_y == y))
            )
    {
        NewNode = MapSearchNode( x+1, y );
        astarsearch->AddSuccessor( NewNode );
    }


    if( (GetMap( x, y+1 ) < 9)
        && !((parent_x == x) && (parent_y == y+1))
            )
    {
        NewNode = MapSearchNode( x, y+1 );
        astarsearch->AddSuccessor( NewNode );
    }

    return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
    return (float) GetMap( x, y );

}

void MapSearchNode::setX(int x) {
    MapSearchNode::x = x;
}

void MapSearchNode::setY(int y) {
    MapSearchNode::y = y;
}


#endif //LAB_PROJECT_FINDPATH_H
