// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "SerializabilityResolver.h"
#include "Graph.h"

int main() {
    cout << "=====================" << '\n'
         << "Leitura de Transações" << '\n'
         << "=====================" << "\n\n";

    //SerializabilityResolver *solver = new SerializabilityResolver(cin);
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

    /**
        T1 <---->T2
        ^^
        ||
        ||
        T3
    */

    Graph* teste = new Graph();
    auto node1 = teste->createNode(10);
    auto node2 = teste->createNode(30);
    auto node3 = teste->createNode(20);

    node1->addNode(node2);
    node2->addNode(node1);
    node3->addNode(node1);
    node3->addNode(node1);

    printf("Ciclo encontrado: %d\n",teste->findCycle());

    return(0);
}
