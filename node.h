#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "connection.h" //Had to include due to some problem with forward declaration and incomplete types

using namespace std;

class Economy;

struct Connection;


class Node {

    /*!
     * @brief Total debt of the Node
     */
    unsigned int debt = 0;

    /*!
     * @brief Total profit of the Node
     */
    unsigned int profit = 0;

    /*!
     * @brief Entries to the Node
     */
    vector<Connection> entries;

    /*!
     * @brief Exits from the Node
     */
    vector<Connection> exits;

public:

    /*!
     * @brief Prints the Node information
     * @details Prints the size of the Node's entries, the #profit, the size of the nodes exits, #debt, and the net profit
     */
    void info();

    /*!
     * @brief Adds an entry
     * @details Adds an entry to a certain Node and with a certain weight
     * @param entry The connection to be added
     *
     */
    void addEntry(Connection entry);

    /*!
     * @brief Adds an entry
     * @details Adds an entry to a specified node with a specified weight
     * @param n Entry Node
     * @param money Money involved in the connection
     */
    void addEntry(Node *n, unsigned int money);

    /*!
     * @brief Removes entry with Connection c
     * @param c Connection to be removed
     * @details Removes Connection c and updates #profit
     */
    void removeEntry(Connection c);

    /*!
     * @brief Removes entry to node n
     * @param n Node whose entry is going to be removed
     * @details Removes the connection with the node n and updates #profit
    */
    void removeEntryTo(Node *n);

    /*!
    * @brief Adds an exit
     * @details Adds an exit to a certain Node and with a certain weight
     * @param exit The connection to be added
     *
     */
    void addExit(Connection exit);

    /*!
     * @brief Adds an exit
     * @details Adds an exit to a specified node with a specified weight
     * @param n Exit Node
     * @param money Money involved in the connection
     */
    void addExit(Node *n, unsigned int money);

    /*!
     * @brief Removes exit with Connection c
     * @param c Connection to be removed
     * @details Removes Connection c and updates #debt
     */
    void removeExit(Connection c);

    /*!
     * @brief Removes exit to node n
     * @param n Node whose exit is going to be removed
     * @details Removes the connection with the node n and updates #debt
    */
    void removeExitTo(Node *n);

    /*!
     * @brief If the connection is to this node
     * @details Returns if the param connection is pointing to this node
     * @param connection Connection that we are going to check
     * @returns true if connection points to this, false otherwise
     */
    bool connectionToThisNode(Connection *connection) const;

    /*!
     * @brief If this has an exit to the node
     * @param node Node to check if is in #exits
     * @returns true if node in #exits, false otherwise
     */
    bool hasExitNode(Node *node);

    /*!
     * @brief If this has an entry from the node
     * @param node Node to check if is in #entries
     * @returns true if node in #entries, false otherwise
     */
    bool hasEntryNode(Node *node);

    /*!
     * @brief Gets the debt of the Node
     * @return #debt amount
     */
    unsigned int getDebt() const;

    /*!
     * @brief Gets the profit of the Node
     * @return #profit amount
     */
    unsigned int getProfit() const;

    /*!
     * @brief Gets the net profit
     * @details Difference between #profit and #debt
     * @return Net profit
     */
    int getNetProfit() const;

    /*!
     * @brief Gets the number of entries
     * @return Number of entries
     */
    int getNumberEntries() const;

    /*!
     * @brief Gets the number of exits
     * @return Number of exits
     */
    int getNumberExits() const;

    /*!
     * @brief Gets an iterator to the a certain entry node
     * @param node The node that the entry connection points to
     * @return An iterator to the entry with that node, last otherwise
     */
    __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
    getEntryConnectionToNode(Node *node) /*const*/;

    /*!
    * @brief Gets an iterator to the a certain exit node
    * @param node The node that the exit connection points to
    * @return An iterator to the exit with that node, last otherwise
    */
    __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
    getExitConnectionToNode(Node *node) /*const*/;

    /*!
     * @brief Merges the entry connections to the same node
     */
    void mergeSameEntries();

    /*!
     * @brief Merges the exit connections to the same node
     */
    void mergeSameExits();

    /*!
     * @brief Settles the debt that two people own each other
     * @details If A owes B and B owes A, makes so just one person owes another
     */
    void nulifyMutualDebt();

    /*!
     * @brief Eliminates either all debt or all profit
     * @details If A owes B and B owes C, then we make it so A owes C and B doesn't owe/profit as much.
     * While one of #exits/#entries is not empty, gets an entry node and an exit node, eliminates debt from the entry, profit from the exit, and makes so the entry node owes the exit node instead
     */
    void turnToOneWayNode();

    /*!
     * @brief If the Node only has exits or only has entries
     * @return true if only has exits or only has entries, false otherwise
     */
    bool IsOneWayNode();

    /*!
     * @brief Diminshes the weight of connection and returns if the connection was deleted
     * @param connection Iterator to the connection that we are going to diminish
     * @param to_diminish Amount to diminish the connection weight
     * @return true if deleted the connection, false otherwise
     */
    //Should return the same iterator if didn't delete, the next otherwise
    bool diminishConnectionWeight(
            __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>> connection,
            unsigned int to_diminish);

    /*!
     * @brief Diminishes the weight of the entry to the node
     * @param node Diminishes the weight from the entry node, decreasing this' profit
     * @param amount Amount to diminish the entry weight
     */
    void diminishEntryFrom(Node *node, unsigned int amount);

    /*!
     * @brief Diminishes the weight of the exit to the node
     * @param node Diminishes the weight to the exit node, decreasing this' debt
     * @param amount Amount to diminish the exit weight
     */
    void diminishExitTo(Node *node, unsigned int amount);
};


#endif // !GRAPH_H
