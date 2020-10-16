#include "graph.h"

using namespace std;

void Node::info() {
    cout << entries.size() << " entries\n";
    cout << profit << " profit\n";
    cout << exits.size() << " exits\n";
    cout << debt << " debt\n";
    cout << getNetProfit() << " net profit\n";
}

Node *Node::addEntry(Connection entry) {
    profit += entry.weight;
    entries.push_back(entry);
    return this;
}

Node *Node::addExit(Connection exit) {
    debt += exit.weight;
    exits.push_back(exit);
    return this;
}

bool Node::connectionToThisNode(Connection *connection) const {
    return this == connection->connection;
}

bool Node::hasExitNode(Node *node) {
    return getExitConnectionToNode(node) != exits.end();
}

bool Node::hasEntryNode(Node *node) {

    return getEntryConnectionToNode(node) != entries.end();
}

unsigned int Node::getDebt() const {
    return debt;
}

unsigned int Node::getProfit() const {
    return profit;
}

int Node::getNetProfit() const {
    return profit - debt;
}

int Node::getNumberExits() const {
    return exits.size();
}

int Node::getNumberEntries() const {
    return entries.size();
}

__gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
Node::getExitConnectionToNode(Node *node) {
    //https://stackoverflow.com/a/15518039

    return find_if(exits.begin(), exits.end(),
                   [node](const Connection &exit_connection) { return exit_connection.connection == node; });
}

__gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>>
Node::getEntryConnectionToNode(Node *node) {
    //https://stackoverflow.com/a/15518039

    return find_if(entries.begin(), entries.end(),
                   [node](const Connection &entry_connection) { return entry_connection.connection == node; });
}


void Node::mergeSameExits() {
    for (auto it = exits.begin(); it != exits.end(); it++) {
        for (auto it2 = exits.begin(); it2 != exits.end(); it2++) {
            if ((*it2).connection == (*it).connection && it != it2) { //We can merge an exit
                (*it).weight += (*it2).weight;
                exits.erase(it2);
                it2 -= 1;
            }
        }
    }
}

void Node::mergeSameEntries() {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        for (auto it2 = entries.begin(); it2 != entries.end(); it2++) {
            if ((*it2).connection == (*it).connection && it != it2) { //We can merge an exit
                (*it).weight += (*it2).weight;
                entries.erase(it2);
                it2 -= 1;
            }
        }
    }
}

void Node::nulifyMutualDebt() {

    // Run the exits and see if any of them has an exit to this node
    for (auto it = exits.begin(); it != exits.end(); it++) {
        Node *other_node = (it->connection);

        if (other_node->hasExitNode(this)) {
            // They have an exit to each other

            auto others_exit_connection = other_node->getExitConnectionToNode(this);
            auto others_entry_connection = other_node->getEntryConnectionToNode(this);
            unsigned int weight_to_change = min(it->weight, others_exit_connection->weight);
            bool erased_iterator = false;


            //Diminish entry and exit connections on both nodes
            other_node->diminishConnectionWeight(others_exit_connection, weight_to_change);
            other_node->diminishConnectionWeight(others_entry_connection, weight_to_change);
            erased_iterator = diminishConnectionWeight(it, weight_to_change); //We might be deleting this connection. If so, iterator needs to be decremeted to properly run next iteration
            diminishConnectionWeight(getEntryConnectionToNode(other_node), weight_to_change);

            if (erased_iterator) {
                it -= 1;
            }
        }

    }

}

bool Node::diminishConnectionWeight(
        __gnu_cxx::__normal_iterator<Connection *, vector<Connection, allocator<Connection>>> connection,
        unsigned int to_diminish) {
    if (connection->weight < to_diminish) {
        return false;
    }
    bool erased_connection = false;
    connection->weight -= to_diminish; //Diminish the weight
    // Didn't work

    //Also, didn't detect connection as belonging to any of the vectors

    if (connection >= exits.begin() && connection < exits.end()) {
        // iterator to an exit. Alter the exit
        debt -= to_diminish; // The debt diminishes
        if (connection->weight == 0) { // The value of the connection is now 0
            exits.erase(connection);
            erased_connection = true;
        }
    }

    if (connection >= entries.begin() && connection < entries.end()) {
        // iterator to an entry. Alter the entry
        profit -= to_diminish; // The profit diminishes
        if (connection->weight == 0) { // The value of the connection is now 0
            entries.erase(connection);
            erased_connection = true;
        }
    }
    return erased_connection;
}