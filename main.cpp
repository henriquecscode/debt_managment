#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "economy.h"

using namespace std;


const int POP_SIZE = 10;
const int CONNECTION_SIZE = 90;

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

int main() {
    test5();
    return 0;
}