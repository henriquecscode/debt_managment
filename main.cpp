#include "economy.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;


const int POP_SIZE = 2000000;
const int CONNECTION_SIZE = 1000000;

string function(int i) {

    string name = "";
    int number = i;
    int char_code;
    while (number >= 26) {
        char_code = number % 26;
        name = char(char('a') + char_code) + name;
        number = number / 26;
    }
    char_code = number % 26;
    name = char(char('a') + char_code) + name;
    number = number / 26;
    return name;
}


void test1() {
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();

    economy.createConnection(a, b, 10);
    economy.createConnection(a, b, 20);
    economy.createConnection(a, c, 30);
    economy.createConnection(a, c, 20);
    economy.createConnection(a, b, 20);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void test2() {
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    Person *d = economy.createPerson();
    economy.createConnection(a, b, 10);
    economy.createConnection(a, b, 20);
    economy.createConnection(a, c, 30);
    economy.createConnection(a, c, 20);
    economy.createConnection(a, b, 20);
    economy.createConnection(a, d, 10);
    economy.createConnection(b, a, 20);
    economy.createConnection(c, a, 50);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void test3(){
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    economy.createConnection(a, b, 10);
    economy.createConnection(b, c, 10);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void test4(){
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    economy.createConnection(a, b, 20);
    economy.createConnection(b, c, 10);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void test5(){
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    economy.createConnection(a, b, 10);
    economy.createConnection(b, c, 20);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void test6(){
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    Person *d = economy.createPerson();
    economy.createConnection(d, b, 5);
    economy.createConnection(a, b, 10);
    economy.createConnection(b, c, 20);
    economy.info();
    economy.runEconomy();
    economy.info();
}


void test7(){
    Economy economy;
    Person *a = economy.createPerson();
    Person *b = economy.createPerson();
    Person *c = economy.createPerson();
    Person *d = economy.createPerson();
    economy.createConnection(d, b, 10);
    economy.createConnection(a, b, 10);
    economy.createConnection(b, c, 20);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void run(){
    Economy economy;
    economy.createRandomEconomy(POP_SIZE, CONNECTION_SIZE);
    economy.info();
    economy.runEconomy();
    economy.info();
}

void metaRun(){
    ofstream output;
    output.open("results.txt");
    std::stringstream ss;
    unsigned long long initial_profit, final_profit, initial_connections, final_connections;
    double ratio;
    for(double i = 100; i < 5000000; i*=1.4){
        std::stringstream ss;
        Economy economy;
        economy.createRandomEconomy((int)i, (int) i/2);
        initial_profit = economy.getProfit();
        initial_connections = economy.getTrueConnections();
        economy.runEconomy();
        final_profit = economy.getProfit();
        final_connections = economy.getTrueConnections();
        ratio = (double) final_profit / initial_profit;
        ss << (int)i << ' ' << initial_profit << ' ' << initial_connections << ' ' <<
        final_profit << ' ' << final_connections << ' ' <<ratio << '\n';
        std::cout <<ss.str();
        output << ss.str();

    }
}

int main() {
    srand(70);
    //run();
    //TODO
    //Make a function to remove nodes with no exits and no entries (size should remain the same)
    metaRun();
    return 0;
}