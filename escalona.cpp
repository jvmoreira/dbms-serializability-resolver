// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// ====================================================

#include "SerializabilityResolver.h"

int main() {
    cout << "=====================" << '\n'
         << "Leitura de Transações" << '\n'
         << "=====================" << "\n\n";

    SerializabilityResolver *solver = new SerializabilityResolver(cin);
    // Transaction *T = solver->findById(2);
    // T->printOperations();

    // Operation *Op = new Operation("1 1 R X");
    // Operation *Op2 = new Operation("2 1 R Z");
    // Transaction *T = new Transaction(Op);
    // T->addOp(Op2);
    //
    // Schedule *s = new Schedule();
    // s->addTransaction(T);
    // Transaction *newT = s->findById(1);

    // if(newT) newT->printOperations();
    // else cout << "Não achei" << endl;
    // Op->printOperation();
    // T->printOperations();

    return(0);
}
