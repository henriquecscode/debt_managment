#include "economy.h"
#include "time.h"
#include <fstream>
#include <string>

void Economy::info() {
    cout << "\n\n";
    cout << size << " people\n";
    cout << connection_size << " connections\n";
    cout << getTrueConnections() << " true connections\n";
    cout << getDebt() << " debt\n";
    cout << getProfit() << " profit\n";
    /*
    for (auto person: people) {
        person->info();
    }
     */
}

void Economy::runEconomy() {
    mergeSameConnections();
    nulifyMutualDebt();
    transposeDebt();
}

void Economy::createRandomEconomy(int size, int connection_size) {
    createPeople(size);
    createRandomConnections(connection_size);
    removeEmptyNodes();
}

void Economy::createConnection(Person *p1, Person *p2, unsigned int money) {
    Connection p1top2 = {p2, money};
    Connection p2fromp1 = {p1, money};

    p1->addExit(p1top2);
    p2->addEntry(p2fromp1);

    initial_debt += money; // createdConnections (independtly of time of creation) always count to initial debt
    connection_size += 1;
}

Person *Economy::createPerson() {
    Person *p = new Person();
    people.push_back(p);
    size += 1;
    return p;
}

unsigned int Economy::getTrueConnections() const {
    //static int run = 0;
    //std::ofstream file; //Debug
    //file.open(to_string(time(NULL)) +' ' + to_string(run)+ ".txt"); //Debug
    unsigned int connections = 0, entries, exits;
    for (auto person: people) {
        entries = person->getNumberEntries();
        exits = person->getNumberExits();
        //file << person << ' ' << person->getProfit() << ' ' << person->getDebt() << ' ' << entries << ' ' << exits << '\n';
        connections += entries + exits;
    }
    //file << connections << '\n';
    //run += 1;

    return connections;

}

unsigned long long int Economy::getDebt() const {
    unsigned long long debt = 0;
    for (auto person: people) {
        debt += person->getDebt();
    }
    return debt;
}

unsigned long long int Economy::getProfit() const {
    unsigned long long profit = 0;
    for (auto person: people) {
        profit += person->getProfit();
    }
    return profit;
}

Person *Economy::getRandomPerson() const {
    return people[rand() % size];
}


void Economy::createPeople(int size) {
    for (int i = 0; i < size; i++) {
        createPerson();
    }
}


void Economy::createRandomConnections(int connection_size) {
    for (int i = 0; i < connection_size; i++) {
        Person *p1 = getRandomPerson();
        Person *p2;
        do {
            p2 = getRandomPerson();
        } while (p2 == p1);
        unsigned int money = createRandomMoneySize();

        createConnection(p1, p2, money);

    }
}


unsigned int Economy::createRandomMoneySize() {
    unsigned int number1, number2;

    number1 = (rand() % 100) + 1;
    number2 = (rand() % 100) + 1;

    return number1 * number2; // Money between 100 and 1009 * 1009
}

void Economy::removeEmptyNodes() {
    for (auto it = people.begin(); it != people.end();) {
        if ((*it)->getNumberEntries() == 0 && (*it)->getNumberExits() == 0) {
            //Node is empty
            it = people.erase(it);
        } else {
            it++;
        }
    }
}

void Economy::mergeSameConnections() {

    for (auto person: people) {
        person->mergeSameExits();
        person->mergeSameEntries();
    }
}

void Economy::nulifyMutualDebt() {
    for (auto person: people) {
        person->nulifyMutualDebt();
    }
}

void Economy::transposeDebt() {

    bool succesfull = true;
    for (auto it = people.begin(); it != people.end(); it++) {
        (*it)->turnToOneWayNode();
        succesfull &= (*it)->IsOneWayNode();
        /*
        if(getDebt() != getProfit()){
            std::cout << it - people.begin() << '\n' ;
        }
         */
    }
}