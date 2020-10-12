#include "economy.h"

Economy::Economy(const int size, const int connection_size) {
    this->size = size;
    this->connection_size = connection_size;

    createPeople();
    createConnections();
}

void Economy::info() {
    cout << "\n\n";
    cout << size << " people\n";
    cout << connection_size << " connections\n";
    cout << getTrueConnections() << " true connections\n";
    cout << getDebt() << " debt\n";
    cout << getProfit() << " profit\n";
    for (auto person: people) {
        person->info();
    }
}

void Economy::runEconomy() {
    mergeSameConnections();
}

void Economy::createPeople() {
    for (int i = 0; i < size; i++) {
        people.push_back(createPerson());
    }
}

Person *Economy::createPerson() {
    return new Person();
}

void Economy::createConnections() {
    for (int i = 0; i < connection_size; i++) {
        Person *p1 = getPerson();
        Person *p2;
        do {
            p2 = getPerson();
        } while (p2 == p1);
        unsigned int money = getMoneySize();

        Connection p1top2 = {p2, money};
        Connection p2fromp1 = {p1, money};

        p1->addExit(p1top2);
        p2->addEntry(p2fromp1);

        initial_debt += money;

    }
}

unsigned int Economy::getMoneySize() {
    unsigned int number1, number2;

    number1 = (rand() % 1000) + 10;
    number2 = (rand() % 1000) + 10;

    return number1 * number2; // Money between 100 and 1009 * 1009
}

unsigned int Economy::getTrueConnections() const {
    unsigned int connections = 0;
    for (auto person: people) {
        connections += person->getNumberExits();
        connections += person->getNumberEntries();
    }
    return connections / 2;
}

unsigned int Economy::getDebt() const {
    unsigned int debt = 0;
    for (auto person: people) {
        debt += person->getDebt();
    }
    return debt;
}

unsigned int Economy::getProfit() const {
    unsigned int profit = 0;
    for (auto person: people) {
        profit += person->getProfit();
    }
    return profit;
}

Person *Economy::getPerson() const {
    return people[rand() % size];
}

void Economy::mergeSameConnections() {

    for (auto person: people) {
        person->mergeSameExits();
        person->mergeSameEntries();
    }
}

void Economy::nulifyMutualDebt() {
    for(auto person: people){
        person->nulifyMutualDebt();
    }
}

void Economy::transposeDebt() {
}