#ifndef ECONOMY_H
#define ECONOMY_H

#include <iostream>
#include <vector>

using namespace std;

class Person;

class Economy {

public:

    /*!
     * @brief Prints information about the economy
     * @details Print the size, the number of original connections, current connections, debt and profit
     */
    void info();

    /*!
     * @brief Runs the economy, trying to diminish debt and profit
     * @details First joins all the connections to an equal node, then mutual debt is nulified. Lastly, makes so each node only has eithe debt or profit
     */
    void runEconomy();

    /*!
     * @brief Creates a random economy
     * @param size The number of people in the econmy
     * @param connection_size The number debt/profit connections
     */
    void createRandomEconomy(int size, int connection_size);

    /*!
     * @brief Creates a debt from p1 to p2 of value money
     * @param p1 The person who owes
     * @param p2 The person who is owed to
     * @param money The amount that is owed
     */
    void createConnection(Person* p1, Person* p2, unsigned int money);

    /*!
     * @brief Adds a person to the economy
     * @details Creates a new person object and adds it to people in the economy
     */
    Person *createPerson();

    /*!
     * @brief Number of connections
     * @details Gets the number of exits and connections from each person
     * @returns Total number of connections on the economy
     */
    unsigned int getTrueConnections() const;

    /*!
     * @brief Total debt in the economy
     * @details Gets the debt from each person
     * @returns Total debt in the economy
     */
    unsigned long long int getDebt() const;

    /*!
    * @brief Total profit in the economy
    * @details Gets the profit from each person
    * @returns Total profit in the economy
    */
    unsigned long long int getProfit() const;

    /*!
     * @brief Selects a random person
     * @details Selects a random person from #people
     * @returns Pointer to the Person being returned
     *
     */
    Person *getRandomPerson() const;

private:

    /*!
     * @brief Creates the people in the economy
     * @details Creates the people and adds them to people
     * @param size Number of people to be created
     *
     */
    void createPeople(int size);

    /*!
     * @brief Creates random connections for the economy
     * @details Creates random connections between elements of #people
     * @param connection_size The number of connections to be created
     */
    void createRandomConnections(int connection_size);


    /*!
     * @brief Creates a random money size
     * @details Creates a random value according to a certain distribution
     * @returns Money size
     */
    static unsigned int createRandomMoneySize() ;

    /*!
     * @brief Removes empty nodes
     * @details Removes people that have no debt nor profit
     */
    void removeEmptyNodes();

    /*!
     * @brief Simplifies all connections to the same person
     * @details Each person has the connections to a same person merged
     */
    void mergeSameConnections();

    /*!
     * @brief Mutual debt is eliminated
     * @details If two people owe each other, debt is forgiven accordingly
     */
    void nulifyMutualDebt();

    /*!
     * @brief The debt and profit from a person is associated to the people they owe to and who owes them
     * @details If A owes B and B owes C, then we make it so A owes C. We apply this process to everyone
     */
    void transposeDebt(); //A to B to C transforms i A to C

    /*!
     * @brief Initial debt of the economy
     * @details DEbt of the economy after the initial connections being created
     */
    unsigned int initial_debt = 0;

    /*!
     * @brief Number of people in the economy

     */
    unsigned int size = 0;

    /*!
     * @brief Connections in the economy
     * @details Connections the economy was initialized with
     */
    unsigned int connection_size = 0;

    /*!
     * @brief People in the economy
     */
    vector<Person *> people;
};

#endif // !ECONOMY_H
