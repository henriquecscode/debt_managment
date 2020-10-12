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

void Node::mergeSameExits() {
    for (auto it = exits.begin(); it != exits.end(); it++) {
        for (auto it2 = exits.begin(); it2 != exits.end(); it2++) {
            if ((*it2).connection == (*it).connection && it != it2) { //We can merge an exit
                (*it).weight += 1;
                exits.erase(it2);
                it2-=1;
            }
        }
    }
}

void Node::mergeSameEntries() {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        for (auto it2 = entries.begin(); it2 != entries.end(); it2++) {
            if ((*it2).connection == (*it).connection && it != it2) { //We can merge an exit
                (*it).weight += 1;
                entries.erase(it2);
                it2-=1;
            }
        }
    }
}