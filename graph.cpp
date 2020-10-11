#include "graph.h"

using namespace std;

void Node::info() {
    cout << entries.size() << " entries\n";
    cout << profit << " profit\n";
    cout << exits.size() << " exits\n";
    cout << debt << " debt\n";
    cout << getNetProfit() << " net profit\n";
}
Node * Node::addEntry(Connection *entry)
{
    profit += entry->weight;
    entries.push_back(entry);
    return this;
}

Node * Node::addExit(Connection *exit)
{
    debt += exit->weight;
    exits.push_back(exit);
    return this;
}

unsigned int Node::getDebt() const{
    return debt;
}

unsigned int Node::getProfit() const{
    return profit;
}

int Node::getNetProfit() const {
    return profit - debt;
}