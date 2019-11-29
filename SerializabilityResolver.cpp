// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// ====================================================

#include "SerializabilityResolver.h"
#include "Transactions.h"

/* Lê as transições recebidas */
SerializabilityResolver::SerializabilityResolver(istream& transactions) {
    // this->schedule = new Schedule();
    this->conflict = new ConflictTester();

    // A função getline() retorna uma linha de transactions em line
    string t;
    while( getline(transactions, t) ) {
        Operation *op = new Operation(t);
        this->conflict->newOp(op);
        // this->newOp(op);
    }
}

// void SerializabilityResolver::newOp(Operation* op) {
//     // this->conflict->newOp(op);
//     Transaction* T = this->findById(op->getId());
//     if(T) T->addOp(op);
//     else {
//         /*Transaction *T = */this->newTransaction(op);
//     }
//
// }
