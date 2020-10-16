#ifndef PERSON_H
#define PERSON_H

#include "graph.h"
#include <string>
#include <iostream>

using namespace std;
class Person : public Node {
    static unsigned int person_number;

public:

    Person();

    void info();

    string getNameFromNumber();

private:
    string name;

};

#endif // !PERSON_H