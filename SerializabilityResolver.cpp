// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "SerializabilityResolver.h"
#include "Tester.h"

/* Lê as transições recebidas */
SerializabilityResolver::SerializabilityResolver(istream& transactions) {
    this->tester = new Tester();

    // A função getline() retorna uma linha de transactions em line
    string t;
    while( getline(transactions, t) ) {
        Operation *op = new Operation(t);
        this->tester->newOp(op);
    }
}

void SerializabilityResolver::writeSchedules(ostream& output) {
    int cont = 1;
    for( auto& schedule : this->tester->getSchedules() ) {

        stringstream s;
        for( unsigned int i = 0; i < schedule->getTransactionIds().size(); i++ )
            s << schedule->getTransactionIds()[i] << (i == schedule->getTransactionIds().size()-1 ? "" : ",");

        output << cont++ <<  " " << s.str() << " " << schedule->isConflictSerial() << " " << schedule->isViewEquivalent() << endl;
    }
}
