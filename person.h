#ifndef PERSON_H
#define PERSON_H

#include "graph.h"
#include <string>

class Person : public Node
{
public:

    Person();

private:
    static unsigned int person_number;
    string name;

    string getNameFromNumber();
};

#endif // !PERSON_H