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

int main() {
    srand(time(NULL));
    Economy economy(POP_SIZE, CONNECTION_SIZE);
    economy.createRandomEconomy();
    economy.info();
    economy.runEconomy();
    economy.info();
    char x;
    cin >> x;
}