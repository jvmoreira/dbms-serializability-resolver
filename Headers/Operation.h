// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Operation {
public:
    //Construtor
    Operation(string operationDef);

    //Getters e Setters
    unsigned int getId() { return this->transactionId; }
    char getAction() { return this->action; }
    char getAttr() { return this->attribute; }
    unsigned int getTS() { return this->timestamp; }
    bool after(Operation T) { return this->getTS() > T.getTS(); }
private:
    unsigned int id;
    unsigned int transactionId;
    char action;
    char attribute;
    unsigned int timestamp;
};