#ifndef ECONOMY_H
#define ECONOMY_H

#include <iostream>
#include <random>
#include "person.h"


using namespace std;

class Economy {

public:

    void info();

    void runEconomy();

    void createRandomEconomy(int size, int connection_size);

    void createConnection(Person* p1, Person* p2, unsigned int money);

    Person *createPerson();

    unsigned int getTrueConnections() const;

    unsigned int getDebt() const;

    unsigned int getProfit() const;

    Person *getRandomPerson() const;

private:

    void createPeople(int size);

    void createRandomConnections(int connection_size);

    static unsigned int createRandomMoneySize() ;

    void mergeSameConnections();

    void nulifyMutualDebt();

    void transposeDebt(); //A to B to C transforms i A to C

    unsigned int initial_debt = 0;
    unsigned int size = 0;
    unsigned int connection_size = 0;

    vector<Person *> people;
};

#endif // !ECONOMY_H
