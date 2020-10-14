#ifndef ECONOMY_H
#define ECONOMY_H

#include <iostream>
#include <random>
#include "person.h"


using namespace std;

class Economy {

public:
    Economy(int size, int connection_size);

    void info();

    void runEconomy();

private:

    void createPeople();

    static Person *createPerson();

    void createConnections();

    void createConnection(Person* p1, Person* p2, unsigned int money);

    static unsigned int getMoneySize() ;

    unsigned int getTrueConnections() const;

    unsigned int getDebt() const;

    unsigned int getProfit() const;

    Person *getRandomPerson() const;

    void mergeSameConnections();

    void nulifyMutualDebt();

    void transposeDebt(); //A to B to C transforms i A to C

    unsigned int initial_debt = 0;
    unsigned int size = 0;
    unsigned int connection_size = 0;

    vector<Person *> people;
};

#endif // !ECONOMY_H
