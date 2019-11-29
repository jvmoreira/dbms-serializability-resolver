// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

#include "Transactions.h"

class SerializabilityResolver {
    // Schedule* schedule;
    Tester *conflict;
public:
    SerializabilityResolver(istream& transactions);
    // Transaction* findById(unsigned int id) { return this->schedule->findById(id); }
    // void newOp(Operation* op);
    // Transaction* newTransaction(Operation* op) {
    //     Transaction *T = new Transaction(op);
    //     this->schedule->addTransaction(T);
    //     return T;
    // }
};
