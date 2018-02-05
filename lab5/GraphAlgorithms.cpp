/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2018
 * @copyright This code is in the public domain.
 *
 * @brief The MST and Shortest Path algorithms
 * (implementation).
 *
 */
#include "GraphAlgorithms.hpp"



/**
 * checkEdgeValidForAddition - checks whether the edge has one node in the MST and one node not on the MST, return true if true, false otherwise
 * @param  onMST    the list of nodes currently on the MST
 * @param  notOnMST the list of nodes not on MST and still in graph
 * @param  i        the edge we want to check if we can add
 * @return          a yes or no indicating whether we can add said edge
 */
bool checkEdgeValidForAddition(std::vector<Node*> onMST, std::vector<Node*> notOnMST,Edge* i){
    //returns true if edge in question in a new edge that would extend the tree
    bool aIntreebInGraph = ((find(onMST.begin(), onMST.end(), i->a) != onMST.end()) && (find(notOnMST.begin(), notOnMST.end(), i->b) != notOnMST.end()));
    bool bIntreeaInGraph = ((find(onMST.begin(), onMST.end(), i->b) != onMST.end()) && (find(notOnMST.begin(), notOnMST.end(), i->a) != notOnMST.end()));
    return aIntreebInGraph || bIntreeaInGraph;
}


/**
 * get Edge From tree iterates through all possible edges and finds the edges that are valid to be added to the MST
 */
std::vector<Edge*> getEdgeFromTree(std::vector<Edge*> &v, std::vector<Node*> onMST, std::vector<Node*> notOnMST){
    std::vector<Edge*> newvec;
    for(auto i: v){
        if(checkEdgeValidForAddition(onMST, notOnMST, i)){
            newvec.push_back(i);
        }
    }
    return newvec;
}

/**
 * updateInfo updates the MST, notOnMST, and the list of edges we are considering so that we don't repeat looking through invalid edges. 
 * this is a helper function
 * @param edgeToAdd current edge added
 * @param onMST     the current list of nodes on MSt
 * @param notOnMST  the current list of nodes still not on MST and in graph
 * @param copyEdge  the list of edges that we will consider looking through
 */
void updateInfo(Edge* edgeToAdd, std::vector<Node*> &onMST, std::vector<Node*> &notOnMST, std::vector<Edge*> &copyEdge){ 
    onMST.push_back(edgeToAdd->a);
    onMST.push_back(edgeToAdd->b);
    auto itnotOnMST = find(notOnMST.begin(), notOnMST.end(), edgeToAdd->a);
    if(itnotOnMST != notOnMST.end()){
        notOnMST.erase(itnotOnMST);
    }
    itnotOnMST = find(notOnMST.begin(), notOnMST.end(), edgeToAdd->b);
    if(itnotOnMST != notOnMST.end()){
        notOnMST.erase(itnotOnMST);
    }
    auto edgeit =find(copyEdge.begin(), copyEdge.end(), edgeToAdd);
    if(edgeit != copyEdge.end()){
        copyEdge.erase(edgeit);
    }
}
/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to GraphAlgorithms.hpp if you write a helper
 * function!
 *
 */

/**
 * TODO: Implement Prim's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Prim's algorithm
 *
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              onMST and notOnMST are two vectors defined in
 *              GraphAlgorithms.hpp
 *              that you can use to store which nodes are both in/not in the
 *              MST. These are cleared at the start of the MST computation for 
 *              you. To access the nodes that a specific node connects to
 *              you, you can use the vector<Node *> edges which is part
 *              of the Node struct in structs.hpp
 *              You can compare two nodes to see if they are the same by
 *              comparing the id attribute of a Node.
 *              You can calculate distance from one node to another by calling
 *              the double distance(Node a) function of the Node struct.
 *              Whenever you decide to add an edge between two nodes
 *              to the MST, you can use the provided drawEdge function
 *              in GraphAlgorithms.cpp
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * start with a start point
 * construct a visited list
 * add start to visited list
 * while(visited list doesn't not contain every node in graph)
 * for all nodes in tree
 *     find nearest node that connects to the tree
 *     add node of least weight to tree
 *     add node to visited list and remove from unvisited
 * 
 *
 *
 */
void buildMSTPrim(Graph g, GraphApp *app) {

    onMST.erase(onMST.begin(), onMST.end());
    notOnMST.erase(notOnMST.begin(), notOnMST.end());
    for(auto i: g.nodes){
        notOnMST.push_back(i);
    }
    //since we aren't given a node to grow from, we'll grow from a random starting node with an edge to another node that has the
    //shortest connection, ensuring a MST
    std::vector<Edge*> copyEdge;
    for(auto i: g.edges){
        copyEdge.push_back(i);
    }

    Edge* edgeToAdd = copyEdge.front();
    for(auto i: copyEdge){
        if(edgeToAdd->weight > i->weight){
            edgeToAdd = i;
        }
    }

    updateInfo(edgeToAdd, onMST, notOnMST, copyEdge);
    
    drawEdge(edgeToAdd->a,edgeToAdd->b, g.edges,app,true);
    
    while(!notOnMST.empty()){
    auto listOfPotentialEdges = getEdgeFromTree(copyEdge, onMST, notOnMST);
    edgeToAdd = *(listOfPotentialEdges.begin());
    double currentWeight = edgeToAdd->weight;
    for(auto i: listOfPotentialEdges){
        if(i->weight < currentWeight){
            edgeToAdd = i;
        }
    }
    drawEdge(edgeToAdd->a,edgeToAdd->b, g.edges,app,true);
    updateInfo(edgeToAdd, onMST, notOnMST, copyEdge);
    }
}


/**
 * TODO: Implement Kruskal's Algorithm to build the MST.
 *
 * @brief Builds the MST of the given graph with Kruskal's algorithm
 *
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than
 *passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              You'll want to use a priority queue to determine which edges
 *              to add first. We've created the priority queue for you
 *              along with the compare function it uses. All you need to do
 *              is call edge_queue.top(), edge_queue.pop(), edge_queue.push()
 *              The data type that this priority queue stores, KruskalEdge 
 *              is defined in GraphAlgorithms.hpp and is an edge between
 *              any two trees. Each Node has a kruskal_edges attribute to store
 *              all the nodes it connects to in the MST. Make sure to use this
 *              to be able to join trees later!
 *              To know which tree a node is in, use the which_tree attribute.
 *              You can still use the edges, distance, and id
 *              attributes of a Node.
 *              When connecting trees, you can call the
 *              kruskalFloodFill function
 *              defined in structs.hpp on a node to convert it and its
 *              MST connected nodes to a different tree number recursively.
 *              As in Prim's algorith, call drawEdge to add a connection between
 *              two nodes to the MST
 *
 * You can assume that the graph is completely connected. Also, we only use
 * existing edges for the MST.
 *
 * start with each node of the graph as its own tree
 * while number of trees in graph != 1
 *     find the minimal cost edge that connects two trees
 *     connect two trees
 *     
 *
 *
 */
void buildMSTKruskal(Graph g, GraphApp *app) {
    auto compare_func = [](KruskalEdge *a, KruskalEdge *b) {
        return (a->weight > b->weight);
    };
    std::priority_queue<KruskalEdge *, std::vector<KruskalEdge *>,
                        decltype(compare_func)>
        edge_queue(compare_func);

    // Write code here
}

/**
 * TODO: Implement Djikstra's shortest path algorithm.
 *
 * @brief Find the shortest path between start and end nodes with Djikstra's
 *        shortest path algorithm
 *
 * @param start Index of start node of path to find
 *              Can access the Node * element by using
 *              g.nodes[start]
 * @param end   Index of end node of path to find
 *              Can access the Node * element by using g.nodes[end]
 * @param g     Graph object containing vector of nodes and edges
 *              Definition for struct Graph in structs.hpp
 * @param app   Graphics application class
 *              Class definition in GraphApp.hpp
 *              You should not need to use this class other than passing app
 *              as a parameter to drawEdge
 *
 * @attention   Some hints for implementation and how to interact with our code
 *              You can use the distance_to_start attribute of the Node struct
 *              in structs.hpp to keep track of what the distance from each
 *              Node to the start node during computation
 *              You can use the previous attribute of the Node struct
 *              in structs.hpp to keep track of the path you are taking to
 *              later backtrack.
 *              To access the nodes that a specific node connects to you, you
 *              can use the vector<Node *> edges which is part of the Node struct
 *              in structs.hpp
 *              Whenever you decide to add an edge between two nodes
 *              to the MST, you can use the provided drawEdge function in
 *              GraphAlgorithms.cpp
 *
 * Add your outline here
 *
 *
 */
void findShortestPath(int start, int end, Graph g, GraphApp *app) {
    // Write code here
}

/**
 * @brief Adds an edge to either the MST or the shortest path based on the
 *          nodes to connect given. This is done by iterating through the edges
 *          to find the correct edge given the nodes.
 *
 * @param pt1   One side of edge to draw
 * @param pt2   Other side of edge to draw
 * @param edges Vector of edges in the graph
 * @param app   Graphics application class
 * @param mst   True if we are adding edge to MST, False if we are adding edge
 *              to shortest path
 **/

void drawEdge(Node *pt1, Node *pt2, vector<Edge *> edges, GraphApp *app,
              bool mst) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        if ((edges[i]->a == pt1 && edges[i]->b == pt2) ||
            (edges[i]->a == pt2 && edges[i]->b == pt1)) {
            if (mst)
                app->add_to_mst(edges[i]);
            else
                app->add_to_path(edges[i]);
            break;
        }
    }
    return;
}
