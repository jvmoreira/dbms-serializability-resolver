// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "Operation.h"

Operation::Operation(string operationDef) {
    stringstream definition(operationDef);
    string tokens[4], *token = tokens;
    while( getline(definition, *(token++), ' ') );
    (stringstream) tokens[0] >> timestamp;
    (stringstream) tokens[1] >> transactionId;
    action = *(tokens[2].c_str());
    attribute = *(tokens[3].c_str());
}
