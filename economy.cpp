#include "economy.h"

Economy::Economy(const int size, const int connection_size)
{
    this->size = size;
    this->connection_size = connection_size;

    createPeople();
    createConnections();
}

void Economy::run()
{
}

void Economy::createPeople()
{
    for (int i = 0; i < size; i++)
    {
        people.push_back(createPerson());
    }
}

Person *Economy::createPerson() const
{
    return new Person();
}

void Economy::createConnections()
{
    for (int i = 0; i < connection_size; i++)
    {
        Person *p1 = getPerson();
        Person *p2;
        do
        {
            p2 = getPerson();
        } while (p2 == p1);
        unsigned int money = getMoneySize();

        Connection p1top2 = {p2, money};
        Connection p2fromp1 = {p1, money};

        p1->addExit(&p1top2);
        p2->addEntry(&p2fromp1);

    }
}

Person *Economy::getPerson() const
{
    return people[rand() % size];
}
unsigned int Economy::getMoneySize() const
{
    unsigned int money;
    do{
    }while(money < 1 || money > 100000000);
}

void Economy::randomizeEconomy()
{
}

void Economy::transposeDebt()
{
}