#ifndef ECONOMY_H
#define ECONOMY_H

#include <iostream>
#include "person.h"

using namespace std;
class Economy
{

public:
    Economy(const int size, const int connection_size);
    void info();

private:

    void run();

    void createPeople();

    static Person *createPerson() ;

    void createConnections();

    void processEconomy();

    unsigned int getMoneySize() const;

    Person *getPerson() const;

    void randomizeEconomy();

    void transposeDebt(); //A to B to C transforms i A to C

    unsigned int initial_debt = 0;
    unsigned int size = 0;
    unsigned int connection_size = 0;

    vector<Person *> people;
};

#endif // !ECONOMY_H
