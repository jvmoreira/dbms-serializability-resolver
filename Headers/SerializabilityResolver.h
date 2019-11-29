// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

#include "Tester.h"

class SerializabilityResolver {
    Tester *tester;
public:
    SerializabilityResolver(istream& transactions);
    void writeSchedules(ostream& output);
};
