#ifndef GRAPH_H
#define GRAPH_H

#include <vector>


using namespace std;


class Node;

struct Connection{

    Node * connection;
    unsigned int weight;
};

class Node{

    unsigned int debt = 0, profit = 0;
    vector<Connection *> entries, exits;
    public:
        Node(){
        }

        Node * addEntry(Connection * entry);

        Node *addExit(Connection *exit);

        unsigned int getDebt() const;

        unsigned int getProfit() const;
};


#endif // !GRAPH_H
