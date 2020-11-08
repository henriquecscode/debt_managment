#include "node.h"
#include "person.h"

unsigned int Person::person_number = 0;

Person::Person() : Node()
{

    name = getNameFromNumber();
    person_number += 1;
}

void Person::info() {
    cout << "\nPerson " << name << '\n';
    Node::info();

}

string Person::getNameFromNumber()
{
    string name = "";
    int number = person_number;
    int char_code;
    while (number >= 26)
    {
        char_code = number % 26;
        name = char(char('a') + char_code) + name;
        number = number / 26;
    }
    char_code = number % 26;
    name = char(char('a') + char_code) + name;
    return name;
}