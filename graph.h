#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Economy;
class Node;

struct Connection {

    ~Connection(){
    }

    Connection(){}

    Connection(Node *n, unsigned int w){
        connection = n;
        weight = w;
    }
    Connection &operator=(const Connection &c){
        connection = c.connection;
        weight = c.weight;
        return *this;
    }

    Node *connection;
    unsigned int weight;

    bool operator==(const Connection &c2) {
        return connection == c2.connection && weight == c2.weight;
    }
};


class Node {

    unsigned int debt = 0, profit = 0;
    vector<Connection> entries, exits;
public:
    Node() {
    }

    void info();

    void addEntry(Connection entry);

    void addEntry(Node * n, unsigned int money);

    void removeEntry(Connection c);

    void removeEntryTo(Node *n);

    void addExit(Connection exit);

    void addExit(Node * n, unsigned int money);

    void removeExit(Connection c);

    void removeExitTo(Node *n);

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

    void turnToOneWayNode();

    //Node only has exits or entries
    bool IsOneWayNode();

    //Should return the same iterator if didn't delete, the next otherwise
    bool diminishConnectionWeight(
            __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>> connection,
            unsigned int to_diminish);

    void diminishEntryTo(Node *n, unsigned int amount);

    void diminishExitTo(Node *n, unsigned int amount);
};


#endif // !GRAPH_H
