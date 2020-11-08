#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Node;
class Person : public Node {
    /*!
     * @brief Number of Person objects created
     */
    static unsigned int person_number;

public:

    /*!
     * @brief Creates a person
     * @details Creates a person, automatically giving it a alphabetical name
     */
    Person();

    /*!
     * @brief Prints information about the person
     * @details Prints the person's Person::name and its Node info
     * @see Node::info
     */
    void info();

    /*!
     * @brief Generates a name from the person's number
     * @details Generates a alphabetical name, according to the number of people already created
     */
    string getNameFromNumber();

private:
    /*!
     * @brief Name of the person
     */
    string name;

};

#endif // !PERSON_H