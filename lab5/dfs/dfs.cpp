/* debugging example */

#include <iostream>
#include <vector>

class Node
{
    int value;
    std::vector<Node*> edges;
public:
    // insert constructors, destructors,
    // accessors, and mutators here
    Node(int _value, std::vector<Node*> _edges){
        this->value = _value;
        this->edges = _edges;
    }
    void addEdge(Node* _node);
    bool dfs(int to_find);
};

// true indicates that the value was found, and false indicates that the value was not found.
void Node::addEdge(Node* _node){
    this->edges.push_back(_node);
}

bool Node::dfs(int to_find)
{
    if(this->value == to_find)
    {
        return true;
    }
    std::vector<Node*>::iterator i;
    for(i = this->edges.begin(); i != this->edges.end(); i++)
    {
        Node * n = *i;
        bool r = n->dfs(to_find);
        if(r)
        {
            return r;
        }
    }
    return false;
}

int main(void)
{
    // TODO: Write your test code here
    // here implements a simple graph with one branch like this
/* 
 +----+            +----+          +-----+
 |  S |  <------>  | F2 |  +---->  |  T  |
 |    |            |    |          |     |
 +-+--+            +-+--+          +-----+
   |                 ^
   |                 |
   v                 v
+--+---+          +--+--+
|  B   +--------> |  F1 | <-------- +-----+
|      |          |     |           | I   |
+------+          +-----+           |     |
                                    +-----+
*/ 
// this has a cycle which breaks the find algorithm
// to fix it, I would implement a visited list so that the dfs 
// doesn't keep looking at the same nodes in the cycle

    Node* T = new Node(5, std::vector<Node*>());
    Node* F1 = new Node(3, std::vector<Node*>());
    Node* F2 = new Node(1, std::vector<Node*>());
    Node* I = new Node(8, std::vector<Node*>());
    Node* B = new Node(4, std::vector<Node*>());
    Node* S = new Node(2, std::vector<Node*>());
    S->addEdge(B);
    S->addEdge(F2);
    B->addEdge(F1);
    F2->addEdge(S);
    F2->addEdge(F1);
    F2->addEdge(T);
    F1->addEdge(F2);
    I->addEdge(F1);
    
    if(S->dfs(5)){
        std::cout<<"value found" << std::endl;
    }else{
        std::cout<<"value not found" << std::endl;
    }
    return 0;

}