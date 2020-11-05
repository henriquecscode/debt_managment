#include "graph.h"
#include "economy.h"

using namespace std;

void Node::info() {
    cout << entries.size() << " entries\n";
    cout << profit << " profit\n";
    cout << exits.size() << " exits\n";
    cout << debt << " debt\n";
    cout << getNetProfit() << " net profit\n";
}

void Node::addEntry(Connection entry) {
    profit += entry.weight;
    entries.push_back(entry);
}

void Node::addEntry(Node *n, unsigned int money) {
    Connection c = {n, money};
    addEntry(c);
}

void Node::removeEntry(Connection c) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        if (*it == c) {
            profit -= c.weight;
            entries.erase(it);
            return;
        }
    }
}

void Node::removeEntryTo(Node *n) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        if ((*it).connection == n) {
            profit -= (*it).weight;
            entries.erase(it);
            return;
        }
    }
}

void Node::addExit(Connection exit) {
    debt += exit.weight;
    exits.push_back(exit);
}

void Node::addExit(Node *n, unsigned int money) {
    Connection c = {n, money};
    addExit(c);
}

void Node::removeExit(Connection c) {
    for (auto it = exits.begin(); it != exits.end(); it++) {
        if (*it == c) {
            debt -= c.weight;
            exits.erase(it);
            return;
        }
    }
}

void Node::removeExitTo(Node *n) {
    for (auto it = exits.begin(); it != exits.end(); it++) {
        if ((*it).connection == n) {
            debt -= (*it).weight;
            exits.erase(it);
            return;
        }
    }
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

void Node::turnToOneWayNode() {
    unsigned int entry_debt, exit_debt, transfer_size;
    Node *entry_node, *exit_node;
    bool erased_entry;
    Connection new_entry_connection, new_exit_connection;
    for (auto it = entries.begin(); it != entries.end(); it = entries.begin()) {
        entry_debt = it->weight;
        entry_node = it->connection;
        for (auto it2 = exits.begin(); it2 != exits.end(); it2 = exits.begin()) {
            exit_debt = it2->weight;
            exit_node = it2->connection;

            transfer_size = min(entry_debt, exit_debt);
            new_entry_connection = {entry_node, transfer_size};
            new_exit_connection = {exit_node, transfer_size};
            /*
            new_entry_connection.connection = entry_node;
            new_entry_connection.weight = transfer_size;
            new_exit_connection.connection = exit_node;
            new_exit_connection.weight = transfer_size;
            */
            //economy.createConnection((Person*) entry_node, (Person*)exit_node, transfer_size);
            entry_node->addExit(exit_node, transfer_size);
            entry_node->diminishExitTo(this, transfer_size);
            exit_node->addEntry(entry_node, transfer_size); //segfault: probably because of previous stuff (diminish entry and exit?)
            exit_node->diminishEntryTo(this, transfer_size);

            erased_entry = diminishConnectionWeight(it, transfer_size);
            diminishConnectionWeight(it2, transfer_size);


            if (erased_entry) {
                break;
            }

        }


        if (exits.size() == 0) { // We have run out of exits to which redirect debt
            return;
        }
    }
}

bool Node::IsOneWayNode() {
    return exits.size() == 0 || entries.size() == 0;
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

void Node::diminishEntryTo(Node *n, unsigned int amount) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        if ((*it).connection == n) {
            profit -= amount;
            (*it).weight -= amount;
            if((*it).weight == 0) {
                entries.erase(it);
            }
            return;
        }
    }
}

void Node::diminishExitTo(Node *n, unsigned int amount) {
    for (auto it = exits.begin(); it != exits.end(); it++) {
        if ((*it).connection == n) {
            debt -= amount;
            (*it).weight -= amount;
            if((*it).weight == 0) {
                exits.erase(it);
            }
            return;
        }
    }
}