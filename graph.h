#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;


class Node;

struct Connection {

    Node *connection;
    unsigned int weight;
};

class Node {

    unsigned int debt = 0, profit = 0;
    vector<Connection> entries, exits;
public:
    Node() {
    }

    void info();

    Node *addEntry(Connection entry);

    Node *addExit(Connection exit);

    bool connectionToThisNode(Connection *connection) const;

    bool hasExitNode(Node *node);

    bool hasEntryNode(Node *node);

    unsigned int getDebt() const;

    unsigned int getProfit() const;

    int getNetProfit() const;

    int getNumberExits() const;

    int getNumberEntries() const;

    __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
    getExitConnectionToNode(Node *node) /*const*/;

    __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
    getEntryConnectionToNode(Node *node) /*const*/;

    void mergeSameExits();

    void mergeSameEntries();

    void nulifyMutualDebt();

    bool diminishConnectionWeight(
            __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>> connection,
            unsigned int to_diminish);
};


#endif // !GRAPH_H
