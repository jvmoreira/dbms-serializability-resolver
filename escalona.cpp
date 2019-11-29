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

    SerializabilityResolver *solver = new SerializabilityResolver(cin);
    solver->writeSchedules(cout);

    return(0);
}
