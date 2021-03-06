/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (header file).
 *
 */
#pragma once 

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>
#include "GraphApp.hpp"
#include "structs.hpp"
#include <algorithm>
#include <float.h>

using namespace std;

/** STUDENT IMPLEMENTED FUNCTIONS */
void buildMSTPrim(Graph g, GraphApp *app);

void buildMSTKruskal(Graph g, GraphApp *app);

void findShortestPath(int start, int end, Graph g, GraphApp * app);

/** Helper function to draw an edge on the graphics app given two nodes */
void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app, 
    bool mst);
void updateInfo(Edge* edgeToAdd, std::vector<Node*> &onMST, std::vector<Node*> &notOnMST,
 std::vector<Edge*> &copyEdge);
std::vector<Edge*> getEdgeFromTree(std::vector<Edge*> &v, std::vector<Node*> onMST,
 std::vector<Node*> notOnMST);
bool checkEdgeValidForAddition(std::vector<Node*> onMST, std::vector<Node*> notOnMST,Edge* i);

void doUpdate(Node* current, Edge* edge,std::vector<Node*> &visited, std::vector<Node*> &notVisited);
Node* lowestCostNode(std::vector<Node*> &v /*notVisited*/);
std::vector<Edge*> getNeightboringNodes(Node* currNode, std::vector<Node*> visited, std::vector<Edge*> &edges);

/** Vector to store Nodes both on and not on MST for Prim's Algorithm */
vector<Node *> onMST;
vector<Node *> notOnMST;

/**
 * @brief Struct representing an edge between two trees during computation of
 * 			MST using Kruskal's algorithm.
 *
 * The KruskalEdge struct stores the two Nodes that it connects as well as the
 * weight of the edge (used in comparisons for priority_queue
 */
struct KruskalEdge
{
	double weight;
	Node *u;
	Node *v;
};
