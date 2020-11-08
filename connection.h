//
// Created by henri on 08/11/2020.
//

#ifndef DEBT_MANAGMENT_CONNECTION_H
#define DEBT_MANAGMENT_CONNECTION_H

class Node;

struct Connection {

    ~Connection(){
    }

    Connection(){}

    Connection(Node *n, unsigned int w){
        connection = n;
        weight = w;
    }
    Connection &operator=(const Connection &c){
        connection = c.connection;
        weight = c.weight;
        return *this;
    }

    /*!
     * @brief The Node it connects to
     */
    Node *connection;

    /*!
     * @brief The weight of the connection
     */
    unsigned int weight;

    /*!
     * @brief If the connections are equal
     * @details If the node and the weight are equal
     * @param c2 Connection to compare to
     * @return true if equal, false otherwise
     */
    bool operator==(const Connection &c2) {
        return connection == c2.connection && weight == c2.weight;
    }
};


#endif //DEBT_MANAGMENT_CONNECTION_H
