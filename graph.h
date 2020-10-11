#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>

using namespace std;


class Node;

struct Connection {

    Node *connection;
    unsigned int weight;
};

class Node {

    unsigned int debt = 0, profit = 0;
    vector<Connection *> entries, exits;
public:
    Node() {
    }

    void info();

    Node *addEntry(Connection *entry);

    Node *addExit(Connection *exit);

    unsigned int getDebt() const;

    unsigned int getProfit() const;

    int getNetProfit() const;
};


#endif // !GRAPH_H
