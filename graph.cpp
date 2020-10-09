#include "graph.h"

using namespace std;

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